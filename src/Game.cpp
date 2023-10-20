#include "Game.h"
#include "Color.h"

void Game::start(){
    std::cout << "\t\t CONSOLE SUDOKU" << std::endl<<std::endl;

    chooseDifficulty();

    //load data and prepare sudoku board
    std::filesystem::path file = chooseFile();
    board.populateBoard(file);

    //game loop
    while(true){
        board.printBoard();
        if(board.getIsFull() && board.getIsCorrect()){
            std::cout << std::endl << "\t\tCONGRATULATION, YOU WON!" << std::endl;
            std::exit(0);
        }
        processInput();
    }

}

void Game::processInput(){
    std::string input;
    bool isValid = false;

    while(!isValid){ //repeats until the user input is correct
        //writes prompt for user input
        std::cout << std::endl;
        std::cout << "Your next move in format row(1-9);column(1-9);number(1-9); (e.g.: 1;1;1; - number 1 in the upper left corner) or 0 for end: ";
        std::cin >> input;
        std::cout << std::endl;

        //processes user input
        if(input == "0"){ //user chosed to end the app
            char inputEnd;
            std::cout << "Are you sure that you want to end this game? [y/n]: ";
            std::cin >> inputEnd;

            if(inputEnd == 'y'){
                std::cout << std::endl << "\t\tGAME OVER!"<<std::endl<<std::endl;
                std::exit(0);
            }
        }else{ //user gave number and its position
            if(input.length() == 6){
                int row, col, num;
                row = input[0] - '0';
                col = input[2] - '0';
                num = input[4] - '0';

                if(row >= 1 && row <= 9 && col >= 1 && col <= 9 && num >= 1 && row <= 9){
                    isValid = true;
                    board.addNumber(row, col, num);
                }
            }

            if(!isValid){
                std::cerr << "Wrong input. Input format must be: row;column;number; . For example: 1;2;4;. Only numbers 1-9." << std::endl;
            }
        }
    }
}

void Game::chooseDifficulty(){
    //player choses game difficulty
    bool isValid = false;

    while(!isValid){
        std::cout << "Difficulty:" << std::endl;

        setColor(Color::GREEN);
        std::cout << "\t 1. easy" << std::endl;

        setColor(Color::YELLOW);
        std::cout << "\t 2. medium" << std::endl;

        setColor(Color::RED);
        std::cout << "\t 3. difficult" << std::endl;

        setColor(Color::RESET);
        std::cout << "Choose difficulty (1-3): " << std::endl;
        std::cin >> difficulty;

        //checks input validity
        if(difficulty >= 1 && difficulty <= 3){
            isValid = true;
        }else{
            std::cout << "Input is not correct. You can use only numbers 1-3." << std::endl<<std::endl;
            break;
        }

        std::cout << std::endl;
    }
}

std::filesystem::path Game::chooseFile(){
    std::string directory = "data/";

    //chooses directory according to difficulty
    switch(difficulty){
        case 1:
            directory += "easy/";
            break;
        case 2:
            directory += "medium/";
            break;
        case 3:
            directory += "difficult/";
            break;
    }

    //gets number of files in the directory
    int fileCount = 0;

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (std::filesystem::is_regular_file(entry)) {
            fileCount++;
        }
    }

    //chooses random file
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    int randomNumber = std::rand() % fileCount + 1;

    std::filesystem::path file = directory + std::to_string(randomNumber) + ".txt";
    return file;
}

