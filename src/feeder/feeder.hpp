/**
 * \file
 * \brief Device feeder dispenser
 * \author Uilian Ries <uilianries@gmail.com>
 */

#ifndef SMARTAQUARIUM_FEEDER_HPP_
#define SMARTAQUARIUM_FEEDER_HPP_

#include <unordered_map>
#include <memory>
#include <bbbgpio/stream.hpp>
#include "device/device.hpp"

namespace smartaquarium {

/**
 * \brief Feeder device
 */
class feeder : public device {
private:
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
     * \brief Update a new level from broker
     * \param level new values to monitor
     */
    void process_update_level(const std::string& level);

    /**
     * \brief Process new data level from the sensor
     * \param level sensor level
     */
    void process_sensor_level(const std::string& level);

    /**
     * \brief Connect with gpio
     */
    void initialize_device() override;

    /** Treat events */
    using process_map = std::unordered_map<std::string, std::function<void(const std::string&)> >;

    /**
     * \brief Enable output on relay
     */
    void output_on();

    /**
     * \brief Disable output on relay
     */
    void output_off();

    /**
     * \brief Dispense food event request
     * \param command payload information
     */
    void on_command(const std::string& command);

    /** Command arrived */
    process_map process_command_;
    /** Pin access */
    std::unique_ptr<bbb::gpio::logic_ostream> gpio_pin_;
    /** Current GPIO level */
    bbb::gpio::pin_level current_level_;
};

} // namespace smartaquarium

#endif // SMARTAQUARIUM_FEEDER_HPP_
