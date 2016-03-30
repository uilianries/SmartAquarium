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

void test_application::SetUp()
{
    const std::string test_process_name{ "dummy_application" };
    const std::string bin_directory{ "test/application" };

    Poco::Path process_abs_path;
    ASSERT_TRUE(Poco::Path::find(bin_directory, test_process_name, process_abs_path));

    Poco::File process_fd{ process_abs_path };
    ASSERT_TRUE(process_fd.exists());
    ASSERT_TRUE(process_fd.canExecute());

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

TEST_F(test_application, StartApplication)
{
}