/**
 * \file
 * \brief Application library for all modules
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "application.hpp"

#include <tuple>
#include <string>
#include <stdexcept>
#include <sstream>

#include <Poco/Path.h>
#include <Poco/Environment.h>

#include "application/mqtt_task.hpp"

namespace smartaquarium {

int application::main(const ArgVec& args)
{
    std::ignore = args;
    Poco::TaskManager task_manager;

    launch_mqtt_client(task_manager);

    waitForTerminationRequest();

    task_manager.cancelAll();
    task_manager.joinAll();

    return Poco::Util::Application::EXIT_OK;
}

void application::configure_logger()
{
    // @TODO - Think about use syslog instead console
#ifdef DEBUG
    logger().setLevel("debug");
    Poco::Logger::root().setLevel("debug");
#endif
    pattern_formatter_.assign(new Poco::PatternFormatter);
    pattern_formatter_->setProperty("pattern", "%Y-%m-%d %H:%M:%S %s: %t");
    formatting_channel_.assign(new Poco::FormattingChannel(pattern_formatter_, logger().getChannel()));
    Poco::Logger::root().setChannel(formatting_channel_);
    logger().setChannel(formatting_channel_);
}

void application::initialize(Application& self)
{
    configure_logger();

    std::ostringstream env_path;
    env_path << Poco::Environment::get("PATH");
    env_path << ":" << Poco::Environment::get("PWD");
    const std::string process_name{ commandName() + ".xml" };
    Poco::Path config_path;

    if (!Poco::Path::find(env_path.str(), process_name, config_path)) {
        std::ostringstream oss;
        oss << "ERROR: Could not find config file " << process_name
            << " at path " << env_path.str();
        throw std::runtime_error(oss.str());
    }

    loadConfiguration(config_path.toString());
    logger().information("Configuration " + config_path.getFileName() + " loaded");

    ServerApplication::initialize(self);
}

void application::launch_mqtt_client(Poco::TaskManager& _task_manager)
{
    IoT::MQTT::MQTTClientFactory::FactoryArguments arguments;

    const auto prefix = commandName() + ".mqtt.";
    auto get_value = [&prefix, this](const std::string& property) { return config().getString(prefix + property); };

    arguments.serverUri = get_value("server") + ":" + get_value("port");
    arguments.clientId = get_value("clientid");
    arguments.options.username = get_value("username");
    arguments.options.password = get_value("password");
    auto topic = get_value("topic");

    std::ostringstream dump;
    dump << "MQTT Client Config:" << std::endl;
    dump << "Server URI: " << arguments.serverUri << std::endl;
    dump << "Client ID: " << arguments.clientId << std::endl;
    dump << "User Name: " << arguments.options.username << std::endl;
    dump << "Password: " << arguments.options.password << std::endl;
    dump << "Topic: " << topic << std::endl;
    logger().debug(dump.str());

    _task_manager.start(new mqtt_task(mqtt_client_, std::move(arguments), std::move(topic), logger()));
}

} // namespace smartaquarium
