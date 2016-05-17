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

    signal_handler::signal_handler(const std::initializer_list<int>& sig_list)
    {
        handler = this;
        for (const auto& sig : sig_list) {
            signal(sig, &signal_handler::on_signal);
        }
    }

    signal_handler::signal_handler(int sig)
        : signal_handler({ sig })
    {
    }

} // namespace test
} // namespace smartaquarium