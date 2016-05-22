/**
 * \file
 * \brief Lighting device
 * \author Uilian Ries <uilianries@gmail.com>
 */

#ifndef SMARTAQUARIUM_LIGHTING_HPP_
#define SMARTAQUARIUM_LIGHTING_HPP_

#include <string>
#include "actuator/actuator.hpp"

namespace smartaquarium {

/**
 * \brief Lighting device
 */
class lighting : public actuator {
public:
    /**
   * \brief Default constructor
   */
    lighting() = default;

private:
    /**
     * \brief Process new data level from the sensor
     * \param level sensor level
     */
    void process_sensor_level(const std::string& level) override;
};

} // namespace smartaquarium

#endif // SMARTAQUARIUM_LIGHTING_HPP_
