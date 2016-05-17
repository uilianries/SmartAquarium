/**
 * \file
 * \brief Thermal sensor
 * \author Uilian Ries <uilianries@gmail.com>
 */

#ifndef SMARTAQUARIUM_TEMPERATURE_SENSOR_HPP
#define SMARTAQUARIUM_TEMPERATURE_SENSOR_HPP

#include <bbbgpio/stream.hpp>
#include "device/device.hpp"

namespace smartaquarium {

/**
 * \brief Treat thermal sensor DS1820
 */
class temperature_sensor : public device {
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
     * \brief Send connected signal
     * \param event placeholder
     */
    void on_connect(const IoT::MQTT::ConnectionDoneEvent& event) override;

    /**
     * \brief Delegate monitor callback
     */
    void initialize_device() override;

    /** Temperature monitor */
    std::unique_ptr<bbb::gpio::thermal_stream> thermal_stream_;

    /**
     * \brief Forward event to broker
     * \param level New temperature level
     */
    void on_temperature_event(const bbb::gpio::thermal_level_type& level);
};

} // namespace smartaquarium

#endif //SMARTAQUARIUM_TEMPERATURE_SENSOR_HPP
