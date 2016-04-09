/**
 * \file
 * \brief Execute Unit Test for application
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "application/dummy_application.hpp"

#include <signal.h>
#include <sys/types.h>

namespace smartaquarium {
namespace test {

    void dummy_application::work()
    {
        auto target = config().getInt(commandName() + ".target");
        kill(target, SIGUSR1);
    }

} // namespace test
} // namespace smartaquarium
