#include "Color.h"

#include <iostream>

void setColor(Color color) {
    switch (color) {
        case Color::YELLOW:
            std::cout << "\033[33m"; // Set text color to yellow
            break;
        case Color::GREEN:
            std::cout << "\033[32m"; // Set text color to green
            break;
        case Color::RED:
            std::cout << "\033[31m"; // Set text color to red
            break;
        case Color::RESET:
            std::cout << "\033[0m";  // Reset text color to default
            break;
        default:
            std::cerr << "Invalid color code!" << std::endl;
    }
}
