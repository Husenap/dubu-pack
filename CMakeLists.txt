cmake_minimum_required(VERSION 3.16)

project("dubu_pack" C CXX)

include("cmake/prevent_in_source_builds.cmake")
include("cmake/standard_project_setup.cmake")

include("cmake/compiler_features.cmake")
include("cmake/compiler_warnings.cmake")

set(${PROJECT_NAME}_FOLDER
    ${PROJECT_NAME}
    CACHE
    STRING
    "The folder that ${PROJECT_NAME} projects will be placed in.")

option(${PROJECT_NAME}_DEPLOYMENT_TESTS
    "If the ${PROJECT_NAME} deployment tests are executed in addition to the dubu-pack library."
    OFF)

option(${PROJECT_NAME}_BUILD_TESTS
    "If the ${PROJECT_NAME} tests are built in addition to the ${PROJECT_NAME} library."
    ON)

include("thirdparty/dubu_serialize.cmake")

add_subdirectory("dubu_pack")
add_subdirectory("dubu_pack_cli")

if(${${PROJECT_NAME}_DEPLOYMENT_TESTS})
    dubu_pack_package(
        ${dubu_pack_SOURCE_DIR}/test/bin/packed
        ${dubu_pack_SOURCE_DIR}/test/bin/assets)
endif()

if(${${PROJECT_NAME}_BUILD_TESTS})
    enable_testing()
    include(GoogleTest)
    include("thirdparty/googletest.cmake")
    add_subdirectory("dubu_pack_test")
endif()
