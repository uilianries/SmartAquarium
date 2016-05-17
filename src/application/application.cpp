/**
 * \file
 * \brief Application library for all modules
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "application.hpp"

#include <Poco/TaskManager.h>
#include <Poco/Environment.h>
#include <Poco/File.h>
#include <iostream>
#include <sstream>
#include "task/task.hpp"

namespace smartaquarium {

int application::main(const ArgVec& args)
{
    std::ignore = args;
    Poco::TaskManager task_manager;

    task_manager.start(new task("ChildWork", std::bind(&application::work, this), logger()));

    waitForTerminationRequest();

    task_manager.cancelAll();
    task_manager.joinAll();

    return Poco::Util::Application::EXIT_OK;
}

void application::configure_logger()
{
    logger().setLevel("debug");
    Poco::Logger::root().setLevel("debug");

    file_channel_.assign(new Poco::FileChannel);
    auto app_name = config().getString("application.name");
    file_channel_->setProperty("path", "/var/tmp/" + app_name + ".log");
    file_channel_->setProperty("rotation", "10 M");
    file_channel_->setProperty("archive", "timestamp");

    pattern_formatter_.assign(new Poco::PatternFormatter);
    pattern_formatter_->setProperty("pattern", "%Y-%m-%d %H:%M:%S %s: %t");
    formatting_channel_.assign(new Poco::FormattingChannel(pattern_formatter_, file_channel_));
    Poco::Logger::root().setChannel(formatting_channel_);
    logger().setChannel(formatting_channel_);
}

void application::initialize(Application& self)
{
    configure_logger();
    loadConfiguration(get_configuration_file_path().toString());
    ServerApplication::initialize(self);
}

Poco::Path application::get_configuration_file_path() const
{
    std::ostringstream oss;
    oss << "/etc/smartaquarium/" << config().getString("application.name") << ".xml";
    return oss.str();
}

} // namespace smartaquarium
