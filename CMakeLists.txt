cmake_minimum_required(VERSION 3.10)
project(steering_wheel VERSION 1.0 DESCRIPTION "C++ package to read, parse, and interpret inputs from the Fanatec DD1 racing wheel" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(MyExecutable main/main.cpp)
include_directories(include)

# Handling libevdev
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBEVDEV REQUIRED libevdev)
include_directories(${LIBEVDEV_INCLUDE_DIRS})
target_link_libraries(MyExecutable PRIVATE ${LIBEVDEV_LIBRARIES})

install(TARGETS MyExecutable DESTINATION bin)
