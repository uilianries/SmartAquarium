/**
 * \file
 * \brief Application library for all modules
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef SMARTAQUARIUM_APP_HPP_
#define SMARTAQUARIUM_APP_HPP_

#include <Poco/Util/ServerApplication.h>
#include <Poco/FormattingChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/FileChannel.h>
#include <Poco/AutoPtr.h>
#include <Poco/Path.h>

using Poco::Util::ServerApplication;
using Poco::Util::Application;

namespace smartaquarium {

/**
 * \brief Start a module as a deamon.
 *        Load configuration, handle signals
 *        and provide an entry for each
 *        specialization.
 */
class application : public ServerApplication {
public:
    /**
     * \brief virtual destructor
     */
    ~application() override = default;

protected:
    /**
     * \brief Execute some routine from child class
     */
    virtual void work() = 0;

    /**
     * \brief Get app configuration file path
     */
    Poco::Path get_configuration_file_path() const;

private:
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

    /**
     * \brief Configure internal log to use formatted pattern
     */
    void configure_logger();

    Poco::AutoPtr<Poco::PatternFormatter> pattern_formatter_; /**< Pattern for log */
    Poco::AutoPtr<Poco::FormattingChannel> formatting_channel_; /**< Formatting Channel */
    Poco::AutoPtr<Poco::FileChannel> file_channel_; /**< File Channel */
};
} // namespace smartaquarium

#endif // SMARTAQUARIUM_APP_HPP_
