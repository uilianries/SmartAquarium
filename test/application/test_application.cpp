/**
 * \file
 * \brief Execute Unit Test for application
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include <chrono>
#include <thread>

#include <Poco/Path.h>
#include <Poco/Environment.h>
#include <Poco/File.h>

#include "test_application.hpp"

static bool g_signal_received = false; /**< Signal flag */

void test_application::SetUp()
{
    const std::string test_process_name{ "dummy_application" };
    const std::string bin_directory{ "test/application" };

    Poco::Path process_abs_path;
    ASSERT_TRUE(Poco::Path::find(bin_directory, test_process_name, process_abs_path));

    Poco::File process_fd{ process_abs_path };
    ASSERT_TRUE(process_fd.exists());
    ASSERT_TRUE(process_fd.canExecute());

    signal(SIGUSR1, &test_application::on_sigusr);

    Poco::Process::Args args;
    process_h_.reset(new Poco::ProcessHandle(Poco::Process::launch(process_abs_path.toString(), args)));
    ASSERT_NE(0, process_h_->id());
}

void test_application::TearDown()
{
    Poco::Process::requestTermination(process_h_->id());
    auto error_code = process_h_->wait();
    ASSERT_EQ(0, error_code);
}

void test_application::on_sigusr(int signum)
{
    if (signum == SIGUSR1) {
        g_signal_received = true;
    }
}

TEST_F(test_application, StartApplication)
{
    auto wait_for = [this](const std::chrono::seconds& limit) {
        auto timeout = std::chrono::steady_clock::now() + limit;
        while (std::chrono::steady_clock::now() <= timeout) {
            if (g_signal_received) {
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
        return g_signal_received;
    };

    ASSERT_TRUE(wait_for(std::chrono::seconds(10)));
}