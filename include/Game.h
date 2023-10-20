#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <filesystem>
#include "Color.h"
#include "Board.h"

/**
 * @class Game
 * @brief Manages game-related operations.
 *
 * This class provides methods for managing UI, user input and data loading.
 *
 */

class Game{
private:
    int difficulty; // 1 - easy, 2 - medium, 3 - difficult
    Board board;
public:
    /**
     * @brief Starts new with the settings given by user. It contains game loop.
     */
    void start();

    /**
     * @brief Processes user input. User can choose to end the app or give number and its position.
     */
    void processInput();

    /**
     * @brief Enables user to choose difficulty of the game.
     */
    void chooseDifficulty();

    /**
     * @brief Randomly chooses data file of correct difficulty, from which will be loaded data for creating a sudoku board.
     * @return std::filesystem::path variable contains path of file from which will be loaded data for a sudoku board.
     */
    std::filesystem::path chooseFile();
};

#endif
