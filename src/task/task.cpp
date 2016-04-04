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
    if (_task_name.empty()) {
        throw std::invalid_argument("Task name could not be empty.");
    }

    if (!_work) {
        throw std::invalid_argument("Work function could not be null.");
    }
}

void task::runTask()
{
    work_();
}

task::~task()
{
}

} // namespace smartaquarium
