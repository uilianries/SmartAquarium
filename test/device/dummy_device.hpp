/**
 * \file
 * \brief Unit Test for Device
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef SMARTAQUARIUM_DUMMY_DEVICE_HPP_
#define SMARTAQUARIUM_DUMMY_DEVICE_HPP_

#include "device/device.hpp"

namespace smartaquarium {
namespace test {

/**
* \brief Unit Test for Device
*/
class dummy_device : public device {
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
     * \param event placeholder
     */
    void on_connect(const IoT::MQTT::ConnectionDoneEvent& event) override;

    /**
     * \brief Load configuration
     */
    void initialize_device() override;

    int token_ = -1; /**< Publish token */
};

} // namespace test
} // namespace smartaquarium

#endif // SMARTAQUARIUM_DUMMY_DEVICE_HPP_
