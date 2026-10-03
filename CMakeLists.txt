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
    find_package(PkgConfig REQUIRED)

    pkg_check_modules(LIBVLC REQUIRED IMPORTED_TARGET libvlc)
    add_library(libvlc ALIAS PkgConfig::LIBVLC)
endif()

find_package(nlohmann_json CONFIG REQUIRED)
find_package(ftxui CONFIG REQUIRED)

add_executable(muster 
    src/main.cpp
    src/core/app.h
    src/core/app.cpp
)

target_include_directories(muster PRIVATE vendor/libvlcpp)

target_compile_features(muster PRIVATE cxx_std_17)
target_link_libraries(muster PRIVATE 
    libvlc 
    nlohmann_json::nlohmann_json 
    ftxui::ftxui 
    ftxui::dom 
    ftxui::screen
)

add_custom_command(
    TARGET muster
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${VLC_SDK_DIR}/libvlc.dll"
        "${VLC_SDK_DIR}/libvlccore.dll"
        "$<TARGET_FILE_DIR:muster>"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${VLC_SDK_DIR}/plugins"
        "$<TARGET_FILE_DIR:muster>/plugins"
)