#ifndef SCREEN_IMAGE_FILE_WRITER_H
#define SCREEN_IMAGE_FILE_WRITER_H

#include <memory>
#include <vector>

#include "screen/image_event_handler.h"

namespace screen
{

class image_file_writer : public image_event_handler
{
public:

    using ptr       = std::shared_ptr<image_file_writer>;
    using ptr_array = std::vector<ptr>;

public:

    image_file_writer(const std::string& path);

    void write_jpeg_file(const std::string& filename, const ui::image::ptr image);

private: // image_event_handler

    void on_image_received(const std::string& display_name, const ui::image::ptr image) override;

private:

    std::FILE*  file_stream_;
    std::string path_;

};

} // namespace screen

#endif // SCREEN_IMAGE_FILE_WRITER_H
