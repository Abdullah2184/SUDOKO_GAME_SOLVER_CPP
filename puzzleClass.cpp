#include <iostream>
#include <string>
#include <fstream>
#include "puzzlesAll.cpp"

class Sudoko_Game {

    private:
    int puzzle[9][9];


    public:

    void get_cell_value(int row, int col) {
        std::cout << puzzle[row][col] << std::endl;
    }

    void print_puzzle() {
        // Printing the puzzle with indexes and clean formatting
        std::cout << "  ";
        for (int j=0; j<9; j++) {
                if (j%3==0) std::cout << "| ";
                std::cout << j << " ";
        }
        std::cout << "\n";

        for (int i=0; i<9; i++) {
            if (i%3==0) {
                std::cout << "-------------------------------\n";
            }
            std::cout << i << "|";
            for (int j=0; j<9; j++) {
                if (j%3==0) std::cout << "| ";
                if (puzzle[i][j] == 0) std::cout << "  ";
                else std::cout << puzzle[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n\n";
    }

    void set_value(int row, int col, int val) {
        if (val>=0 && val<=9) puzzle[row][col] = val;
    }
    
    bool is_valid_move(int row, int col, int val) {
        for (int i=0; i<9; i++) {
            if (puzzle[row][i] == val && i!=col) return false; //Check row
            if (puzzle[i][col] == val && i!=row) return false; //Check column
            
            int r = i/3 + (row/3)*3;
            int c = i%3 + (col/3)*3;
            if ((r != row || c != col) && puzzle[r][c] == val) return false;

        }
        return true;
    }

    bool solve_puzzle(int row=0, int col=0) {
        if (col == 9) { 
            col = 0; 
            row++; 
        }
        if (row == 9) return true; // solved


        if (puzzle[row][col] != 0) return solve_puzzle(row, col+1); //Skip filled cells

        for (int val=1; val<=9; val++) {
            set_value(row, col, val);
            if (is_valid_move(row, col, val)) {
                if (solve_puzzle(row, col+1)) return true;
            }
            set_value(row, col, 0); //Reset cell if not valid
        }
        return false;
    }

    void input_puzzle() {
        std::cout << "Enter the values row-wise as a continous (space-seperated) stream of numbers" 
                << " with 0's for empty spaces: ";
        for (int i=0; i<9; i++) {
            for (int j=0; j<9; j++) { 
                int val;  
                if (std::cin >> val) set_value(i, j, val);
                else {
                    std::cout << "The value for cell " << i << " " << j << "is invalid. Exiting." << std::endl;
                    exit(1); //Exit if invalid input
                }
            } 
        }
    }

    //Function overloading to copy puzzle from different input types
    void copy_puzzle(int** ptr_puzzle) {
        //Copies the contents of a double ptr puzzle type into the class puzzle
        for (int i=0; i<9; i++) {
            for (int j=0; j<9; j++) {
                puzzle[i][j] = ptr_puzzle[i][j];
            }
        }
    }

    void copy_puzzle(int arr_puzzle[][9]) {
        //Copies the contents of a 2D puzzle type into the class puzzle
        for (int i=0; i<9; i++) {
            for (int j=0; j<9; j++) {
                puzzle[i][j] = arr_puzzle[i][j];
            }
        }
    }

    void load_puzzle() {
        // Loads a puzzle from the sudoku puzzles file
        int puzzle_fromfile[9][9];
        Puzzles puzzle_base;
        copy_puzzle(puzzle_base.get_randpuzzle());

        /*
        std::fstream file;
        file.open("sudoko_puzzles.dat", std::ios::in | std::ios::binary);
        if (file.is_open()) {
            file.read(reinterpret_cast<char*>(puzzle_fromfile), sizeof(puzzle_fromfile));
            copy_puzzle(puzzle_fromfile);
            file.close();
        } else {
            std::cout << "Error opening file" << std::endl;
        }
        */    
    }

    void solvable() {
        //Copies it, Loops through the copy and checks if it is solvable
        Sudoko_Game puzzle_duplicate;
        puzzle_duplicate.copy_puzzle(puzzle);
        if (puzzle_duplicate.solve_puzzle()) std::cout << "This puzzle is definitely solvable!" << std::endl;
        else std::cout << "This puzzle is not solvable!" << std::endl;
    }

    bool check_if_correct() {
        //Loops through the puzzle and checks if it is correct by validating each cell
        for (int i=0; i<9; i++) {
            for (int j=0; j<9; j++) {
                if (!is_valid_move(i, j, puzzle[i][j])) {
                    return false;
                }
            }
        }
        return true;
    }

    bool check_if_full() {
        for (int i=0; i<9; i++) {
            for (int j=0; j<9; j++) {
                if (puzzle[i][j] == 0) {
                    return false;
                }
            }
        }
        return true;
    }

};