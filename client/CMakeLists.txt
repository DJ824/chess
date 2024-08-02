# client/CMakeLists.txt
add_executable(client
        ChessClient.cpp
        ChessClient.h
        ClientMain.cpp
)

# Link with SDL2 libraries and other local project libraries
target_link_libraries(client PRIVATE ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} game pieces utils)
