cmake_minimum_required(VERSION 3.16)

project(muster)

if(NOT DEFINED VCPKG_TARGET_TRIPLET)
    message(FATAL_ERROR
        "vcpkg toolchain is not active (VCPKG_TARGET_TRIPLET undefined).\n"
        "Delete this build directory and reconfigure with:\n"
        "  cmake -S . -B build "
        "-DCMAKE_TOOLCHAIN_FILE=<vcpkg-root>/scripts/buildsystems/vcpkg.cmake")
endif()

if(WIN32)
    find_package(unofficial-pdcurses CONFIG REQUIRED)
    set(MUSTER_CURSES unofficial::pdcurses::pdcurses)
else()
    find_package(Curses REQUIRED)
    set(MUSTER_CURSES Curses::Curses)
endif()

add_executable(muster 
    src/main.cpp
    src/core/app.h
    src/core/app.cpp
)

target_compile_features(muster PRIVATE cxx_std_17)
target_link_libraries(muster PRIVATE ${MUSTER_CURSES})