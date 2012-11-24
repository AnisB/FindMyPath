
cmake_minimum_required(VERSION 2.6)
 
project(FindMyPath)
set (CMAKE_CXX_FLAGS "-fpermissive") 

set( SOURCE 
	src/MapLoader.cpp
	src/PathFindAStar.cpp
	src/Renderer.cpp
	src/Map.cpp)
 
 
add_executable(FindMyPath src/FindMyPath.cpp ${SOURCE})
 


