set(target_name "dubu_pack")

set(src_precompiled
    "src/precompiled.h")

set(src_dubu_pack
    "src/dubu_pack/package.cpp"
    "src/dubu_pack/package.h"
    "src/dubu_pack/dubu_pack.h")

set(src_files
    ${src_precompiled}
    ${src_packer}
    ${src_dubu_pack})

# Project
add_library(${target_name} STATIC ${src_files})

target_precompile_headers(${target_name} PUBLIC ${src_precompiled})

source_group("src" FILES ${src_dubu_pack})
source_group("src/precompiled" FILES ${src_precompiled})
source_group("src/precompiled" REGULAR_EXPRESSION "cmake_pch\.[ch]xx")

target_include_directories(${target_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

set_target_properties(${target_name} PROPERTIES FOLDER ${DUBUPACK_FOLDER})