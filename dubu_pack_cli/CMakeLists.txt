set(target_name "dubu_pack_cli")

add_executable(${target_name} "src/main.cpp")

target_link_libraries(${target_name}
    compiler_features
    compiler_warnings
    dubu_pack)

set_target_properties(${target_name} PROPERTIES FOLDER ${PROJECT_NAME}_FOLDER)

function(dubu_pack_package)
    add_custom_target(
        dubu_pack_packer ALL
        COMMAND dubu_pack_cli ${ARGV})
endfunction()