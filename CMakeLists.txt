cmake_minimum_required(VERSION 3.10)
project(PyLauncher CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

add_executable(py-launcher
    src/main.cpp
    src/window.cpp
    src/installer.cpp
)

target_include_directories(py-launcher PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_directories(py-launcher PRIVATE ${GTKMM_LIBRARY_DIRS})
target_link_libraries(py-launcher PRIVATE ${GTKMM_LIBRARIES})
target_compile_options(py-launcher PRIVATE ${GTKMM_CFLAGS_OTHER})