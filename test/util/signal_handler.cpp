/**
 * \file
 * \brief Treat Posix signals
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include "signal_handler.hpp"

namespace smartaquarium {
namespace test {

    signal_handler* handler = nullptr; /**< Owner */

    void signal_handler::on_signal(int sig)
    {
        if (handler) {
            handler->on_signal_arrived.notify(handler, sig);
        }
    }

    signal_handler::signal_handler(int sig)
    {
        handler = this;
        signal(sig, &signal_handler::on_signal);
    }

} // namespace test
} // namespace smartaquarium