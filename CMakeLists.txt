cmake_minimum_required(VERSION 2.6)


set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
#  SFML finding
find_package(SFML 1.6 COMPONENTS window graphics REQUIRED)
add_subdirectory(test)
add_subdirectory(release)
