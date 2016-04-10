/**
 * \file
 * \brief Abstract actuator
 * \author Uilian Ries <uilianries@gmail.com>
 */

#ifndef SMARTAQUARIUM_ACTUATOR_HPP_
#define SMARTAQUARIUM_ACTUATOR_HPP_

#include "device/device.hpp"

namespace smartaquarium {

/**
 * \brief Abstract actuator
 */
class actuator : public device {
    /**
     * \brief Treat disconnection event
     * \param event disconnection cause
     */
    void on_disconnect(const IoT::MQTT::ConnectionLostEvent& event) override;

    /**
     * \brief Treat message delived event
     * \param event message token
     */
    void on_message_delivered(const IoT::MQTT::MessageDeliveredEvent& event) override;

    /**
     * \brief Treat message arrived from broker
     * \param event message paylod
     */
    void on_message_arrived(const IoT::MQTT::MessageArrivedEvent& event) override;

    /**
     * \brief On connect event from broker
     * \param client_id client name connected on broker
     */
    void on_connect(const std::string& client_id) override;

    /**
     * \brief Connect with gpio
     */
    void initialize_device() override;
};

} // namespace smartaquarium

#endif //SMARTAQUARIUM_ACTUATOR_HPP_
