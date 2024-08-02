cmake_minimum_required(VERSION 3.17)
project(chessv2)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SDL Paths
set(SDL2_PATH "/Library/Frameworks/SDL2.framework")
set(SDL2_IMAGE_PATH "/Library/Frameworks/SDL2_image.framework")
set(SDL2_TTF_PATH "/Library/Frameworks/SDL2_ttf.framework")

# Include directories
include_directories("${SDL2_PATH}/Headers")
include_directories("${SDL2_IMAGE_PATH}/Headers")
include_directories("${SDL2_TTF_PATH}/Headers")

# Find SDL libraries
find_library(SDL2_LIBRARY NAME SDL2 PATHS ${SDL2_PATH})
find_library(SDL2_IMAGE_LIBRARY NAME SDL2_image PATHS ${SDL2_IMAGE_PATH})
find_library(SDL2_TTF_LIBRARY NAME SDL2_ttf PATHS ${SDL2_TTF_PATH})

# Add subdirectories
add_subdirectory(pieces)
add_subdirectory(game)
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(utils)

# Optionally, you can link SDL libraries here if every executable links them
link_libraries(${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY})