/**
 * \file
 * \brief Create and MQTT client the the Server
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef SMARTAQUARIUM_MQTT_TASK_HPP_
#define SMARTAQUARIUM_MQTT_TASK_HPP_

#include <memory>

#include "IoT/MQTT/MQTTClient.h"
#include "IoT/MQTT/MQTTClientFactory.h"

#include "task.hpp"

namespace smartaquarium {

/**
 * \brief Start MQTT connection
 */
class mqtt_task : public task {
public:
    /**
         * \brief create MQTT Client and connect on server
         * \param _client Client the be created
         * \param _arguments options to create the client
         * \param _topic Initial topic to listen
         * \param _logger logger handle
         */
    mqtt_task(std::unique_ptr<IoT::MQTT::MQTTClient>& _client,
        IoT::MQTT::MQTTClientFactory::FactoryArguments&& _arguments,
        std::string&& _topic,
        Poco::Logger& _logger);

private:
    /**
         * \brief Create connection with MQTT server
         */
    void create_connection();

    /** Client handle */
    std::unique_ptr<IoT::MQTT::MQTTClient>& client_;
    /** Client Arguments */
    IoT::MQTT::MQTTClientFactory::FactoryArguments arguments_;
    /** Client topic */
    std::string topic_;
};
} // namespace smartaquarium

#endif // SMARTAQUARIUM_MQTT_TASK_HPP_
