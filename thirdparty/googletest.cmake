message("-- External Project: googletest")
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY  https://github.com/google/googletest.git
    GIT_TAG         a4ab0ab
)

FetchContent_MakeAvailable(googletest)

set_target_properties("gtest" PROPERTIES FOLDER "thirdparty/googletest")
set_target_properties("gmock" PROPERTIES FOLDER "thirdparty/googletest")
set_target_properties("gtest_main" PROPERTIES FOLDER "thirdparty/googletest")
set_target_properties("gmock_main" PROPERTIES FOLDER "thirdparty/googletest")