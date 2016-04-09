/**
 * \file
 * \brief Execute Unit Test for application
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "application/dummy_application.hpp"
#include <iostream>
#include <Poco/Util/ServerApplication.h>

/**
 * \brief Execute dummy application
 */
POCO_SERVER_MAIN(smartaquarium::test::dummy_application)
