/**
 * \file
 * \brief Execute Unit Test for application
 * \author Uilian Ries <uilianries@gmail.com>
 */
#include "application/application.hpp"

/**
 * \brief Run application
 */
class dummy_application : public smartaquarium::application {
protected:
    /**
     * \brief Do nothing
     */
    void execute() override
    {
    }
};