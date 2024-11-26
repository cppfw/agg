cmake_minimum_required(VERSION 3.10)

include(GNUInstallDirs)

set(name agg)

project(${name})

# find_package(utki CONFIG REQUIRED)

# non-recursive
file(GLOB srcs "../src/${name}/src/*.cpp")

add_library(
    ${name}
    STATIC
    ${srcs}
)

target_compile_features(${name} PUBLIC cxx_std_17)
set_target_properties(${name} PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(${name} PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(
    ${name}
    INTERFACE
        $<BUILD_INTERFACE:>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../src/${name}/include/${name}"
)

# target_link_libraries(
#     ${name}
#     PUBLIC
#         utki::utki
# )

# install library header files preserving directory hierarchy
install(
    DIRECTORY
        "${CMAKE_CURRENT_SOURCE_DIR}/../src/${name}/include/${name}"
    DESTINATION
        "${CMAKE_INSTALL_INCLUDEDIR}"
    FILES_MATCHING PATTERN
        "*.h"
)

install(
    TARGETS
        ${name}
    EXPORT # generate cmake configs
        ${name}-config
)

# install cmake configs
install(
    EXPORT
        ${name}-config
    FILE
        ${name}-config.cmake
    DESTINATION
        ${CMAKE_INSTALL_DATAROOTDIR}/${name}
    NAMESPACE
        ${name}::
)
