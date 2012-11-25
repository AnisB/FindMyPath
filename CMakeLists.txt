cmake_minimum_required(VERSION 2.6)
 
project(FindMyPath)
set (CMAKE_CXX_FLAGS "-fpermissive") 
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake")

set( SOURCE 
	src/MapLoader.cpp
	src/PathFindAStar.cpp
	src/Renderer.cpp
	src/Map.cpp)
 
#  SFML finding
find_package(SFML 1.6 COMPONENTS window graphics REQUIRED)
add_executable(FindMyPath src/FindMyPath.cpp ${SOURCE})
target_link_libraries(FindMyPath ${SFML_LIBRARIES})

execute_process( COMMAND ${CMAKE_COMMAND}  -E create_symlink  ${PROJECT_SOURCE_DIR}/Samples/ ${PROJECT_BINARY_DIR}/Samples)
message(STATUS ${PROJECT_BINARY_DIR}/Samples)


 


