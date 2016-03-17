/**
 * \file
 * \brief Application library for all modules
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef SMARTAQUARIUM_APP_HPP_
#define SMARTAQUARIUM_APP_HPP_

#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/Application.h>

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
   * \brief Execute main function
   * \param args arguments from stdin
   * \return process code error
   */
    int main(const ArgVec& args);
};
} // namespace smartaquarium

#endif // SMARTAQUARIUM_APP_HPP_
