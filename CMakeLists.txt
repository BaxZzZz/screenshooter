cmake_minimum_required(VERSION 2.8)

project(screenshooter)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

include_directories(src)

SET(HEADERS
    src/ui/display.h
    src/ui/image.h
    src/screen/shooter.h
    src/screen/monitor.h
    src/screen/image_event_handler.h
    src/screen/jpeg_file_writer.h
    src/process/signal_handler.h
    src/process/daemonizer.h
)

SET(SOURCES
    src/ui/display.cpp
    src/ui/image.cpp
    src/screen/shooter.cpp
    src/screen/monitor.cpp
    src/screen/jpeg_file_writer.cpp
    src/process/signal_handler.cpp
    src/process/daemonizer.cpp
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries (${PROJECT_NAME} X11 pthread jpeg)
