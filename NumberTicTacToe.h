
#ifndef UNTITLED44_NUMBERTICTACTOE_H
#define UNTITLED44_NUMBERTICTACTOE_H


#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "BoardGame_Classes.h"
#include "limits"

using namespace std;

template<typename T>

// Class for Number Tic-Tac-Toe game
class NumberTicTacToe : public Board<T> {
public:
    NumberTicTacToe();

    void display_board() override;  // Function to display the game board
    bool update_board(int x, int y, T symbol) override;  // Function to update the board with a symbol
    bool is_draw() override;  // Function to check if the game is a draw
    bool isValidPlace(int place);  // Function to check if a place is valid
    bool isValidMove(int move, char playerSymbol);  // Function to check if the player's move is valid
    void makeMove(int place, int move);  // Function to make a move on the board
    bool is_win() override;  // Function to check if there is a winner
    bool game_is_over() override;  // Function to check if the game is over

private:
    vector<vector<T>> board;  // 2D vector representing the board
    vector<T> availableNumbers;  // Vector containing available numbers for moves
    int rows;  // Number of rows in the board
    int cols;  // Number of columns in the board

};

template <typename T>
// Class for a random player in the game
class N_RandomPlayer : public RandomPlayer<T> {
public:
    N_RandomPlayer(T symbol,NumberTicTacToe<T>* boardptr);  // Constructor to initialize the player with a symbol

    void getmove(int& x, int& y) override;
    // Function to get the move of the random player
private:
    NumberTicTacToe<T>*numberTicTacToeptr;
};

// Constructor for NumberTicTacToe
template<typename T>
NumberTicTacToe<T>::NumberTicTacToe() {
    this->rows = 3;  // Set the number of rows to 3
    this->cols = 3;  // Set the number of columns to 3
    board.resize(rows, vector<int>(cols, -1));  // Initialize the board with -1 (empty cells)
    availableNumbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};  // Available numbers for the moves
}

// Function to display the current game board
template<typename T>
void NumberTicTacToe<T>::display_board() {
    cout << "-------------\n";
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (board[r][c] == -1)
                cout << "|   ";  // If the cell is empty
            else
                cout << "| " << board[r][c] << " ";  // Display the number in the cell
        }
        cout << "|\n";
    }
    cout << "-------------\n";
}

// Function to check if a place on the board is valid (empty and within range)
template<typename T>
bool NumberTicTacToe<T>::isValidPlace(int place) {
    return place >= 1 && place <= 9 && board[(place - 1) / cols][(place - 1) % cols] == -1;
}

// Function to check if a move is valid for the player
template<typename T>
bool NumberTicTacToe<T>::isValidMove(int move, char playerSymbol) {
    // Check if the move matches the player's allowed numbers
    if ((playerSymbol == 'X' && move % 2 == 0) || (playerSymbol == 'O' && move % 2 == 1)) {
        cout << "Invalid move. Choose a valid number.\n";
        return false;
    }

    // Check if the move is in availableNumbers
    auto it = find(availableNumbers.begin(), availableNumbers.end(), move);
    if (it == availableNumbers.end()) {
        cout << "Number not available. Try again.\n";
        return false;
    }

    return true;
}

// Function to make a move on the board
template<typename T>
void NumberTicTacToe<T>::makeMove(int place, int move) {
    int row = (place - 1) / cols;
    int col = (place - 1) % cols;
    board[row][col] = move;
    // Remove the move from the available numbers
    availableNumbers.erase(remove(availableNumbers.begin(), availableNumbers.end(), move), availableNumbers.end());
}

// Function to update the board with a symbol (used by players)
template<typename T>
bool NumberTicTacToe<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < rows && y >= 0 && y < cols && board[x][y] == -1) {
        board[x][y] = symbol;  // Update the board with the symbol
        availableNumbers.erase(remove(availableNumbers.begin(), availableNumbers.end(), symbol), availableNumbers.end());
        return true;
    }
    return false;  // If the move is invalid
}

// Function to check if the game is a draw (no empty spaces and no winner)
template<typename T>
bool NumberTicTacToe<T>::is_draw() {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (board[r][c] == -1) {
                return false;  // There are still empty spaces, so it's not a draw
            }
        }
    }
    return !is_win();  // If there's no winner, it's a draw
}

// Function to check if there is a winner
template<typename T>
bool NumberTicTacToe<T>::is_win() {
    // Check rows for a sum of 15 (X = 1, 3, 5, 7, 9, O = 2, 4, 6, 8)
    for (int r = 0; r < rows; ++r) {
        if (board[r][0] != -1 && board[r][0] + board[r][1] + board[r][2] == 15)
            return true;
    }

    // Check columns for a sum of 15
    for (int c = 0; c < cols; ++c) {
        if (board[0][c] != -1 && board[0][c] + board[1][c] + board[2][c] == 15)
            return true;
    }

    // Check diagonals for a sum of 15
    if (board[0][0] != -1 && board[0][0] + board[1][1] + board[2][2] == 15)
        return true;

    if (board[0][2] != -1 && board[0][2] + board[1][1] + board[2][0] == 15)
        return true;

    return false;  // No winner
}

// Function to check if the game is over (win or no available numbers)
template<typename T>
bool NumberTicTacToe<T>::game_is_over() {
    return is_win() || availableNumbers.empty();  // The game ends when there's a win or no available numbers
}

// Constructor for random player
template <typename T>
N_RandomPlayer<T>::N_RandomPlayer(T symbol,NumberTicTacToe<T>* boardptr) : RandomPlayer<T>(symbol),numberTicTacToeptr(boardptr) {
    srand(time(0));  // Seed the random number generator
}

// Function to get the random player's move
template <typename T>
void N_RandomPlayer<T>::getmove(int& x, int& y) {
    int move = rand() % 9 + 1;  // Random number between 1 and 9

    // Ensure the selected move is valid
    while (!this->numberTicTacToeptr->isValidPlace(move)) {
        move = rand() % 9 + 1;  // Keep retrying if the move is already taken
    }

    // Convert the move to row and column
    x = (move - 1) / 3;  // Row calculation for 3x3 board
    y = (move - 1) % 3;  // Column calculation for 3x3 board
}

// Class for a human player
template <typename T>
class HumanPlayer : public Player<T> {
public:
    HumanPlayer(string n, T symbol) : Player<T>(n, symbol) {}

    // Function to get the move of a human player
    void getmove(int& x, int& y) override {
        bool validInput = false;
        while (!validInput) {
            cout << "Enter your move (row and column, space-separated, between 1 and 3): ";
            cin >> x >> y;

            // Validate input
            if (cin.fail() || x < 1 || x > 3 || y < 1 || y > 3) {
                cin.clear();  // Clear input stream error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
                cout << "Invalid input. Please enter numbers between 1 and 3.\n";
            } else {
                validInput = true;
            }
        }

        // Convert from 1-3 to 0-2 indexing for array
        x--;
        y--;
    }
};


#endif //UNTITLED44_NUMBERTICTACTOE_H
