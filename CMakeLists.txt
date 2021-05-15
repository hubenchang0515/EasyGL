cmake_minimum_required(VERSION 3.5)
project(EasyGL C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

link_libraries("$<$<NOT:$<C_COMPILER_ID:MSVC>>:pthread>")
link_libraries("$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:pthread>")

add_subdirectory(thirdparty)
add_subdirectory(EasyGL)
add_subdirectory(demo)
