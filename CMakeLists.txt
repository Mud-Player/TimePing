cmake_minimum_required(VERSION 3.5)

project(TimePing)

add_subdirectory(SchedulerLib)
add_subdirectory(TimeApp)

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})
