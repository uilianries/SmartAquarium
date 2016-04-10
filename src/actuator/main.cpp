/**
 * \file
 * \brief Launch actuator application
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include <iostream>
#include <Poco/Util/ServerApplication.h>

#include "actuator/actuator.hpp"

POCO_SERVER_MAIN(smartaquarium::actuator)