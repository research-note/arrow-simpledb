project(testdb)

set(GTEST_ROOT "" CACHE PATH "GoogleTest root directory")

find_package(Arrow REQUIRED)

# find_library(
#   arrow_shared
#   NAMES libarrow.so
#   HINTS /usr/lib/x86_64-linux-gnu
#   REQUIRED)

add_executable(testdb TableTest.cpp main.cpp Tables.cpp)

target_link_libraries(testdb libgtest.a libdb gtest arrow_shared)

install(TARGETS testdb DESTINATION bin)