#ifndef SCREEN_SHOOTER_H
#define SCREEN_SHOOTER_H

#include <memory>
#include <thread>
#include <atomic>
#include <vector>

#include "ui/display.h"
#include "screen/image_event_handler.h"

namespace screen
{

/*!
 * \brief Class for catching screenshots of user display
 */
class shooter
{

public:

    using ptr       = std::shared_ptr<shooter>;
    using ptr_array = std::vector<ptr>;

public:

    ~shooter();

    /*!
     * \brief Method for starting catching screenshots
     * \param [in] display_name  - display name
     * \param [in] event_handler - handler of images
     */
    void start(const std::string& display_name, image_event_handler& event_handler);

    /*!
     * \brief Method for stopping catching
     */
    void stop();

private:

    void run();

private:

    std::atomic<bool>    is_started_ { false };
    ui::display          display_;
    std::thread          worker_;
    image_event_handler* even_handler_ = nullptr;

};

} // namespace screen

#endif // SCREEN_SHOOTER_H
