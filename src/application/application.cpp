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
#include <Poco/TaskManager.h>

#include "task.hpp"

namespace smartaquarium {

int application::main(const ArgVec& args)
{
    std::ignore = args;
    Poco::TaskManager task_manager;

    auto task_name = commandName();

    // @TODO - Add Task for connect MQTT client

    task_manager.start(new task(task_name, std::bind(&application::execute, this)));

    waitForTerminationRequest();

    task_manager.cancelAll();
    task_manager.joinAll();

    return Poco::Util::Application::EXIT_OK;
}

void application::initialize(Application& self)
{
    std::string env_path{ Poco::Environment::get("PATH") };
    env_path += ":" + Poco::Environment::get("PWD");
    const std::string process_name{ commandName() + ".xml" };
    Poco::Path config_path;

    if (!Poco::Path::find(env_path, process_name, config_path)) {
        std::ostringstream oss;
        oss << "ERROR: Could not find config file " << process_name
            << " at path " << env_path;
        throw std::runtime_error(oss.str());
    }

    loadConfiguration(config_path.toString());
    logger().information("Configuration loaded");

    ServerApplication::initialize(self);
}

void application::execute()
{
    logger().trace(__func__);
}

} // namespace smartaquarium
