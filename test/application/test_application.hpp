/**
 * \file
 * \brief Execute basic test for application library
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef SMARTAQUARIUM_TEST_APP_HPP_
#define SMARTAQUARIUM_TEST_APP_HPP_

#include <memory>
#include <csignal>

#include <gtest/gtest.h>

#include <Poco/Process.h>
#include <Poco/AutoPtr.h>

/**
 * \brief Test case for application library
 */
class test_application : public testing::Test {

public:
    /**
     * \brief Spawn application process
     */
    void SetUp() override;

    /**
     * \brief Kill application process
     */
    void TearDown() override;

private:
    std::unique_ptr<Poco::ProcessHandle> process_h_; /**< Process pid */

    /**
     * \brief Set signal received from dummy application
     * \param signum signal number received
     */
    static void on_sigusr(int signum);
};

#endif // SMARTAQUARIUM_TEST_APP_HPP_