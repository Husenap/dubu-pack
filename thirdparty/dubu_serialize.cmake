message("-- External Project: dubu_serialize")
include(FetchContent)

FetchContent_Declare(
    dubu_serialize
    GIT_REPOSITORY  https://github.com/Husenap/dubu-serialize.git
    GIT_TAG         4723aa8ea6e43ac33aa493c1a163cf0d258cce0b #v1.1
)

set(dubu_serialize_BUILD_TESTS OFF)

FetchContent_MakeAvailable(dubu_serialize)