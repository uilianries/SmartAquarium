/**
 * \file
 * \brief Execute Unit Test for application
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef SMARTAQUARIUM_TEST_APPLICATION_DUMMY_APP_HPP_
#define SMARTAQUARIUM_TEST_APPLICATION_DUMMY_APP_HPP_

#include "application/application.hpp"

namespace smartaquarium {
namespace test {

    /**
     * \brief Run application
     */
    class dummy_application : public smartaquarium::application {

        /**
         * \brief Send signal to test application
         */
        void work() override;
    };
} // namespace test
} // namespace smartaquarium

#endif // SMARTAQUARIUM_TEST_APPLICATION_DUMMY_APP_HPP_
