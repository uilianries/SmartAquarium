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
    virtual ~application() = default;

protected:
    /**
     * \brief Execute some routine from child class
     */
    virtual void work() = 0;

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
    Poco::AutoPtr<Poco::FormattingChannel> formatting_channel_; /**< Formmatin Channel */
};
} // namespace smartaquarium

#endif // SMARTAQUARIUM_APP_HPP_
