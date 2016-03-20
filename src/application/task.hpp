/**
 * \file
 * \brief Execute async task on application
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef SMARTAQUARIUM_TASK_HPP_
#define SMARTAQUARIUM_TASK_HPP_

#include <functional>
#include <string>

#include <Poco/Task.h>

namespace smartaquarium {

/**
 * \brief Start an async task in middle the 
 *        application.
 */
class task : public Poco::Task {
    public:

    /**
     * Task assign
     */
     using work = std::function<void()>;

     /**
      * \brief Task constructor
      * \param _task_name task identifier
      * \param _work function to be executed in task
      */
     task(const std::string& _task_name, work _work);

    private:
    /**
     * \brief Start task work
     */
    void runTask() override;

    /** task to be executed */
    work work_;
};
} // namespace smartaquarium

#endif // SMARTAQUARIU_TASK_HPP_
