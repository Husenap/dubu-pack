set(target_name "dubu-pack")

set(src_packer
    "src/dubu-pack/packer/packer.cpp"
    "src/dubu-pack/packer/packer.h")

set(src_dubu_pack
    "src/dubu-pack/dubu-pack.h")

set(src_files
    ${src_packer}
    ${src_dubu_pack})

# Project
add_library(${target_name} STATIC ${src_files})

source_group("src" FILES ${src_dubu_pack})
source_group("src/packer" FILES ${src_packer})

target_include_directories(${target_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

set_target_properties(${target_name} PROPERTIES FOLDER ${DUBUPACK_FOLDER})