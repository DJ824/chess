# pieces/CMakeLists.txt
add_library(pieces STATIC
        Bishop.h
        King.h
        Knight.h
        Pawn.h
        Piece.cpp
        Piece.h
        Queen.h
        Rook.h
)

target_link_libraries(pieces PRIVATE ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY})
