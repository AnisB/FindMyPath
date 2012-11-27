cmake_minimum_required(VERSION 2.6)
 
project(test)
set (CMAKE_CXX_FLAGS "-fpermissive") 

include_directories(../src)
set( SOURCE 
	../src/MapLoader.cpp
	../src/PathFindAStar.cpp
	../src/Renderer.cpp
	../src/Map.cpp
        ../src/PathFindDijkstra.cpp)
 
#  SFML finding
add_executable(testAStar testAStar.cpp ${SOURCE})
target_link_libraries(testAStar ${SFML_LIBRARIES})
add_executable(testDijkstra testDijkstra.cpp ${SOURCE})
target_link_libraries(testDijkstra ${SFML_LIBRARIES})

message(STATUS ${CMAKE_SOURCE_DIR}/Samples/)
message(STATUS ${CMAKE_BINARY_DIR}/test/Samples)
execute_process( COMMAND ${CMAKE_COMMAND}  -E create_symlink  ${CMAKE_SOURCE_DIR}/Samples/ ${CMAKE_BINARY_DIR}/test/Samples)



 


