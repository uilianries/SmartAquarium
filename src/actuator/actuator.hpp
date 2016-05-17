/**
 * \file
 * \brief Abstract actuator
 * \author Uilian Ries <uilianries@gmail.com>
 */

#ifndef SMARTAQUARIUM_ACTUATOR_HPP_
#define SMARTAQUARIUM_ACTUATOR_HPP_

#include <unordered_map>
#include <memory>
#include <bbbgpio/stream.hpp>
#include "device/device.hpp"

namespace smartaquarium {

/**
 * \brief Actuator data
 */
struct actuator_options {
    /**
     * \brief Max and min levels to treat
     */
    struct sensor_level {
        /** Min level */
        double min = 0.0;
        /** Max level */
        double max = 0.0;
    };
    /** sensor to observe */
    std::string sensor_topic;
    /** Current Sensor level */
    sensor_level level;
};

/**
 * \brief Abstract actuator
 */
class actuator : public device {
public:
    /**
   * \brief Default constructor
   */
    actuator() = default;

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
     * \brief Update the internal level
     */
    void update_level_from_file();

    /**
     * \brief Update data from broker, to config file
     * \param payload Formatted message from broker
     */
    void update_level_on_file(const std::string& payload);

    /**
     * \brief Get max config in XML file
     * \return max level path in config file
     */
    std::string get_config_max() const;

    /**
     * \brief Get min config in XML file
     * \return minimal level path in config file
     */
    std::string get_config_min() const;

    /** Actuator options */
    actuator_options actuator_options_;
    /** Command arrived */
    process_map process_command_;
    /** Pin access */
    std::unique_ptr<bbb::gpio::logic_ostream> gpio_pin_;
    /** Current GPIO level */
    bbb::gpio::pin_level current_level_;
};

} // namespace smartaquarium

#endif // SMARTAQUARIUM_ACTUATOR_HPP_
