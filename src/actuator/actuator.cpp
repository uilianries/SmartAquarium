/**
 * \file
 * \brief Abstract actuator
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include "actuator/actuator.hpp"

#include <string>
#include <tuple>

#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Util/XMLConfiguration.h>
#include <Poco/AutoPtr.h>

namespace smartaquarium {

void actuator::on_disconnect(const IoT::MQTT::ConnectionLostEvent& event)
{
    logger().error("Disconnected from broker: " + event.cause);
}

void actuator::on_message_delivered(const IoT::MQTT::MessageDeliveredEvent& event)
{
    logger().debug("Message delivered by token " + std::to_string(event.token));
}

void actuator::on_message_arrived(const IoT::MQTT::MessageArrivedEvent& event)
{
    logger().debug("Message received - topic: " + event.topic + " - payload: " + event.message.payload);
    process_command_.at(event.topic)(event.message.payload);
}

void actuator::on_connect(const IoT::MQTT::ConnectionDoneEvent& event)
{
    std::ignore = event;
}

void actuator::initialize_device()
{
    update_level_from_file();
    actuator_options_.sensor_topic = get_config(commandName() + ".mqtt.sensor_topic");

    process_command_ = { { actuator_options_.sensor_topic, std::bind(&actuator::process_sensor_level, this, std::placeholders::_1) },
        { device_options().mqtt.topic, std::bind(&actuator::process_update_level, this, std::placeholders::_1) } };

    std::ostringstream oss;
    oss << commandName() << ": Initialize device - ";
    oss << " sensor topic: " << actuator_options_.sensor_topic;
    oss << "; sensor min level: " << actuator_options_.level.min;
    oss << "; sensor max level: " << actuator_options_.level.max;
    auto pin = static_cast<unsigned>(std::stoul(device_options().pin));
    oss << "; PIN: " << pin;
    logger().debug(oss.str());
    logger().debug("Creating GPIO connection");
    gpio_pin_.reset(new bbb::gpio::logic_ostream(pin));
    logger().debug("GPIO connection was created");
    output_off();

    mqtt_client().subscribeMany({ { actuator_options_.sensor_topic, IoT::MQTT::QoS::AT_LEAST_ONCE },
        { device_options().mqtt.topic, IoT::MQTT::QoS::AT_LEAST_ONCE } });
}

void actuator::process_update_level(const std::string& level)
{
    logger().debug(commandName() + ": Update sensor level");

    update_level_on_file(level);
    update_level_from_file();
}

void actuator::process_sensor_level(const std::string& level)
{
    auto dlevel = std::stod(level);
    std::ostringstream oss;

    const auto middle_temperature = (actuator_options_.level.min + actuator_options_.level.max) / 2;

    oss << commandName() << ": Received sensor event: " << dlevel;
    if ((dlevel < actuator_options_.level.min) and (current_level_ == bbb::gpio::pin_level::high)) {
        oss << " - under minimal temperature: " << actuator_options_.level.min;
        output_on();
    }
    else if ((dlevel > middle_temperature) and (current_level_ == bbb::gpio::pin_level::low)) {
        oss << " - over middle temperature: " << actuator_options_.level.max;
        output_off();
    }

    logger().debug(oss.str());
}

void actuator::output_on()
{
    *gpio_pin_ << bbb::gpio::pin_level::low;
    current_level_ = bbb::gpio::pin_level::low;
}

void actuator::output_off()
{
    *gpio_pin_ << bbb::gpio::pin_level::high;
    current_level_ = bbb::gpio::pin_level::high;
}

void actuator::update_level_from_file()
{
    actuator_options_.level.min = std::stod(get_config(get_config_min()));
    actuator_options_.level.max = std::stod(get_config(get_config_max()));
}

void actuator::update_level_on_file(const std::string& payload)
{
    Poco::JSON::Parser json_parser;
    auto parsed_result = json_parser.parse(payload);
    auto json_object_ptr = parsed_result.extract<Poco::JSON::Object::Ptr>();

    const auto& min = json_object_ptr->get("min").convert<int>();
    const auto& max = json_object_ptr->get("max").convert<int>();

    std::ostringstream oss;
    oss << "Received level update - min: " << min << " - max: " << max;
    logger().debug(oss.str());

    config().setInt(get_config_min(), min);
    config().setInt(get_config_max(), max);

    Poco::AutoPtr<Poco::Util::XMLConfiguration> xml_configuration(new Poco::Util::XMLConfiguration(get_configuration_file_path().toString()));
    xml_configuration->setInt(get_config_min(), min);
    xml_configuration->setInt(get_config_max(), max);
    xml_configuration->save(get_configuration_file_path().toString());
}

std::string actuator::get_config_max() const
{
    return commandName() + ".sensor.max";
}

std::string actuator::get_config_min() const
{
    return commandName() + ".sensor.min";
}

} // namespace smartaquarium
