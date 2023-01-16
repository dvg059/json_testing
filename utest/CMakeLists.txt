cmake_minimum_required(VERSION 3.10)
project(JSONUnitTestProj VERSION 1.0.1)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 11)


include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()


add_executable(json_unittest json_unit_test.cpp ../src/cjson_mngr.cpp ../json/jsoncpp.cpp)

target_link_libraries(json_unittest GTest::gtest_main)


include(GoogleTest
gets_discover_tests)
