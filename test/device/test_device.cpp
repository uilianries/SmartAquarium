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

#include "util/util.hpp"

namespace smartaquarium {
namespace test {

    void test_device::SetUp()
    {
        constexpr auto xml_config_file = "dummy_device.xml";

        xml_configuration_.assign(new Poco::Util::XMLConfiguration(xml_config_file));
        auto broker_address = xml_configuration_->getString("dummy_device.mqtt.server") + ":" + xml_configuration_->getString("dummy_device.mqtt.port");

        Poco::AutoPtr<Poco::Util::SystemConfiguration> system_configuration(new Poco::Util::SystemConfiguration());
        auto current_pid = system_configuration->getInt("system.pid");
        xml_configuration_->setInt("dummy_device.pid", current_pid);
        xml_configuration_->save(xml_config_file);

        // TODO(uilianries@gmail.com): move gtest main to util

        mqtt_client_ = IoT::MQTT::MQTTClientFactory::CreateMQTTClient<IoT::MQTT::MQTTClientFactory::ClientType::Paho>({ broker_address, "TestDevice", {} });
        mqtt_client_->messageArrived += Poco::delegate(this, &test_device::receive_message);

        signal_handler_.reset(new signal_handler(SIGUSR1));
        signal_handler_->on_signal_arrived += Poco::delegate(this, &test_device::on_signal);

        Poco::Path dummy_process_path = "test/device/dummy_device";
        process_h_ = launch_process(dummy_process_path);
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

    void test_device::on_signal(const int& sig)
    {
        if (sig == SIGUSR1) {
            dummy_connected_ = true;
        }
    }

    TEST_F(test_device, SendAndWait)
    {
        mqtt_client_->subscribe(xml_configuration_->getString("dummy_device.mqtt.target"), IoT::MQTT::QoS::AT_LEAST_ONCE);
        ASSERT_TRUE(mqtt_client_->connected());

        ASSERT_TRUE(wait_for(std::chrono::seconds(5), [this]() { return dummy_connected_; }));

        const auto& client_id = xml_configuration_->getString("dummy_device.mqtt.clientid");
        mqtt_client_->publish(xml_configuration_->getString("dummy_device.mqtt.topic"), client_id, IoT::MQTT::QoS::AT_LEAST_ONCE);

        ASSERT_TRUE(wait_for(std::chrono::seconds(5), [this]() { return message_received_; }));

        ASSERT_EQ(client_id, arrived_event_.message.payload);
    }

} // namespace test
} // namespace smartaquarium
