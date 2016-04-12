/**
 * \file
 * \brief Abstract device
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include "device/device.hpp"

#include <sstream>
#include <Poco/Delegate.h>
#include <boost/lexical_cast.hpp>

namespace smartaquarium {

void device::work()
{
    load_options();
    create_client();
    delegate_all();
    create_connection();
    initialize_device();
}

void device::create_client()
{
    std::string topic;
    MQTTClientFactory::FactoryArguments arguments;
    std::tie(arguments, topic) = load_arguments();

    log_connection_data(arguments, topic);

    mqtt_client_ = std::move(MQTTClientFactory::CreateMQTTClient<MQTTClientFactory::ClientType::Paho>(std::move(arguments)));
}

void device::create_connection()
{
    std::string topic;
    MQTTClientFactory::FactoryArguments arguments;
    std::tie(arguments, topic) = load_arguments();

    auto server_uri = arguments.serverUri;
    mqtt_client_->subscribe(std::move(topic), IoT::MQTT::QoS::AT_LEAST_ONCE);

    logger().information("MQTT Client is connected at " + server_uri);

    IoT::MQTT::ConnectionDoneEvent event;
    mqtt_client_->connectionDone.notify(this, event);
}

void device::log_connection_data(const MQTTClientFactory::FactoryArguments& arguments, const std::string& topic)
{
    std::ostringstream dump;
    dump << "MQTT Client Config:" << std::endl;
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
    const auto mqtt_element = command_name + ".mqtt.";

    if (!config().has(command_name)) {
        throw std::runtime_error("Could not load xml file config");
    }

    device_options_.pin = config().getString(command_name + ".pin");
    device_options_.mqtt.server = config().getString(mqtt_element + "server");
    device_options_.mqtt.port = config().getString(mqtt_element + "port");
    device_options_.mqtt.client_id = config().getString(mqtt_element + "clientid");
    device_options_.mqtt.username = config().getString(mqtt_element + "username");
    device_options_.mqtt.password = config().getString(mqtt_element + "password");
    device_options_.mqtt.topic = config().getString(mqtt_element + "topic");
}

} // namespace smartaquarium
