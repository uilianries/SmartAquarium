/**
 * \file
 * \brief Application library for all modules
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "application.hpp"

#include <Poco/TaskManager.h>
#include "task/task.hpp"

namespace smartaquarium {

int application::main(const ArgVec& args)
{
    Poco::TaskManager task_manager;

    task_manager.start(new task("ChildWork", std::bind(&application::work, this), logger()));

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
    loadConfiguration();
    ServerApplication::initialize(self);
}

} // namespace smartaquarium
