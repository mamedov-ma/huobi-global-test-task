cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

project(huobi-global)

add_compile_options(-O3 -Wall -Wextra -Wpedantic)

add_library(my_library SHARED)
target_sources(my_library PRIVATE src/order_book.cpp)
target_include_directories(my_library PUBLIC include lib)

add_executable(main src/main.cpp)
target_link_libraries(main my_library)

add_subdirectory(bm)

