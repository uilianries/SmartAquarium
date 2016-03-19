/**
 * \file
 * \brief Execute Unit Test for application
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include <iostream>

#include "application/application.hpp"

/**
 * \brief Run application
 */
class test_application : public smartaquarium::application
{
    protected:
        /**
         * \brief Do nothing
         */
        void execute() override
        {
            std::cout << "F00B4R" << std::endl;
        }
};
