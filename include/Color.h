#ifndef COLOR_H
#define COLOR_H

#include <iostream>

/**
 * @class Color
 * @brief Manages change of text color in terminal.
 */

enum class Color {
    YELLOW,
    GREEN,
    RED,
    RESET
};

/**
 * @brief Sets text color in terminal to chosen color.
 */
void setColor(Color color);

#endif
