# game/CMakeLists.txt
add_library(game STATIC
        Game.cpp
        Game.h
        Board.cpp
        Board.h
        Player.cpp
        Player.h
        Square.h
        Square.cpp
)

target_link_libraries(game PRIVATE ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY})
