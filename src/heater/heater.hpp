/**
 * \file
 * \brief Heater device
 * \author Uilian Ries <uilianries@gmail.com>
 */

#ifndef SMARTAQUARIUM_HEATER_HPP_
#define SMARTAQUARIUM_HEATER_HPP_

#include "actuator/actuator.hpp"

namespace smartaquarium {

/**
 * \brief Heater device
 */
class heater : public actuator {
public:
    /**
   * \brief Default constructor
   */
    heater() = default;

private:
    /**
     * \brief Process new data level from the sensor
     * \param level sensor level
     */
    void process_sensor_level(const std::string& level) override;
};

} // namespace smartaquarium

#endif // SMARTAQUARIUM_HEATER_HPP_
