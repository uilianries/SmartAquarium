/**
 * \file
 * \brief Unit Test for Device
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef SMARTAQUARIUM_TEST_DEVICE_HPP_
#define SMARTAQUARIUM_TEST_DEVICE_HPP_

#include <memory>

#include <gtest/gtest.h>
#include <IoT/MQTT/MQTTClientFactory.h>
#include <IoT/MQTT/MQTTClient.h>
#include <Poco/AutoPtr.h>
#include <Poco/Util/XMLConfiguration.h>
#include <Poco/Process.h>

#include "util/signal_handler.hpp"

namespace smartaquarium {
namespace test {

    /**
     * \brief Execute Device unit test
     */
    class test_device : public ::testing::Test {
        /**
         * \brief Launch dummy device
         */
        void SetUp() override;

        /**
         * \brief kill dummy device
         */
        void TearDown() override;

    protected:
        /**
         * \brief Receives message from dummy application
         */
        void receive_message(const IoT::MQTT::MessageArrivedEvent& event);

        /**
         * \brief Connect on broker
         */
        void connect();

        /**
         * \brief Connect on broker and send a message
         * \param payload Message to be sent
         */
        void publish(const std::string& payload);

        /**
         * \brief Wait for an answer from the dummy process
         * \param expected_answer To equate with the payload
         */
        void wait_for_publish_answer(const std::string& expected_answer);

        /**
         * \brief Request for broker to MQTT client reset
         */
        void disconnect();

        /**
         * \brief Wait for disconnect event, after send request
         */
        void wait_for_disconnect();

    private:
        /**
         * \brief Receive signal from dummy process when connect on broker
         * \param sig POSIX signal id
         */
        void on_signal(const int& sig);

        std::unique_ptr<signal_handler> signal_handler_; /**> receives POSIX signal */
        std::unique_ptr<IoT::MQTT::MQTTClient> mqtt_client_; /**< MQTT client that sends message to dummy*/
        std::unique_ptr<Poco::ProcessHandle> process_h_; /**< dummy process handler */
        Poco::AutoPtr<Poco::Util::XMLConfiguration> xml_configuration_; /** Load XML file */
        IoT::MQTT::MessageArrivedEvent arrived_event_; /**< Event to be treated */
        bool dummy_connected_ = false; /**< sentinel to broker connection */
        bool message_received_ = false; /**< Message from broker was received*/
    };

} // namespace test
} // namespace smartaquarium

#endif // SMARTAQUARIUM_TEST_DEVICE_HPP_
