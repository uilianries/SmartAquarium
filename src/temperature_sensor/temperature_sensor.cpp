/**
 * \file
 * \brief Temperature sensor
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include "temperature_sensor/temperature_sensor.hpp"

namespace smartaquarium {

void temperature_sensor::on_disconnect(const IoT::MQTT::ConnectionLostEvent& event)
{
    logger().error("Disconnected from broker: " + event.cause);
}

void temperature_sensor::on_message_delivered(const IoT::MQTT::MessageDeliveredEvent& event)
{
    logger().information("Message delivered - Token " + std::to_string(event.token));
}

void temperature_sensor::on_message_arrived(const IoT::MQTT::MessageArrivedEvent& event)
{
    logger().information("Message received - topic: " + event.topic + " - payload: " + event.message.payload);
}

void temperature_sensor::on_connect(const IoT::MQTT::ConnectionDoneEvent& event)
{
    std::ignore = event;
    logger().information("Connected on broker");
}

void temperature_sensor::initialize_device()
{
    logger().information("Delegate thermal GPIO event");
    thermal_stream_.reset(new bbb::gpio::thermal_stream);
    thermal_stream_->set_polling_interval(std::chrono::seconds(10));
    thermal_stream_->delegate_event(std::bind(&temperature_sensor::on_temperature_event, this, std::placeholders::_1));
}

void temperature_sensor::on_temperature_event(const bbb::gpio::thermal_level_type& level)
{
    const auto& topic = device_options().mqtt.topic;
    auto token = mqtt_client().publish(topic, level, IoT::MQTT::QoS::AT_LEAST_ONCE);
    std::ostringstream oss;
    oss << "Temperature event: " << level << " - Publish Token: " << token;
    logger().information(oss.str());
}

} // namespace smartaquarium
