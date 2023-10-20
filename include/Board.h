#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <filesystem>
#include "Color.h"

/**
 * @class Board
 * @brief Represents Sudoku playing board.
 *
 * This class provides methods for loading initial state of the board, adding number and check correctness of solution provided by the user.
 */

class Board{
private:
    char tilesInitial[9][9] = {}; //holds initial state of sudoku board
    char tilesPlaying[9][9] = {}; //holds current state of sudoku board
    bool isCorrect = true;
    bool isFull = false;
public:
    /**
     * @brief Getter method for variable isCorrect. This variable says whether all numbers that were entered by user are correct.
     */
    bool getIsCorrect();

    /**
     * @brief Getter method for variable isFull. This variable says whether sudoku boar has been completely filled out.
     */
    bool getIsFull();

    /**
     * @brief Prints current state of the sudoku board.
     */
    void printBoard();

    /**
     * @brief Loads data from chosen file and populates the sudoku board with these data.
     */
    void populateBoard(std::filesystem::path file);

    /**
     * @brief Adds number in the specified row and column
     */
    void addNumber(int row, int col, int num);

    /**
     * @brief Checks whether the tile specified by its row and column is in conflict with other tiles in same row, column or square.
     */
    bool checkTile(int row, int col, int num);
};

#endif
