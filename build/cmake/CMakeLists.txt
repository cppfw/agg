cmake_minimum_required(VERSION 3.20)

set(name agg)
project(${name})

# !!! find_package must go after project() declaration !!!
# Otherwise VCPKG does not set the CMAKE_PREFIX_PATH to find packages.
find_package(myci CONFIG REQUIRED)

set(srcs)
myci_add_source_files(srcs
    DIRECTORY
        ../../src/${name}/src
)

myci_declare_library(${name}
    # TODO: fix warnings if any (for MSVC?)
    NO_WARNINGS_AS_ERRORS
    SOURCES
        ${srcs}
    PUBLIC_INCLUDE_DIRECTORIES
        ../../src/${name}/include
    PRIVATE_INCLUDE_DIRECTORIES
        ../../src/${name}/include/${name}
    INSTALL_INCLUDE_DIRECTORIES
        ../../src/${name}/include/${name}
)

if(MSVC)
    # MSVS issues warnings about "unsafe" functions like fopen().
    # Suppress these warnings because the code is legacy and cannot be easily maintained.
    target_compile_definitions(${name} PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
