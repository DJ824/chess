#ifndef COLOR_H
#define COLOR_H

#include <iostream>

enum class Color {
    WHITE,
    BLACK
};

// Inline the << operator to avoid duplicate symbol errors in the linker phase
inline std::ostream& operator<<(std::ostream& os, const Color& color) {
    switch (color) {
        case Color::WHITE:
            os << "White";
            break;
        case Color::BLACK:
            os << "Black";
            break;
        default:
            os << "Unknown Color";
    }
    return os;
}

#endif // COLOR_H
