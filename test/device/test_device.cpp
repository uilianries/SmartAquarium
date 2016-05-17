/**
 * \file
 * \brief Unit Test for Device
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "test_device.hpp"

#include <chrono>
#include <Poco/Delegate.h>
#include <Poco/Logger.h>
#include <Poco/Path.h>
#include <Poco/File.h>
#include <Poco/Util/SystemConfiguration.h>
#include <unordered_map>

#include "util/util.hpp"

namespace smartaquarium {
namespace test {

    void test_device::SetUp()
    {
        constexpr auto xml_config_file = "/etc/smartaquarium/dummy_device.xml";

        xml_configuration_.assign(new Poco::Util::XMLConfiguration(xml_config_file));
        auto broker_address = xml_configuration_->getString("dummy_device.mqtt.server") + ":" + xml_configuration_->getString("dummy_device.mqtt.port");

        // TODO(uilianries@gmail.com): move gtest main to util

        mqtt_client_ = IoT::MQTT::MQTTClientFactory::CreateMQTTClient<IoT::MQTT::MQTTClientFactory::ClientType::Paho>({ broker_address, "TestDevice", {} });
        mqtt_client_->messageArrived += Poco::delegate(this, &test_device::receive_message);
        connect();

        Poco::Path dummy_process_path = "test/device/dummy_device";
        process_h_ = launch_process(dummy_process_path);
        ASSERT_NE(0, process_h_->id());
    }

    void test_device::TearDown()
    {
        Poco::Process::requestTermination(process_h_->id());
        process_h_->wait();
    }

    void test_device::receive_message(const IoT::MQTT::MessageArrivedEvent& event)
    {
        message_received_ = true;
        arrived_event_ = event;
    }

    void test_device::connect()
    {
        auto topic = xml_configuration_->getString("dummy_device.mqtt.target");
        mqtt_client_->subscribe(topic, IoT::MQTT::QoS::AT_LEAST_ONCE);
        ASSERT_TRUE(mqtt_client_->connected());
    }

    void test_device::publish(const std::string& payload)
    {
        mqtt_client_->publish(xml_configuration_->getString("dummy_device.mqtt.topic"), payload, IoT::MQTT::QoS::AT_LEAST_ONCE);
    }

    void test_device::wait_for_publish_answer(const std::string& expected_answer)
    {
        ASSERT_TRUE(wait_for(std::chrono::seconds(5), [this]() { return message_received_; }));
        message_received_ = false;
        ASSERT_EQ(expected_answer, arrived_event_.message.payload);
    }

    void test_device::disconnect()
    {
        publish("disconnect");
    }

    void test_device::wait_for_disconnect()
    {
        ASSERT_TRUE(wait_for(std::chrono::seconds(5), [this]() { return message_received_; }));
        message_received_ = false;
        const auto& pin = xml_configuration_->getString("dummy_device.pin");
        ASSERT_EQ(pin, arrived_event_.message.payload);
    }

    void test_device::wait_for_dummy_device_connection()
    {
        ASSERT_TRUE(wait_for(std::chrono::seconds(5), [this]() { return message_received_; }));
        message_received_ = false;
        const auto& client_id = xml_configuration_->getString("dummy_device.mqtt.clientid");
        ASSERT_EQ(client_id, arrived_event_.message.payload);
    }

    TEST_F(test_device, ConnectReceiveSendClose)
    {
        wait_for_dummy_device_connection();
        publish(__DATE__);
        wait_for_publish_answer(__DATE__);
        disconnect();
        wait_for_disconnect();
    }

} // namespace test
} // namespace smartaquarium
