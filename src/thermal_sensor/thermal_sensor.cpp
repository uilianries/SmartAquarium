/**
 * \file
 * \brief Thermal sensor
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include "thermal_sensor.hpp"

namespace smartaquarium {

void thermal_sensor::on_disconnect(const IoT::MQTT::ConnectionLostEvent& event)
{
    std::ignore = event;
}

void thermal_sensor::on_message_delivered(const IoT::MQTT::MessageDeliveredEvent& event)
{
    std::ignore = event;
}

void thermal_sensor::on_message_arrived(const IoT::MQTT::MessageArrivedEvent& event)
{
    std::ignore = event;
}

void thermal_sensor::on_connect(const IoT::MQTT::ConnectionDoneEvent& event)
{
    std::ignore = event;
}

void thermal_sensor::initialize_device()
{
    thermal_stream_.delegate_event(std::bind(&thermal_sensor::on_temperature_event, this, std::placeholders::_1));
}

void thermal_sensor::on_temperature_event(const bbb::gpio::thermal_level_type& level)
{
    const  auto& topic = device_options().mqtt.topic;
    mqtt_client().unsubscribe(topic);
    mqtt_client().publish(topic, level, IoT::MQTT::QoS::AT_LEAST_ONCE);
}

} // namespace smartaquarium