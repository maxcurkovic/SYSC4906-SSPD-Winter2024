cmake_minimum_required(VERSION 3.27)
project(Group-Yash-And-Max-Assignment_SYSC4906)

set(CMAKE_CXX_STANDARD 20)

add_executable(Group-Yash-And-Max-Assignment_SYSC4906 main.cpp)


include_directories(Catch2/single_include)
enable_testing()
add_executable(tests
            sspp_test.cpp
            ._pu1_test.cpp
            ._pu2_test.cpp
            ._pu3_test.cpp
)
add_test(NAME Catch2Tests COMMAND tests)
