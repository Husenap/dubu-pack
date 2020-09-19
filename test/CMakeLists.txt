set(target_name "dubu_pack_test")

set(src_unit
    "unit/test.cpp")

add_executable(${target_name} ${src_unit})

target_link_libraries(${target_name}
    gtest
    gmock
    gmock_main
    dubu_pack)

set_target_properties(${target_name} PROPERTIES FOLDER ${DUBUPACK_FOLDER}/test)

add_custom_command(
    TARGET ${target_name} POST_BUILD COMMAND
    ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/bin/
    $<TARGET_FILE_DIR:${target_name}>)

gtest_discover_tests(${target_name}
    WORKING_DIRECTORY $<TARGET_FILE_DIR:${target_name}>
    VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${target_name}>)