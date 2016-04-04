/**
 * \file
 * \brief Abstract device
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef SMARTAQUARIUM_DEVICE_HPP_
#define SMARTAQUARIUM_DEVICE_HPP_

#include <memory>
#include <tuple>

#include <Poco/TaskManager.h>
#include <IoT/MQTT/MQTTClient.h>
#include <IoT/MQTT/MQTTClientFactory.h>

#include "application/application.hpp"

using IoT::MQTT::MQTTClient;
using IoT::MQTT::MQTTClientFactory;

namespace smartaquarium {
/**
     * \brief Abstract device
     */
class device : public application {
public:
    /**
         * \brief Virtual destructor
         */
    virtual ~device(){};

protected:
    /**
         * \brief Treat disconnection event
         * \param event disconnection cause
         */
    virtual void on_disconnect(const IoT::MQTT::ConnectionLostEvent& event) = 0;

    /**
         * \brief Treat message delived event
         * \param event message token
         */
    virtual void on_message_delivered(const IoT::MQTT::MessageDeliveredEvent& event) = 0;

    /**
         * \brief Treat message arrived from broker
         * \param event message paylod
         */
    virtual void on_message_arrived(const IoT::MQTT::MessageArrivedEvent& event) = 0;

private:
    std::unique_ptr<MQTTClient> mqtt_client_; /**< MQTT Client handle */

    /**
        * \brief Connect MQTT client
        */
    void work() override;

    /**
         * \brief Delegate all virtual functions to treat an event
         */
    void delegate_all();

    /**
         * \brief Start MQTT client
         */
    void create_connection();

    /**
         * \brief Log for debug
         * \param arguments data to be logged
         * \param topic Topic to subscribe
         */
    void log_connection_data(const MQTTClientFactory::FactoryArguments& arguments, const std::string& topic);

    /**
         * \brief Load device arguments
         * \return Arguments from config file
         */
    std::tuple<MQTTClientFactory::FactoryArguments, std::string> load_arguments();
};
} // namespace smartaquarium

#endif //SMARTAQUARIUM_DEVICE_HPP
