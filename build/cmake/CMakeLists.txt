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
    SOURCES
        ${srcs}
    PUBLIC_INCLUDE_DIRECTORIES
        ../../src/${name}/include
    PRIVATE_INCLUDE_DIRECTORIES
        ../../src/${name}/include/${name}
    INSTALL_INCLUDE_DIRECTORIES
        ../../src/${name}/include/${name}
)
