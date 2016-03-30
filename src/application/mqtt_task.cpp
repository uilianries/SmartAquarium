/**
 * \file
 * \brief Create and MQTT client the the Server
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "application/mqtt_task.hpp"

#include <functional>
#include <stdexcept>

namespace smartaquarium {
mqtt_task::mqtt_task(std::unique_ptr<IoT::MQTT::MQTTClient>& _client,
    IoT::MQTT::MQTTClientFactory::FactoryArguments&& _arguments,
    std::string&& _topic,
    Poco::Logger& _logger)
    : task("LaunchMQTTClient", std::bind(&mqtt_task::create_connection, this), _logger)
    , client_(_client)
    , arguments_(std::move(_arguments))
    , topic_(std::move(_topic))
{
    if (topic_.empty()) {
        throw std::invalid_argument("Topic could not be empty");
    }
}

void mqtt_task::create_connection()
{
    using IoT::MQTT::MQTTClientFactory;
    using IoT::MQTT::MQTTClientFactory;

    client_ = std::move(MQTTClientFactory::CreateMQTTClient<MQTTClientFactory::ClientType::Paho>(arguments_));
    client_->subscribe(topic_, IoT::MQTT::QoS::AT_LEAST_ONCE);
    if (!client_->connected()) {
        throw std::runtime_error("Could not connect on server");
    }

    logger_.information("MQTT Client is connected at " + arguments_.serverUri);
}
}
