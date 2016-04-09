/**
 * \file
 * \brief Treat Posix signals
 * \author Uilian Ries <uilianries@gmail.com>
 */

#ifndef SMARTAQUARIUM_SIGNAL_HANDLER_HPP
#define SMARTAQUARIUM_SIGNAL_HANDLER_HPP

#include <signal.h>
#include <Poco/BasicEvent.h>

namespace smartaquarium {
namespace test {

    /**
     * \brief Treat any POSIX signal
     */
    class signal_handler {

    public:
        /**
         * \brief Observer some signal
         * \param sig POSIX signal id
         */
        explicit signal_handler(int sig);

        /**
         * \brief Launch when the observed signal arrives
         */
        Poco::BasicEvent<const int> on_signal_arrived;

    private:
        /**
         * \brief Receive signal notification from the system
         * \param sig POSIX signal id
         */
        static void on_signal(int sig);
    };

} // namespace test
} // namespace smartaquarium

#endif //SMARTAQUARIUM_SIGNAL_HANDLER_HPP
