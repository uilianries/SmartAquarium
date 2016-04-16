/**
 * \file
 * \brief Unit Test for Device
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "device/dummy_device.hpp"

#include <cassert>

namespace smartaquarium {
namespace test {

    void dummy_device::initialize_device()
    {
        try {
            get_config("abnormal_option");
            abort();
        }
        catch (const std::invalid_argument&) {
        }
        assert(mqtt_client().connected());
    }

    void dummy_device::on_disconnect(const IoT::MQTT::ConnectionLostEvent& event)
    {
        std::ignore = event;
    }

    void dummy_device::on_message_delivered(const IoT::MQTT::MessageDeliveredEvent& event)
    {
        std::ignore = event.token;
    }

    void dummy_device::on_message_arrived(const IoT::MQTT::MessageArrivedEvent& event)
    {
        const auto& topic = config().getString(commandName() + ".mqtt.target");

        if (event.message.payload == "disconnect") {
            token_ = mqtt_client().publish(topic, device_options().pin, IoT::MQTT::QoS::AT_LEAST_ONCE);
            mqtt_client().connectionLost(this, IoT::MQTT::ConnectionLostEvent());
        }
        else {
            token_ = mqtt_client().publish(topic, event.message.payload, IoT::MQTT::QoS::AT_LEAST_ONCE);
        }
    }

    void dummy_device::on_connect(const IoT::MQTT::ConnectionDoneEvent& event)
    {
        std::ignore = event;
        const auto& topic = config().getString(commandName() + ".mqtt.target");
        mqtt_client().publish(topic, device_options().mqtt.client_id, IoT::MQTT::QoS::AT_LEAST_ONCE);
    }

} // namespace test
} // namespace smartaquarium
