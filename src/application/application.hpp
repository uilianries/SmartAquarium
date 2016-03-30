/**
 * \file
 * \brief Application library for all modules
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef SMARTAQUARIUM_APP_HPP_
#define SMARTAQUARIUM_APP_HPP_

#include <string>
#include <memory>

#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/Application.h>
#include <Poco/TaskManager.h>
#include <Poco/FormattingChannel.h>
#include <Poco/AutoPtr.h>
#include <Poco/PatternFormatter.h>

#include "IoT/MQTT/MQTTClient.h"

using Poco::Util::ServerApplication;
using Poco::Util::Application;
using IoT::MQTT::MQTTClient;

namespace smartaquarium {

/**
 * \brief Start a module as a deamon.
 *        Load configuration, handle signals
 *        and provide an entry for each
 *        specialization.
 */
class application : public ServerApplication {

    /**
   * \brief Execute main function
   * \param args arguments from stdin
   * \return process code error
   */
    int main(const ArgVec& args) override;

    /**
    * \brief Load config file
    * \param self ownership
    */
    void initialize(Application& self) override;

private:
    /**
     * \brief Launch task to create the MQTT client
     */
    void launch_mqtt_client(Poco::TaskManager& _task_manager);

    /**
     * \brief Configure internal log to use formatted pattern
     */
    void configure_logger();

    std::unique_ptr<MQTTClient> mqtt_client_; /**< MQTT Client handle */
    Poco::AutoPtr<Poco::PatternFormatter> pattern_formatter_; /**< Pattern for log */
    Poco::AutoPtr<Poco::FormattingChannel> formatting_channel_; /**< Formmatin Channel */
};
} // namespace smartaquarium

#endif // SMARTAQUARIUM_APP_HPP_
