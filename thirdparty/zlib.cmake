message("-- External Project: zlib")
include(FetchContent)

FetchContent_Declare(
    zlib
    GIT_REPOSITORY  https://github.com/husenap/zlib.git
    GIT_TAG         67769180d718b2798b80791fc8362bde81dee017
    SOURCE_DIR      "${FETCHCONTENT_BASE_DIR}/zlib/zlib"
)

set(zlib_BUILD_EXAMPLES ON CACHE BOOL "" FORCE)
set(zlib_FOLDER "thirdparty/zlib" CACHE STRING "" FORCE)

FetchContent_MakeAvailable(zlib)

target_include_directories(zlib SYSTEM PUBLIC
    ${zlib_BINARY_DIR}
    ${zlib_SOURCE_DIR}
    ${zlib_SOURCE_DIR}/..)
