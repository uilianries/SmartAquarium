/**
 * \file
 * \brief Abstract actuator
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include "actuator.hpp"

namespace smartaquarium {

} // namespace smartaquarium
void smartaquarium::actuator::on_disconnect(const IoT::MQTT::ConnectionLostEvent& event)
{
    logger().error("Disconnected from broker: " + event.cause);
}

void smartaquarium::actuator::on_message_delivered(const IoT::MQTT::MessageDeliveredEvent& event)
{
    logger().debug("Message delivered by token " + std::to_string(event.token));
}

void smartaquarium::actuator::on_message_arrived(const IoT::MQTT::MessageArrivedEvent& event)
{
    logger().debug("Message received - topic: " + event.topic + " - payload: " + event.message.payload);
}

void smartaquarium::actuator::on_connect(const IoT::MQTT::ConnectionDoneEvent& event)
{
    (void)event;
    logger().debug("Connected on broker with the client id ");
}

void smartaquarium::actuator::initialize_device()
{
    logger().debug("Connect with GPIO");
}
