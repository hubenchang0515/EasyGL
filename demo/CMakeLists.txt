cmake_minimum_required(VERSION 3.5)

project(EasyGL-Demo LANGUAGES CXX)

set(DEMO_LIST "01.triangle" "02.transform" "03.texture" "04.cube" "05.coordinate" "06.camera" "07.lighting")

foreach(DEMO ${DEMO_LIST})
    add_executable(${DEMO} ${DEMO}.cpp)
    target_link_libraries(${DEMO} PRIVATE EasyGL)
    target_compile_definitions(${DEMO} PRIVATE -DDEMO_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
endforeach(DEMO ${DEMO_LIST})

