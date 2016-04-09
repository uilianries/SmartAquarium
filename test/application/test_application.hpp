/**
 * \file
 * \brief Execute basic test for application library
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef SMARTAQUARIUM_TEST_APP_HPP_
#define SMARTAQUARIUM_TEST_APP_HPP_

#include <memory>

#include <gtest/gtest.h>

#include <Poco/Process.h>
#include <Poco/AutoPtr.h>

#include "util/signal_handler.hpp"

namespace smartaquarium {
namespace test {
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

    protected:
        /**
         * \brief Returns SIGUSR1 flag
         * \return signal received from system
         */
        bool signal_received() const noexcept;

    private:
        std::unique_ptr<Poco::ProcessHandle> process_h_; /**< Process pid */
        std::unique_ptr<signal_handler> signal_handler_; /**< Get USR1 signal */
        bool signal_received_ = false; /**< Signal USR1 was received */

        /**
         * \brief Receive SIGUSR1 signal
         * \param signal POSIX signal id
         */
        void on_sigusr(const int& signal);
    };

} // namespace test
} // namespace smartaquarium

#endif // SMARTAi}QUARIUM_TEST_APP_HPP_
