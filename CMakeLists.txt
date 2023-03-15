project(IG_project)

cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0043 NEW)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -lassimp")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/glfw)
add_subdirectory(${CMAKE_SOURCE_DIR}/glm)
add_subdirectory(${CMAKE_SOURCE_DIR}/assimp)



find_package(OpenGL REQUIRED)
find_package(assimp REQUIRED)

FILE(GLOB_RECURSE folder_source ${CMAKE_SOURCE_DIR}/src/*.cpp)
FILE(GLOB_RECURSE folder_header ${CMAKE_SOURCE_DIR}/src/*.hpp)
FILE(GLOB_RECURSE folder_header ${CMAKE_SOURCE_DIR}/src/*.h)
FILE(GLOB_RECURSE shader_files ${CMAKE_SOURCE_DIR}/src/shaders/*.glsl)

set(glad_file ${CMAKE_SOURCE_DIR}/glad/src/glad.c)
FILE(GLOB_RECURSE imgui_files ${CMAKE_SOURCE_DIR}/includes/imgui/*.cpp ${CMAKE_SOURCE_DIR}/includes/imgui/*.h)

include_directories( GLOB_RECURSE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/glad/include
    ${CMAKE_SOURCE_DIR}/glm
    ${CMAKE_SOURCE_DIR}/assimp/include)

add_executable(${CMAKE_PROJECT_NAME} ${folder_source} ${shader_files} ${glad_file} ${folder_header} ${imgui_files})

file(COPY ${shader_files} DESTINATION "shaders")

set(EXT_LIBS ${OPENGL_LIBRARIES} glfw assimp)

target_link_libraries(${CMAKE_PROJECT_NAME} ${EXT_LIBS})
