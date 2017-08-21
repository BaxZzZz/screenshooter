#ifndef SCREEN_JPEG_FILE_WRITER_H
#define SCREEN_JPEG_FILE_WRITER_H

#include <memory>
#include <vector>

#include "screen/image_event_handler.h"

namespace screen
{

/*!
 * \brief Class of writing image to file in jpeg format
 */
class jpeg_file_writer : public image_event_handler
{
public:

    using ptr       = std::shared_ptr<jpeg_file_writer>;
    using ptr_array = std::vector<ptr>;

public:

    /*!
     * \brief Constructor
     * \param [in] path - path for writing files
     */
    jpeg_file_writer(const std::string& path);

    /*!
     * \brief Method for writing image to file
     * \param [in] filename - filename with full path
     * \param [in] image    - image pointer
     */
    void write(const std::string& filename, const ui::image::ptr image);

private: // image_event_handler

    void on_image_received(const std::string& display_name, const ui::image::ptr image) override;

private:

    std::string path_;

};

} // namespace screen

#endif // SCREEN_JPEG_FILE_WRITER_H
