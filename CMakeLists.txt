# --------------------------------------------------
# Project Configurations
#   - Setup
#   - Build
# --------------------------------------------------

# --------------------------------------------------
# SETUP
# --------------------------------------------------

cmake_minimum_required(VERSION 3.14)
project(regxstring VERSION 0.0.1)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 14)

# Load files
file(GLOB_RECURSE source_code src/*.cpp)
file(GLOB_RECURSE header_code include/*.h)
set(source ${source_code})
set(header ${header_code})

# --------------------------------------------------
# BUILD
# --------------------------------------------------

# Build library
add_library(${PROJECT_NAME} ${header} ${source})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
