# Minimum CMake version required to generate
# our build system
cmake_minimum_required(VERSION 3.0)	

project(RCSwitchControl)
 
#Bring the headers, such as Student.h into the project
include_directories(include)
file (GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")
 
#Generate the shared library from the sources
add_library(${PROJECT_NAME} SHARED ${SOURCES})
 
#Set the location for library installation -- i.e., /usr/lib in this case
# not really necessary in this example. Use "sudo make install" to apply
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_SOURCE_DIR}/lib)
install(FILES ${HEADERS} DESTINATION ${CMAKE_SOURCE_DIR}/include)

