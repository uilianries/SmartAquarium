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
#include <Poco/URI.h>
#include <IoT/MQTT/MQTTClient.h>
#include <IoT/MQTT/MQTTClientFactory.h>
#include <iostream>

#include "application/application.hpp"

using IoT::MQTT::MQTTClient;
using IoT::MQTT::MQTTClientFactory;

namespace smartaquarium {

/**
 * \brief Options load from xml
 */
struct device_options {

    /**
     * \brief MQTT client options
     */
    struct mqtt_options {
        Poco::URI server; /**< Broker address */
        std::string port; /**< Broker port */
        std::string client_id; /**< MQTT client id */
        std::string username; /**< User name for broker authentication */
        std::string password; /**< Password for broker authentication */
        std::string topic; /**< Initial client topic */
    };

    mqtt_options mqtt; /**< MQTT client options member */
    std::string pin; /**< GPIO pin */
};

/**
 * \brief Abstract device
 */
class device : public application {
public:
    /**
     * \brief default constructor
     */
    device() = default;
    /**
     * \brief Virtual destructor
     */
    ~device() override = default;

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

    /**
     * \brief Send connected signal
     * \param event placeholder
     */
    virtual void on_connect(const IoT::MQTT::ConnectionDoneEvent& event) = 0;

    /**
     * \brief Execute the initial configuration
     */
    virtual void initialize_device() = 0;

    /**
     * \brief Retrieve MQTT client
     * \return MQTT client instance
     */
    MQTTClient& mqtt_client();

    /**
     * \brief Get configuration options
     * \return Options load from config xml
     */
    const smartaquarium::device_options& device_options() const;

    /**
     * \brief Check if options is valid and get the value.
     *        If the option is invalid, then throw invalid_argument
     * \param option Configuration option in config file
     * \return option value
     */
    std::string get_config(const std::string& option) const;

private:
    /**
    * \brief Connect MQTT client
    */
    void work() override;

    /**
     * \brief Delegate all virtual functions to treat an event
     */
    void delegate_all();

    /**
     * \brief Create MQTT client
     */
    void create_client();

    /**
     * \brief Load internal options
     */
    void load_options();

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

    std::unique_ptr<MQTTClient> mqtt_client_; /**< MQTT Client handle */
    smartaquarium::device_options device_options_; /**< Internal config */
};
} // namespace smartaquarium

#endif //SMARTAQUARIUM_DEVICE_HPP
