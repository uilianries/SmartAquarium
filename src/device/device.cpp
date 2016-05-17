/**
 * \file
 * \brief Abstract device
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include "device/device.hpp"

#include <Poco/Delegate.h>
#include <boost/lexical_cast.hpp>
#include <sstream>
#include <tuple>

namespace smartaquarium {

void device::work()
{
    load_options();
    create_client();
    delegate_all();
    initialize_device();
}

void device::create_client()
{
    std::string topic;
    MQTTClientFactory::FactoryArguments arguments;
    std::tie(arguments, topic) = load_arguments();

    log_connection_data(arguments, topic);

    mqtt_client_ = MQTTClientFactory::CreateMQTTClient<MQTTClientFactory::ClientType::Paho>(std::move(arguments));
}

void device::log_connection_data(const MQTTClientFactory::FactoryArguments& arguments, const std::string& topic)
{
    std::ostringstream dump;
    dump << "MQTT Client Config: " << std::endl;
    dump << "Server URI: " << arguments.serverUri << std::endl;
    dump << "Client ID: " << arguments.clientId << std::endl;
    dump << "User Name: " << arguments.options.username << std::endl;
    dump << "Password: " << arguments.options.password << std::endl;
    dump << "Topic: " << topic << std::endl;
    logger().debug(dump.str());
}

std::tuple<MQTTClientFactory::FactoryArguments, std::string> device::load_arguments()
{
    IoT::MQTT::MQTTClientFactory::FactoryArguments arguments;

    arguments.serverUri = device_options_.mqtt.server.toString() + ":" + device_options_.mqtt.port;
    arguments.clientId = device_options_.mqtt.client_id;
    arguments.options.username = device_options_.mqtt.username;
    arguments.options.password = device_options_.mqtt.password;

    return std::make_tuple(arguments, device_options_.mqtt.topic);
}

void device::delegate_all()
{
    mqtt_client_->connectionLost += Poco::delegate(this, &device::on_disconnect);
    mqtt_client_->messageArrived += Poco::delegate(this, &device::on_message_arrived);
    mqtt_client_->messageDelivered += Poco::delegate(this, &device::on_message_delivered);
    mqtt_client_->connectionDone += Poco::delegate(this, &device::on_connect);
}

MQTTClient& device::mqtt_client()
{
    return *mqtt_client_;
}

const smartaquarium::device_options& device::device_options() const
{
    return device_options_;
}

void device::load_options()
{
    const auto& command_name = config().getString("application.name");

    device_options_.pin = get_config(command_name + ".pin");

    const auto mqtt_element = command_name + ".mqtt.";

    device_options_.mqtt.server = get_config(mqtt_element + "server");
    device_options_.mqtt.port = get_config(mqtt_element + "port");
    device_options_.mqtt.client_id = get_config(mqtt_element + "clientid");
    device_options_.mqtt.username = get_config(mqtt_element + "username");
    device_options_.mqtt.password = get_config(mqtt_element + "password");
    device_options_.mqtt.topic = get_config(mqtt_element + "topic");
}

std::string device::get_config(const std::string& option) const
{
    if (!config().hasOption(option)) {
        std::ostringstream oss;
        oss << "ERROR: Could not load config " << option;
        throw std::invalid_argument(oss.str());
    }
    return config().getString(option);
}

} // namespace smartaquarium
