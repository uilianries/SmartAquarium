/**
 * \file
 * \brief Execute Unit Test for application
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include <chrono>
#include <thread>

#include <Poco/AutoPtr.h>
#include <Poco/Path.h>
#include <Poco/Util/Application.h>
#include <Poco/Util/SystemConfiguration.h>
#include <Poco/Util/XMLConfiguration.h>
#include <Poco/Delegate.h>

#include "test_application.hpp"
#include "util/util.hpp"

namespace smartaquarium {
namespace test {

    void test_application::SetUp()
    {
        const std::string test_process_name{ "dummy_application" };
        const Poco::Path test_process_bin_path{ "test/application/" + test_process_name };

        Poco::AutoPtr<Poco::Util::SystemConfiguration> system_configuration(new Poco::Util::SystemConfiguration());
        auto current_pid = system_configuration->getInt("system.pid");

        auto test_config_name = test_process_name + ".xml";
        Poco::AutoPtr<Poco::Util::XMLConfiguration> xml_configuration(new Poco::Util::XMLConfiguration(test_config_name));
        xml_configuration->setInt(test_process_name + ".target", current_pid);
        xml_configuration->save(test_config_name);

        signal_handler_.reset(new signal_handler(SIGUSR1));
        signal_handler_->on_signal_arrived += Poco::delegate(this, &test_application::on_sigusr);

        process_h_ = launch_process(test_process_bin_path);
    }

    void test_application::TearDown()
    {
        Poco::Process::requestTermination(process_h_->id());
        auto error_code = process_h_->wait();
        ASSERT_EQ(0, error_code);
    }

    void test_application::on_sigusr(const int& signum)
    {
        if (signum == SIGUSR1) {
            signal_received_ = true;
        }
    }

    bool test_application::signal_received() const noexcept
    {
        return signal_received_;
    }

    TEST_F(test_application, StartApplication)
    {
        ASSERT_TRUE(wait_for(std::chrono::seconds(10), [this]() { return signal_received(); }));
    }

} // namespace test
} // namespace smartaquarium
