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

    set(VLC_SDK_DIR "" CACHE PATH "Path to extracted VLC SDK (contains sdk/include, sdk/lib)")
    if(NOT VLC_SDK_DIR)
        message(FATAL_ERROR "Set VLC_SDK_DIR to your extracted VLC archive root")
    endif()

    add_library(libvlc SHARED IMPORTED GLOBAL)
    set_target_properties(libvlc PROPERTIES
        IMPORTED_IMPLIB "${VLC_SDK_DIR}/sdk/lib/libvlc.lib"
        IMPORTED_LOCATION "${VLC_SDK_DIR}/sdk/libvlc.dll"
        INTERFACE_INCLUDE_DIRECTORIES "${VLC_SDK_DIR}/sdk/include"
    )
elseif(UNIX AND NOT APPLE)
    find_package(Curses REQUIRED)
    find_package(PkgConfig REQUIRED)

    pkg_check_modules(LIBVLC REQUIRED IMPORTED_TARGET libvlc)
    add_library(libvlc ALIAS PkgConfig::LIBVLC)

    set(MUSTER_CURSES Curses::Curses)
endif()

add_executable(muster 
    src/main.cpp
    src/core/app.h
    src/core/app.cpp
)

target_include_directories(muster PRIVATE vendor/libvlcpp)

target_compile_features(muster PRIVATE cxx_std_17)
target_link_libraries(muster PRIVATE ${MUSTER_CURSES} libvlc)

file(COPY ${VLC_SDK_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})