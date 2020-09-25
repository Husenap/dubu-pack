set(target_name "dubu_pack")

set(src_precompiled
    "src/precompiled.h")

set(src_serializer
    "src/dubu_pack/serializer/Serializer.h")

set(src_packer
    "src/dubu_pack/packer/Unpacker.cpp"
    "src/dubu_pack/packer/Unpacker.h"
    "src/dubu_pack/packer/Packer.cpp"
    "src/dubu_pack/packer/Packer.h")

set(src_file_locator
    "src/dubu_pack/file_locator/IFileLocator.h"
    "src/dubu_pack/file_locator/PackageFileLocator.cpp"
    "src/dubu_pack/file_locator/PackageFileLocator.h"
    "src/dubu_pack/file_locator/FilesystemFileLocator.cpp"
    "src/dubu_pack/file_locator/FilesystemFileLocator.h")

set(src_package
    "src/dubu_pack/package/Package.cpp"
    "src/dubu_pack/package/Package.h")

set(src_dubu_pack
    "src/dubu_pack/Definitions.h"
    "src/dubu_pack/dubu_pack.h")

set(src_files
    ${src_precompiled}
    ${src_serializer}
    ${src_file_locator}
    ${src_packer}
    ${src_package}
    ${src_dubu_pack})

add_library(${target_name} STATIC ${src_files})

target_link_libraries(${target_name}
    compiler_features
    compiler_warnings)

target_precompile_headers(${target_name} PUBLIC ${src_precompiled})

source_group("src" FILES ${src_dubu_pack})
source_group("src/serializer" FILES ${src_serializer})
source_group("src/package" FILES ${src_package})
source_group("src/packer" FILES ${src_packer})
source_group("src/file_locator" FILES ${src_file_locator})
source_group("src/precompiled" FILES ${src_precompiled})
source_group("src/precompiled" REGULAR_EXPRESSION "cmake_pch\.[ch]xx")

target_include_directories(${target_name}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

set_target_properties(${target_name} PROPERTIES FOLDER ${${PROJECT_NAME}_FOLDER})
