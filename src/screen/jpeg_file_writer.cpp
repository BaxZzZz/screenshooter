#include <sstream>
#include <iomanip>
#include <chrono>
#include <jpeglib.h>

#include "screen/image_file_writer.h"

namespace screen
{

const std::string TIME_FORMAT = "%Y-%m-%d_%H:%M:%S";

namespace
{

std::string get_current_time_as_string()
{
    using namespace std::chrono;
    auto now      = system_clock::now();
    auto ms       = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
    auto datetime = system_clock::to_time_t(now);

    std::ostringstream oss;
    oss << std::put_time(std::localtime(&datetime), TIME_FORMAT.c_str());
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

    return  oss.str();
}

} // namespace


image_file_writer::image_file_writer(const std::string& path) :
    path_(path)
{

}

void image_file_writer::write_jpeg_file(const std::string& filename, const ui::image::ptr image)
{
    if (filename.empty())
    {
        throw std::runtime_error("empty filename");
    }

    file_stream_ = std::fopen(filename.c_str(), "wb");

    if (file_stream_ == nullptr)
    {
        throw std::runtime_error("Failed to open output file" + filename);
    }

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr       jerr;
    JSAMPROW row_pointer;

    char* buffer = static_cast<char*>(malloc(sizeof(char) * 3 * image->get_width() *
                                             image->get_height()));

    for (int y = 0; y < image->get_height(); ++y)
    {
        for (int x = 0; x < image->get_width(); ++x)
        {
            auto pixel = image->get_pixel(x,y);
            buffer[y*image->get_width()*3+x*3+0] = (char)(pixel>>16);
            buffer[y*image->get_width()*3+x*3+1] = (char)((pixel&0x00ff00)>>8);
            buffer[y*image->get_width()*3+x*3+2] = (char)(pixel&0x0000ff);
        }
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, file_stream_);

    cinfo.image_width      = image->get_width();
    cinfo.image_height     = image->get_height();
    cinfo.input_components = 3;
    cinfo.in_color_space   = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 85, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    while (cinfo.next_scanline < cinfo.image_height)
    {
        row_pointer = (JSAMPROW) &buffer[cinfo.next_scanline
                      *(image->get_depth()>>3)*image->get_width()];
        jpeg_write_scanlines(&cinfo, &row_pointer, 1);
    }

    free(buffer);
    jpeg_finish_compress(&cinfo);
    fclose(file_stream_);
}

void image_file_writer::on_image_received(const std::string& display_name,
                                          const ui::image::ptr image)
{
    auto filename = path_+ '/' + display_name + '-' + get_current_time_as_string() + ".jpeg";
    write_jpeg_file(filename, image);
}

} // namespace screen
