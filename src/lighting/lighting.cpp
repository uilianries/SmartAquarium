/**
 * \file
 * \brief Lighting device
 * \author Uilian Ries <uilianries@gmail.com>
 */

#include "lighting/lighting.hpp"

namespace smartaquarium {

void lighting::process_sensor_level(const std::string& level)
{
    auto dlevel = std::stod(level);
    std::ostringstream oss;

    oss << commandName() << ": Received sensor event: " << dlevel;
    if ((dlevel < get_actuator_options().level.min) and (get_current_level() == bbb::gpio::pin_level::high)) {
        oss << " - under minimal temperature: " << get_actuator_options().level.min;
        output_on();
    }
    else if ((dlevel > get_actuator_options().level.max) and (get_current_level() == bbb::gpio::pin_level::low)) {
        oss << " - over middle temperature: " << get_actuator_options().level.max;
        output_off();
    }

    logger().debug(oss.str());
}

} // namespace smartaquarium