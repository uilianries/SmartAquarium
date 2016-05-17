/**
 * \file
 * \brief Abstract sensor
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef SMARTAQUARIUM_SENSOR_HPP_
#define SMARTAQUARIUM_SENSOR_HPP_

#include <memory>
#include <unordered_set>
#include <bbbgpio/stream.hpp>
#include "device/device.hpp"

namespace smartaquarium {
/**
 * \brief Abstract sensor
 */
class sensor : public device {
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
     * \brief Connect with gpio
     */
    void initialize_device() override;

    /**
     * \brief Receive event from BBB GPIO
     * \param pin_level value changed
     */
    void on_pin_level_event(bbb::gpio::analog_level pin_level);

    std::unique_ptr<bbb::gpio::analog_istream> input_pin_; /**< Read GPIO */
    std::unordered_set<int> tokens_; /**< Published tokens */
};

} // namespace smartaquarium

#endif // SMARTAQUARIUM_SENSOR_HPP_
