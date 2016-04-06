/**
 * \file
 * \brief Abstract sensor
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include "sensor/sensor.hpp"

namespace smartaquarium {

void sensor::on_disconnect(const IoT::MQTT::ConnectionLostEvent& event)
{
}

void sensor::on_message_delivered(const IoT::MQTT::MessageDeliveredEvent& event)
{
}

void sensor::on_message_arrived(const IoT::MQTT::MessageArrivedEvent& event)
{
}

} // namespace smartaquarium
