/**
 * \file
 * \brief Launch sensor application
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include <iostream>
#include <Poco/Util/ServerApplication.h>

#include "sensor/sensor.hpp"

POCO_SERVER_MAIN(smartaquarium::sensor)