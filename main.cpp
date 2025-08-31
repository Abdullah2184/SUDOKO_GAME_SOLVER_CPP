#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "puzzleClass.cpp"

void gameplay(Sudoko_Game &game) {
    while (true) {
                std::cout << "The puzzle is: \n"; 
                game.print_puzzle();
                if (game.check_if_full()) {
                    if (game.check_if_correct()) {
                        std::cout << "You have solved the puzzle correctly!" << std::endl;
                        break;
                    } else {
                        std::cout << "You have made a mistake somewhere!" << std::endl;
                    }
                }

                std::cout << "\n\nEnter a cell index (0-8, 0-8) and the value (1-9)\n";
                std::cout << "Enter -1 -1 -1 to show the solution\n";
                std::cout << "Enter the 3 values separated by spaces: ";
                int row, col, val; std::cin >> row >> col >> val;
                if (row==-1 && col==-1 && val==-1) {
                    if (game.solve_puzzle()) {
                        std::cout << "Game over. The solution is: \n";
                        game.print_puzzle();
                        
                        /*
                        //for debugging purposes
                        for (int i=0; i<9; i++) {
                            for (int j=0; j<9; j++) {
                                std::cout << get_cell_value(i, j) << " ";
                            }
                            std::cout << std::endl;
                        }
                        */

                        break;
                        return;
                    }
                    else std::cout << "This puzzle is not solvable!" << std::endl;
                    break; return;
                }
                while (row<0 || row>8 || col<0 || col>8 || val<1 || val>9) {
                    std::cout << "Invalid input. Please enter again: ";
                    std::cin >> row >> col >> val;
                }
                game.set_value(row, col, val);
                system("cls");
            }
}

int main() {
    std::cout << "SUDOKO SOLVER" << "\n\n";

    bool play = true;
    while(play = true) {
        std::cout << "Choose an option: \n1. Solve a puzzle\n2. Enter your own puzzle\n3. Exit\n> ";
        int choice; std::cin >> choice;
        
        if (choice == 1) {
            Sudoko_Game game;
            game.load_puzzle();
            gameplay(game);
            
        }
        else if (choice == 2) {
            Sudoko_Game game;
            game.input_puzzle();
            gameplay(game);
        }
        else if (choice == 3) break;
        else std::cout << "Invalid choice. Please enter again.\n\n";
        
    }
    return 0;
}