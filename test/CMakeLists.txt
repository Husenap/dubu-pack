set(target_name "dubu-pack-test")

include("${dubu-pack_SOURCE_DIR}/thirdparty/gtest.cmake")

set(src_unit
    "unit/test.cpp")

add_executable(${target_name} ${src_unit})

target_link_libraries(${target_name} gtest_main)

set_target_properties(${target_name} PROPERTIES FOLDER ${DUBUPACK_FOLDER}/test)

gtest_discover_tests(${target_name})