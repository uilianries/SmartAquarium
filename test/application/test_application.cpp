/**
 * \file
 * \brief Execute Unit Test for application
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include <chrono>
#include <thread>

#include <Poco/AutoPtr.h>
#include <Poco/Path.h>
#include <Poco/Environment.h>
#include <Poco/File.h>
#include <Poco/Util/Application.h>
#include <Poco/Util/SystemConfiguration.h>
#include <Poco/Util/XMLConfiguration.h>


#include "test_application.hpp"

namespace test_smartaquarium
{
    static bool signal_received = false; /**< Signal flag */
}

void test_application::SetUp()
{
    const std::string test_process_name{ "dummy_application" };
    const std::string bin_directory{ "test/application" };

    Poco::Path process_abs_path;
    ASSERT_TRUE(Poco::Path::find(bin_directory, test_process_name, process_abs_path));

    Poco::File process_fd{ process_abs_path };
    ASSERT_TRUE(process_fd.exists());
    ASSERT_TRUE(process_fd.canExecute());

    Poco::AutoPtr<Poco::Util::SystemConfiguration> system_configuration(new Poco::Util::SystemConfiguration());
    auto current_pid = system_configuration->getInt("system.pid");

    auto test_config_name = test_process_name + ".xml";
    Poco::AutoPtr<Poco::Util::XMLConfiguration> xml_configuration(new Poco::Util::XMLConfiguration(test_config_name));
    xml_configuration->setInt(test_process_name + ".target", current_pid);
    xml_configuration->save(test_config_name);

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
        test_smartaquarium::signal_received = true;
    }
}

TEST_F(test_application, StartApplication)
{
    auto wait_for = [this](const std::chrono::seconds& limit) {
        auto timeout = std::chrono::steady_clock::now() + limit;
        while (std::chrono::steady_clock::now() <= timeout) {
            if (test_smartaquarium::signal_received) {
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
        return test_smartaquarium::signal_received;
    };

    ASSERT_TRUE(wait_for(std::chrono::seconds(10)));
}