/**
 * \file
 * \brief Unit Test for Device
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "device/dummy_device.hpp"

#include <cassert>
#include <stdexcept>

#include <Poco/Util/ServerApplication.h>
#include <signal.h>

namespace smartaquarium {
namespace test {

void dummy_device::initialize_device()
{
    auto ss = config().getString("dummy_device.mqtt.topic");
    mqtt_client_->subscribe(ss, IoT::MQTT::QoS::AT_LEAST_ONCE);
    assert(mqtt_client_->connected());
}

void dummy_device::on_disconnect(const IoT::MQTT::ConnectionLostEvent& event)
{
    throw std::runtime_error(event.cause);
}

void dummy_device::on_message_delivered(const IoT::MQTT::MessageDeliveredEvent& event)
{
    assert(token_ == event.token);
}

void dummy_device::on_message_arrived(const IoT::MQTT::MessageArrivedEvent& event)
{
    auto target = config().getString("dummy_device.mqtt.target");
    token_ = mqtt_client_->publish(target, event.message.payload, IoT::MQTT::QoS::AT_LEAST_ONCE);
}

void dummy_device::on_connect(const std::string& client_id)
{
    std::ignore = client_id;
    kill(config().getInt("dummy_device.pid"), SIGUSR1);
}

} // namespace test
} // namespace smartaquarium
