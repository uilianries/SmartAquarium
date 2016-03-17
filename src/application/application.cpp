/**
 * \file
 * \brief Application library for all modules
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "application.hpp"

#include <tuple>

namespace smartaquarium {

int application::main(const ArgVec& args)
{
    std::ignore = args;

    return Poco::Util::Application::EXIT_OK;
}

} // namespace smartaquarium
