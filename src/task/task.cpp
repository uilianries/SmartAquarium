/**
 * \file
 * \brief Execute async task on application
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "task/task.hpp"

#include <stdexcept>

namespace smartaquarium {

task::task(const std::string& _task_name, work _work, Poco::Logger& _logger)
    : Poco::Task(_task_name)
    , logger_(_logger)
    , work_(_work)
{
}

void task::runTask()
{
}

} // namespace smartaquarium
