#include "Board.h"

bool Board::getIsCorrect(){
    return isCorrect;
}

bool Board::getIsFull(){
    return isFull;
}

void Board::printBoard(){
    isCorrect = true;
    isFull = true;

    int rowCorrection = 1;
    int colCorrection;

    for (int i = 1; i < 12; i++) { //rows
        colCorrection = 1;
        for (int j = 1; j < 12; j++) { //columns
            if (i % 4 == 0 && j % 4 == 0) {  //intersection of horizontal and vertical borders
                std::cout << "+";
            } else if (i % 4 == 0) { //horizontal border
                std::cout << "--";
                if(j == 11){
                    rowCorrection++;
                }
            } else if (j % 4 == 0) {  //vertical border
                std::cout << "|";
                colCorrection++;
            } else { //numbers
                if(tilesInitial[i - rowCorrection][j-colCorrection] != '.'){  //numbers that are part of initial board
                    std::cout << tilesInitial[i - rowCorrection][j-colCorrection] << " ";
                }else if(tilesPlaying[i - rowCorrection][j-colCorrection] != '.'){ //numbers that were entered by user

                    //sets text color according to the current state of conflict in this tile
                    if(checkTile(i-rowCorrection, j-colCorrection, tilesPlaying[i - rowCorrection][j-colCorrection])){ //there is not conflict in row, column and square
                        setColor(Color::YELLOW);
                    }else{ //there is a conflict in row, column or square
                        setColor(Color::RED);
                        isCorrect = false; //one conflict means that whole board is incorrectly filled up
                    }

                    std::cout << tilesPlaying[i - rowCorrection][j-colCorrection] << " ";
                    setColor(Color::RESET);                 }
                else{ //there is at leas one tile with char '.' => sudoku board haven't been yet fully filled up
                    isFull = false;
                    std::cout << ". ";
                }
            }
        }
        std::cout << std::endl;
    }
}

void Board::populateBoard(std::filesystem::path file){
    //initial tiles
    //opens file
    std::fstream stream(file);
    if(!stream.is_open()){
        std::cerr << "Failed to open file." << std::endl;
        std::exit(1);
    }

    //reads lines
    std::string buf;
    int line = 0;

    while(std::getline(stream, buf) && line != 9){
        //single numbers are assigned to the tiles
        for(int i=0; i<9; i++){
            tilesInitial[line][i] = buf[i];
            tilesPlaying[line][i] = buf[i];
        }
        line++;
    }

    stream.close();
}

void Board::addNumber(int row, int col, int num){
    //adds number to the board if chosen tile isn't part of initial data
    setColor(Color::YELLOW);
    if(tilesInitial[row-1][col-1] == '.'){
        tilesPlaying[row-1][col-1] =  static_cast<char>(num + '0');
    }
    setColor(Color::RESET);
}

bool Board::checkTile(int row, int col, int num){
    bool isValid = true;

    //checks row and column for possible conflicts
    for(int i=0; i<9; i++){
        //checks row
        if(tilesPlaying[row][i] == num && i != col){
            isValid = false;
        }

        //checks column
        if(tilesPlaying[i][col] == num && i != row){
            isValid = false;
        }
    }

    //checks square for possible conflicts
    int cols[2], rows[2];
    int k = 0;
    int l = 0;

    //coordinates of first tile in square
    int sqCol = (col / 3) * 3;
    int sqRow = (row / 3) * 3;
;
    //finds the position of unchecked tiles in the square, position is relativ to specific square
    for(int j=0; j<3; j++){
        //columns
        if(j != (col%3)){
            cols[k] = j;
            k++;
        }

        //rows
        if(j != (row%3)){
            rows[l] = j;
            l++;
        }
    }

    //checks tiles that haven't been yet checked by row and column check
    if(tilesPlaying[sqRow + rows[0]][sqCol + cols[0]] == num || tilesPlaying[sqRow + rows[0]][sqCol + cols[1]] == num || tilesPlaying[sqRow + rows[1]][sqCol + cols[0]] == num || tilesPlaying[sqRow + rows[1]][sqCol + cols[1]] == num){
        isValid = false;
    }

    return isValid;
}
