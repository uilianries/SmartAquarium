/**
 * \file
 * \brief Abstract device
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include "device/device.hpp"

#include <sstream>
#include <Poco/Delegate.h>

namespace smartaquarium {

void device::work()
{
    create_connection();
    delegate_all();
    initialize_device();
}

void device::create_connection()
{
    std::string topic;
    MQTTClientFactory::FactoryArguments arguments;
    std::tie(arguments, topic) = load_arguments();

    log_connection_data(arguments, topic);
    auto server_uri = arguments.serverUri;
    auto client_id = arguments.clientId;

    mqtt_client_ = std::move(MQTTClientFactory::CreateMQTTClient<MQTTClientFactory::ClientType::Paho>(std::move(arguments)));
    mqtt_client_->subscribe(std::move(topic), IoT::MQTT::QoS::AT_LEAST_ONCE);
    if (!mqtt_client_->connected()) {
        throw std::runtime_error("Could not connect on server");
    }

    logger().information("MQTT Client is connected at " + server_uri);
    connected_event_ += Poco::delegate(this, &device::on_connect);
    connected_event_.notify(this, client_id);
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

    const auto prefix = commandName() + ".mqtt.";
    auto get_value = [&prefix, this](const std::string& property) { return config().getString(prefix + property); };

    arguments.serverUri = get_value("server") + ":" + get_value("port");
    arguments.clientId = get_value("clientid");
    arguments.options.username = get_value("username");
    arguments.options.password = get_value("password");

    auto topic = get_value("topic");

    return std::make_tuple(arguments, topic);
}

void device::delegate_all()
{
    mqtt_client_->connectionLost += Poco::delegate(this, &device::on_disconnect);
    mqtt_client_->messageArrived += Poco::delegate(this, &device::on_message_arrived);
    mqtt_client_->messageDelivered += Poco::delegate(this, &device::on_message_delivered);
}

} // namespace smartaquarium