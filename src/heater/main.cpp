/**
 * \file
 * \brief Launch heater application
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include <iostream>
#include <Poco/Util/ServerApplication.h>

#include "heater/heater.hpp"

POCO_SERVER_MAIN(smartaquarium::heater)