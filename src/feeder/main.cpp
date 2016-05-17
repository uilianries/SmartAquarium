/**
 * \file
 * \brief Launch feeder application
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include <iostream>
#include <Poco/Util/ServerApplication.h>

#include "feeder/feeder.hpp"

POCO_SERVER_MAIN(smartaquarium::feeder)