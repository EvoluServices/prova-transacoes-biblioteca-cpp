cmake_minimum_required(VERSION 3.15)
project(biblioteca CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_library(biblioteca_lib
    src/cli/command.cpp
    src/cli/console.cpp
    src/data/library.cpp
    src/model/date.cpp
    src/service/library_service.cpp
)
target_include_directories(biblioteca_lib PUBLIC src)

add_executable(biblioteca src/main.cpp)
target_link_libraries(biblioteca PRIVATE biblioteca_lib)

enable_testing()
add_executable(testes tests/command_test.cpp)
target_include_directories(testes PRIVATE tests)
target_link_libraries(testes PRIVATE biblioteca_lib)
add_test(NAME testes COMMAND testes)
