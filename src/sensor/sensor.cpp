/**
 * \file
 * \brief Abstract sensor
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include "sensor/sensor.hpp"
#include "bbbgpio/string.hpp"
#include <boost/lexical_cast.hpp>

namespace smartaquarium {

void sensor::on_disconnect(const IoT::MQTT::ConnectionLostEvent& event)
{
    logger().error("Disconnected from broker: " + event.cause);
}

void sensor::on_message_delivered(const IoT::MQTT::MessageDeliveredEvent& event)
{
    logger().debug("Message delivered by token " + std::to_string(event.token));
    tokens_.erase(event.token);
}

void sensor::on_message_arrived(const IoT::MQTT::MessageArrivedEvent& event)
{
    logger().debug("Message received - topic: " + event.topic + " - payload: " + event.message.payload);
}

void sensor::on_connect(const IoT::MQTT::ConnectionDoneEvent& event)
{
    std::ignore = event;
    logger().debug("Connected on broker");
}

void sensor::initialize_device()
{
    auto pin = device_options().pin;
    logger().debug("Connect with GPIO " + pin);
    input_pin_.reset(new bbb::gpio::analog_istream(boost::lexical_cast<unsigned>(pin)));
    input_pin_->delegate_event(std::bind(&sensor::on_pin_level_event, this, std::placeholders::_1));
}

void sensor::on_pin_level_event(bbb::gpio::analog_level pin_level)
{
    tokens_.insert(mqtt_client().publish(device_options().mqtt.topic, bbb::gpio::to_string(pin_level),
        IoT::MQTT::QoS::AT_LEAST_ONCE));
}

} // namespace smartaquarium
