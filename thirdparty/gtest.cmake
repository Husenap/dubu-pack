message("-- External Project: gtest")
include(FetchContent)

set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    gtest
    GIT_REPOSITORY  https://github.com/google/googletest.git
    GIT_TAG         release-1.10.0
)

FetchContent_MakeAvailable(gtest)

include(GoogleTest)
enable_testing()