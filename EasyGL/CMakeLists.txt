add_compile_options("$<$<NOT:$<C_COMPILER_ID:MSVC>>:-W;-Wall;-Wextra;-O3>")
add_compile_options("$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-W;-Wall;-Wextra;-O3>")

file(GLOB HDR "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}" SRC)
add_library(${PROJECT_NAME} STATIC ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}")
target_link_libraries(${PROJECT_NAME} PUBLIC glad glfw glm stb)