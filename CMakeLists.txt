cmake_minimum_required(VERSION 3.5)

project(GraphColoring LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXTRA_LIBS ${YARP_LIBRARIES})
set(SOURCES main.cpp graphcoloring.cpp xmlparser.cpp)
set(HEADERS graphcoloring.h xmlparser.h)
set(CMAKE_REQUIRED_LIBRARIES xml2)
list(APPEND EXTRA_LIBS "xml2")

add_executable(GraphColoring ${SOURCES} ${HEADERS})

target_include_directories(GraphColoring PRIVATE "/usr/include/libxml2")
target_link_libraries(GraphColoring ${EXTRA_LIBS})

