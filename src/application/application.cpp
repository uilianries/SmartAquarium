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

#include <Poco/Path.h>
#include <Poco/Environment.h>
#include <Poco/TaskManager.h>

#include "task.hpp"

namespace smartaquarium {

int application::main(const ArgVec& args)
{
    std::ignore = args;
    Poco::TaskManager task_manager;

    std::string task_name = name();

    // @TODO - Add Task for connect MQTT client

    task_manager.start(new task(task_name, std::bind(&application::execute, this)));

    waitForTerminationRequest();

    task_manager.cancelAll();
    task_manager.joinAll();

    return Poco::Util::Application::EXIT_OK;
}

void application::initialize(Application& self)
{
    const std::string env_path{ Poco::Environment::get("PATH") };
    const std::string process_name{ name() + std::string(".xml") };
    Poco::Path config_path;

    if (!Poco::Path::find(env_path, process_name, config_path)) {
        throw std::runtime_error("ERROR: Could not find config file.");
    }

    loadConfiguration(config_path.toString());
    logger().information("Configuration loaded");

    ServerApplication::initialize(self);
}

void application::execute()
{
}

} // namespace smartaquarium
