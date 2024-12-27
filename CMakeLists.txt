cmake_minimum_required(VERSION 3.10)
project(Prolab3)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_FAKER_TESTS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_subdirectory(externals/faker-cxx)

add_executable(main main.cpp tweet.cpp user.cpp)

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(main faker-cxx)
