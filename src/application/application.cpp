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

namespace smartaquarium {

int application::main(const ArgVec& args)
{
    std::ignore = args;

    waitForTerminationRequest();

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

} // namespace smartaquarium
