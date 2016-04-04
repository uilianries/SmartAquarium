/**
 * \file
 * \brief Execute Unit Test for application
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "application/application.hpp"

#include <sys/types.h>
#include <signal.h>

#include <iostream>

/**
 * \brief Run application
 */
class dummy_application : public smartaquarium::application {

    /**
     * \brief
     */
    void work() override
    {
        auto target = config().getInt(commandName() + ".target");
        kill(target, SIGUSR1);
    }
};

POCO_SERVER_MAIN(dummy_application)