cmake_minimum_required(VERSION 3.16)

project("dubu_pack" C CXX)

include("cmake/setup.cmake")

include("cmake/compiler_features.cmake")
include("cmake/compiler_warnings.cmake")

set(DUBUPACK_FOLDER
    ${PROJECT_NAME}
    CACHE
    STRING
    "The folder that ${PROJECT_NAME} projects will be placed in.")

option(DUBUPACK_BUILD_TESTS
    "If the ${PROJECT_NAME} tests are built in addition to the dubu-pack library."
    ON)

if(DUBUPACK_BUILD_TESTS)
    add_subdirectory("test")
endif()

add_subdirectory("dubu_pack")