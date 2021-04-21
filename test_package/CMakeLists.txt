cmake_minimum_required(VERSION 3.1)
project(PackageTest CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Load files
file(GLOB_RECURSE source_code *test.cpp)
file(GLOB_RECURSE header_code *test.h)
set(source ${source_code})
set(header ${header_code})

# --------------------------------------------------
# BUILD
# --------------------------------------------------

add_executable(${PROJECT_NAME} main.cpp ${source} ${header})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/resource/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/resource)

# CTest is a testing tool that can be used to test your project.
enable_testing()
add_test(NAME ${PROJECT_NAME}
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
         COMMAND ${PROJECT_NAME})