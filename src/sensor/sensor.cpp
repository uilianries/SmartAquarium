/**
 * \file
 * \brief Abstract sensor
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include "sensor/sensor.hpp"

namespace smartaquarium {

void sensor::on_disconnect(const IoT::MQTT::ConnectionLostEvent& event)
{
    logger().error("Disconnected from broker: " + event.cause);
}

void sensor::on_message_delivered(const IoT::MQTT::MessageDeliveredEvent& event)
{
    logger().debug("Message delivered by token " + std::to_string(event.token));
}

void sensor::on_message_arrived(const IoT::MQTT::MessageArrivedEvent& event)
{
    logger().debug("Message received - topic: " + event.topic + " - payload: " + event.message.payload);
}

} // namespace smartaquarium
