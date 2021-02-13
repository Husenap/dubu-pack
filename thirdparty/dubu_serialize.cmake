message("-- External Project: dubu_serialize")
include(FetchContent)

FetchContent_Declare(
    dubu_serialize
    GIT_REPOSITORY  https://github.com/Husenap/dubu-serialize.git
    GIT_TAG         v1.2
)

set(dubu_serialize_BUILD_TESTS OFF)
set(dubu_serialize_FOLDER "thirdparty/dubu_serialize" CACHE STRING "" FORCE)

FetchContent_MakeAvailable(dubu_serialize)