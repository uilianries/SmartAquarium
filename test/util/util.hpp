/**
 * \file
 * \brief Unit Test Utils
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef SMARTAQUARIUM_TEST_UTIL_HPP_
#define SMARTAQUARIUM_TEST_UTIL_HPP_

#include <chrono>
#include <thread>
#include <cassert>

#include <Poco/Path.h>
#include <Poco/Process.h>
#include <Poco/File.h>
#include <Poco/Pipe.h>

namespace smartaquarium {
namespace test {

    template <class Duration>
    /**
     * \brief Wait for condition, until timeout.
     *        When the condition becomes true, then
     *        the function returns true. Otherwise,
     *        wait until the timeout
     * \param limit Duration time limit
     * \param condtion expression to condition validation
     * \return true if the condition is true until timeout. Otherwise, false.
     */
    inline bool wait_for(const Duration& limit, std::function<bool()> condition)
    {
        auto timeout = std::chrono::steady_clock::now() + limit;
        while (std::chrono::steady_clock::now() <= timeout) {
            if (condition()) {
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        return condition();
    }

    /**
     * \brief Create some process by Poco::Process
     * \param process_path path to process file
     */
    inline std::unique_ptr<Poco::ProcessHandle> launch_process(const Poco::Path& process_path)
    {
        Poco::File dummy_process_file(process_path);
        assert(dummy_process_file.exists());
        assert(dummy_process_file.isFile());
        assert(dummy_process_file.canExecute());

        std::vector<std::string> args;
        Poco::Pipe pipe_out;
        std::unique_ptr<Poco::ProcessHandle> process_h(new Poco::ProcessHandle(Poco::Process::launch(process_path.toString(), args, nullptr, nullptr, &pipe_out)));
        assert(process_h->id());

        return process_h;
    }

} // namespace test
} // namespace smartaquarium

#endif // SMARTAQUARIUM_TEST_UTIL_HPP_
