/**
 * \file
 * \brief Launch thermal sensor application
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include <iostream>
#include <Poco/Util/ServerApplication.h>

#include "temperature_sensor/temperature_sensor.hpp"

POCO_SERVER_MAIN(smartaquarium::temperature_sensor)
