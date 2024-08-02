#include "ChessClient.h"
#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

ChessClient::ChessClient(const char* serverIP, int port) : isRunning(true) {
    connectToServer(serverIP, port);

    // Initialize SDL with all required subsystems
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Initialize SDL_image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        exit(1);
    }

    // Create window with more specific flags
    window = SDL_CreateWindow("Chess Client", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    if (!window) {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Initialize board
    board = std::make_unique<Board>(renderer);
    board->loadTextures();
    board->initializePiecesForDisplay();

    // Initial render
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    board->drawBoard();
    SDL_RenderPresent(renderer);

    selectedSquare = nullptr;

    std::cout << "ChessClient initialized successfully" << std::endl;
}

ChessClient::~ChessClient() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    close(socket);
}

void ChessClient::connectToServer(const char* serverIP, int port) {
    socket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (socket < 0) {
        std::cerr << "Error creating socket" << std::endl;
        exit(1);
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, serverIP, &serverAddr.sin_addr);

    if (connect(socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        exit(1);
    }

    std::cout << "Connected to server" << std::endl;
}

void ChessClient::run() {
    while (isRunning) {
        std::cout << "Starting new game loop iteration" << std::endl;
        handleEvents();
        render();
        receiveServerMessages();
        SDL_Delay(16);
    }
}
void ChessClient::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        std::cout << "Event detected: " << event.type << std::endl;
        switch (event.type) {
            case SDL_QUIT:
                std::cout << "Quit event received" << std::endl;
                isRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                std::cout << "Mouse button down event received" << std::endl;
                std::cout << "Button: " << (int)event.button.button << std::endl;
                std::cout << "Clicks: " << (int)event.button.clicks << std::endl;
                std::cout << "X: " << event.button.x << ", Y: " << event.button.y << std::endl;
                handleMouseClick(event.button.x, event.button.y);
                break;
            case SDL_WINDOWEVENT:
                std::cout << "Window event: " << event.window.event << std::endl;
                break;
            default:
                std::cout << "Unhandled event type: " << event.type << std::endl;
                break;
        }
    }
}

void ChessClient::handleMouseClick(int mouseX, int mouseY) {
    int rowIndex = mouseY / 100;
    int colIndex = mouseX / 100;

    std::cout << "Mouse clicked at: (" << rowIndex << ", " << colIndex << ")" << std::endl;

    if (rowIndex >= 0 && rowIndex < 8 && colIndex >= 0 && colIndex < 8) {
        Square& clickedSquare = board->getSquare(rowIndex, colIndex);

        if (selectedSquare == nullptr) {
            selectedSquare = &clickedSquare;
            std::cout << "Selected square: (" << rowIndex << ", " << colIndex << ")" << std::endl;
        } else {
            std::pair<int, int> start = selectedSquare->getCoordinates();
            std::pair<int, int> end = clickedSquare.getCoordinates();
            std::cout << "Attempting move from (" << start.first << ", " << start.second
                      << ") to (" << end.first << ", " << end.second << ")" << std::endl;
            sendMove(start.first, start.second, end.first, end.second);
            selectedSquare = nullptr;
        }
    }
}
void ChessClient::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    board->drawBoard();
    SDL_RenderPresent(renderer);
}

void ChessClient::sendMove(int startX, int startY, int endX, int endY) {
    std::ostringstream oss;
    oss << "MOVE " << startX << " " << startY << " " << endX << " " << endY;
    std::string move = oss.str();
    std::cout << "Sending move to server: " << move << std::endl;

    send(socket, move.c_str(), move.length(), 0);
    receiveServerMessages();
}

void ChessClient::receiveServerMessages() {
    char buffer[1024];
    ssize_t bytesRead = recv(socket, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        handleServerResponse(std::string(buffer));
    }
}

void ChessClient::handleServerResponse(const std::string& response) {
    if (response == "INVALID_MOVE") {
        std::cout << "Invalid move! Try again." << std::endl;
    } else {
        board->updateFromSerializedState(response);
    }
}
