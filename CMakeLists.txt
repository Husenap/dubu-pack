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

option(DUBUPACK_DEPLOYMENT_TESTS
    "If the ${PROJECT_NAME} deployment tests are executed in addition to the dubu-pack library."
    OFF)

option(DUBUPACK_BUILD_TESTS
    "If the ${PROJECT_NAME} tests are built in addition to the dubu-pack library."
    ON)

add_subdirectory("dubu_pack")
add_subdirectory("dubu_pack_cli")

if(DUBUPACK_DEPLOYMENT_TESTS)
    dubu_pack_package(
        ${dubu_pack_SOURCE_DIR}/test/bin/packed
        ${dubu_pack_SOURCE_DIR}/test/bin/assets)
endif()

if(DUBUPACK_BUILD_TESTS)
    enable_testing()
    include(GoogleTest)
    include("thirdparty/googletest.cmake")
    add_subdirectory("test")
endif()
