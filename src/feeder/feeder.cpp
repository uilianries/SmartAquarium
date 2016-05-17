/**
 * \file
 * \brief Abstract actuator
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include "feeder/feeder.hpp"

namespace smartaquarium {

void feeder::on_disconnect(const IoT::MQTT::ConnectionLostEvent& event)
{
    logger().error("Disconnected from broker: " + event.cause);
}

void feeder::on_message_delivered(const IoT::MQTT::MessageDeliveredEvent& event)
{
    logger().debug("Message delivered by token " + std::to_string(event.token));
}

void feeder::on_message_arrived(const IoT::MQTT::MessageArrivedEvent& event)
{
    logger().debug("Message received - topic: " + event.topic + " - payload: " + event.message.payload);
    process_command_.at(event.topic)(event.message.payload);
}

void feeder::on_connect(const IoT::MQTT::ConnectionDoneEvent& event)
{
    std::ignore = event;
}

void feeder::initialize_device()
{
    process_command_.insert({ device_options().mqtt.topic, std::bind(&feeder::on_command, this, std::placeholders::_1) });

    std::ostringstream oss;
    oss << commandName() << ": Initialize device - ";
    logger().debug("Creating GPIO connection");
    gpio_pin_.reset(new bbb::gpio::logic_ostream(std::stoul(device_options().pin)));
    logger().debug("GPIO connection was created");
    output_off();

    mqtt_client().subscribe(device_options().mqtt.topic, IoT::MQTT::QoS::AT_LEAST_ONCE);
}

void feeder::output_on()
{
    *gpio_pin_ << bbb::gpio::pin_level::low;
    current_level_ = bbb::gpio::pin_level::low;
}

void feeder::output_off()
{
    *gpio_pin_ << bbb::gpio::pin_level::high;
    current_level_ = bbb::gpio::pin_level::high;
}

void feeder::on_command(const std::string& command)
{
    if (command == "on") {
        output_on();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        output_off();
        mqtt_client().publish("smartaquarium/actuator/feeder/level", "0", IoT::MQTT::QoS::AT_LEAST_ONCE);
    }
}

} // namespace smartaquarium
