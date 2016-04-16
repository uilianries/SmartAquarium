/**
 * \file
 * \brief Launch thermal sensor application
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include <iostream>
#include <Poco/Util/ServerApplication.h>

#include "thermal_sensor/thermal_sensor.hpp"

POCO_SERVER_MAIN(smartaquarium::thermal_sensor)