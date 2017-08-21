#ifndef SCREEN_MONITOR_H
#define SCREEN_MONITOR_H

#include <unordered_map>

#include "screen/shooter.h"
#include "screen/image_event_handler.h"

namespace screen
{

/*!
 * \brief Class for monitoring sreenshots from different dispays of active users
 */
class monitor
{

public:

    ~monitor();

    /*!
     * \brief Method of adding monitoring of user's display
     * \param [in] display_name - dispaly name
     * \param event_handler     - handler of images
     */
    void add_display(const std::string& display_name, image_event_handler& event_handler);

    /*!
     * \brief Method of deletion
     * \param [in] display_name - display name
     */
    void remove_display(const std::string& display_name);

    /*!
     * \brief Method of deletion of everything
     */
    void remove_all();

private:

    using shooter_table = std::unordered_map<std::string, shooter::ptr>;

private:

    shooter_table shooters_;

};

} // namespace screen

#endif // SCREEN_MONITOR_H
