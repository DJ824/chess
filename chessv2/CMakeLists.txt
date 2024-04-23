cmake_minimum_required(VERSION 3.17)
project(chessv2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL2_PATH "/Library/Frameworks/SDL2.framework")
set(SDL2_IMAGE_PATH "/Library/Frameworks/SDL2_image.framework")

link_directories("/Library/Frameworks")

include_directories("${SDL2_PATH}/Headers")
include_directories("${SDL2_IMAGE_PATH}/Headers")

add_executable(chessv2 main.cpp Game.cpp Board.cpp Piece.cpp Player.cpp Square.cpp)

find_library(SDL2_LIBRARY NAME SDL2 PATHS ${SDL2_PATH})
find_library(SDL2_IMAGE_LIBRARY NAME SDL2_image PATHS ${SDL2_IMAGE_PATH})

target_link_libraries(chessv2 ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
