/**
 * \file
 * \brief Application library for all modules
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef SMARTAQUARIUM_APP_HPP_
#define SMARTAQUARIUM_APP_HPP_

namespace smartaquarium {

/**
    * \brief Start a module as a deamon.
    *        Load configuration, handle signals
    *        and provide an entry for each
    *        specialization.
    */
class application {

public:
    /**
      * \brief For now, do nothing
      */
    application();
};
} // namespace smartaquarium

#endif // SMARTAQUARIUM_APP_HPP_
