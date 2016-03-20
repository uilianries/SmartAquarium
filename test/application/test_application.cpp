/**
 * \file
 * \brief Execute Unit Test for application
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include <thread>
#include <chrono>

#include <cppunit/extensions/HelperMacros.h>
#include <Poco/Path.h>
#include <Poco/Environment.h>
#include <Poco/File.h>

#include "test_application.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(test_application);

void test_application::setUp()
{
    const std::string test_process_name{ "dummy_application" };
    const std::string bin_directory{ "test/application" };

    Poco::Path process_abs_path;
    CPPUNIT_ASSERT(Poco::Path::find(bin_directory, test_process_name, process_abs_path));

    Poco::File process_fd{ process_abs_path };
    CPPUNIT_ASSERT(process_fd.exists());
    CPPUNIT_ASSERT(process_fd.canExecute());

    Poco::Process::Args args;
    process_h_.reset(new Poco::ProcessHandle(Poco::Process::launch(process_abs_path.toString(), args)));
    CPPUNIT_ASSERT(process_h_->id() != 0);
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void test_application::tearDown()
{
    Poco::Process::requestTermination(process_h_->id());
    auto error_code = process_h_->wait();
    CPPUNIT_ASSERT_EQUAL(0, error_code);
}

void test_application::start_application()
{
}