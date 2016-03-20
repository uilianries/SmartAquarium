/**
 * \file
 * \brief Execute async task on application
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "task.hpp"

#include <stdexcept>

namespace smartaquarium {

task::task(const std::string& _task_name, work _work)
    : Poco::Task(_task_name)
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

} // namespace smartaquarium
