cmake_minimum_required(VERSION 3.16)

project("dubu-pack" C CXX)

include("cmake/setup.cmake")

include("cmake/compiler_features.cmake")
include("cmake/compiler_warnings.cmake")

option(
    DUBUPACK_BUILD_TESTS
    "If the dubu-pack tests are built in addition to the dubu-pack library."
    ON)

if(DUBUPACK_BUILD_TESTS)
    add_subdirectory("test")
endif()

add_subdirectory("dubu-pack")