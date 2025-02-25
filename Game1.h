#ifndef OOP_A2_T2_GAME1_H
#define OOP_A2_T2_GAME1_H

#include "BoardGame_Classes.h"

/// Pyramid Tic-Tac-Toe
template <typename T>
class Game1_Board : public Board<T>{
public:
    Game1_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Game1_Player : public Player<T> {
public:
    Game1_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Game1_Random_Player : public RandomPlayer<T>{
public:
    Game1_Random_Player (T symbol);
    void getmove(int &x, int &y);
private:
    int width;
    int length;

};

template <typename T>
class Game1_MinMax_Player : public Player<T> {
public:
    Game1_MinMax_Player(T symbol);

    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(T s, bool isMaximizing);
    std::pair<int, int> getBestMove();
};




//---------------------- IMPLEMENTATION ----------------------

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <cctype>

using namespace std;

// Pyramid Tic-Tac-Toe Constructor
template <typename T>
Game1_Board<T> :: Game1_Board(){
    this->rows = 3;
    this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->board[0][0] = this->board[0][0] = this->board[0][0] = this->board[0][0]
            = this->board[0][0] = this->board[0][0] = -1; // If the cell = -1 then it is not valid in the game.
    this->n_moves = 0;
}

template <typename T>
bool Game1_Board<T> :: update_board(int x , int y , T mark){
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) &&
    (this->board[x][y] == 0|| mark == 0) && !(x == 0 && y == 0) &&
    !(x == 0 && y == 1) && !(x == 0 && y == 3) && !(x == 0 && y == 4) &&
    !(x == 1 && y == 0) && !(x == 1 && y == 4)) {
        if (mark == 0){ // When removing the value in the cell.
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void Game1_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            if (i == 0 && j == 0 || i == 0 && j == 1 || i == 0 && j == 3 || i == 0 && j == 4 || i == 1 && j == 0 || i == 1 && j == 4){
                cout << "        |";
                continue;
            }
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template<typename T>
bool Game1_Board<T>::is_win() {
    // Check the middle column
    if (this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2] && this->board[0][2] != 0) {
        return true;
    }

    // Check the second row
    if (this->board[1][1] == this->board[1][2] && this->board[1][2] == this->board[1][3] && this->board[1][1] != 0){
        return true;
    }

    // Check the last row
    if (((this->board[2][0] == this->board[2][1] && this->board[2][1] == this->board[2][2]) ||
    (this->board[2][2] == this->board[2][1] && this->board[2][1] == this->board[2][3]) ||
    (this->board[2][2] == this->board[2][3] && this->board[2][3] == this->board[2][4]))
    && this->board[2][2] != 0){
        return true;
    }

    // Check diagonals
    if ((this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[1][1] != 0) ||
        (this->board[0][2] == this->board[1][3] && this->board[1][3] == this->board[2][4] && this->board[1][3] != 0)) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Game1_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Game1_Board<T>::game_is_over() {
    return is_win() || is_draw();
}


//--------------------------------------


// Constructor for Game1_Player
template <typename T>
Game1_Player<T>::Game1_Player(string name, T symbol) : Player<T>(name, symbol)  {}

template <typename T>
void Game1_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x (0 to 2) and y (0 to 4) separated by spaces: \n"
            "Note that the cells {(0,0), (0,1), (0,3), (0,4), (1,0), (1,4)} are INVALID! ";
    cin >> x >> y;
}


//--------------------------------------


// Constructor for Game1_Random_Player
template <typename T>
Game1_Random_Player<T>::Game1_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->width = 3;
    this->length = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Game1_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->length;  // Random number between 0 and 4
    y = rand() % this->width;   // Random number between 0 and 2
    while (x == 0 && y == 0 || x == 0 && y == 1 || x == 0 && y == 3 || x == 0 && y == 4 || x == 1 && y == 0 || x == 1 && y == 4){
        x = rand() % this->length;
        y = rand() % this->width;
    }
}


//--------------------------------------


// Constructor for Game1_MinMax_Player
template <typename T>
Game1_MinMax_Player<T>::Game1_MinMax_Player(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
}

// Method to get the best move for the player
template <typename T>
void Game1_MinMax_Player<T>::getmove(int& x, int& y) {
    pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}

// Minimax algorithm to evaluate the board
template <typename T>
int Game1_MinMax_Player<T>::calculateMinMax(T s, bool isMaximizing) {
    // Base Case
    if (this->boardPtr->is_win()) {
        return isMaximizing ? -1 : 1;
    } else if (this->boardPtr->is_draw()) {
        return 0;
    }

    int bestValue = isMaximizing ? numeric_limits<int>::min() : numeric_limits<int>::max();
    T opponentSymbol = (s == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (i == 0 && j == 0 || i == 0 && j == 1 || i == 0 && j == 3 || i == 0 && j == 4 || i == 1 && j == 0 || i == 1 && j == 4){
                continue;
            }
            if (this->boardPtr->update_board(i, j, s)) {
                int value = calculateMinMax(opponentSymbol, !isMaximizing);
                this->boardPtr->update_board(i, j, 0); // Undo move

                if (isMaximizing) {
                    bestValue = max(bestValue, value);
                } else {
                    bestValue = min(bestValue, value);
                }
            }
        }
    }

    return bestValue;
}

// Find the best move using the minimax algorithm
template <typename T>
pair<int, int> Game1_MinMax_Player<T>::getBestMove() {
    int bestValue = std::numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};
    T opponentSymbol = (this->symbol == 'X') ? 'O' : 'X';

    // First, check if we can win in the next move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (i == 0 && j == 0 || i == 0 && j == 1 || i == 0 && j == 3 || i == 0 && j == 4 || i == 1 && j == 0 || i == 1 && j == 4){
                continue;
            }
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                if (this->boardPtr->is_win()) {
                    this->boardPtr->update_board(i, j, 0); // Undo move
                    return {i, j}; // Winning move found
                }
                this->boardPtr->update_board(i, j, 0); // Undo move
            }
        }
    }

    // Second, check if the opponent can win in their next move and block them
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (i == 0 && j == 0 || i == 0 && j == 1 || i == 0 && j == 3 || i == 0 && j == 4 || i == 1 && j == 0 || i == 1 && j == 4){
                continue;
            }
            if (this->boardPtr->update_board(i, j, opponentSymbol)) {
                if (this->boardPtr->is_win()) {
                    this->boardPtr->update_board(i, j, 0); // Undo move
                    return {i, j}; // Block opponent's winning move
                }
                this->boardPtr->update_board(i, j, 0); // Undo move
            }
        }
    }

    // If no immediate win or block, use MinMax to find the best move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (i == 0 && j == 0 || i == 0 && j == 1 || i == 0 && j == 3 || i == 0 && j == 4 || i == 1 && j == 0 || i == 1 && j == 4){
                continue;
            }
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                int moveValue = calculateMinMax(this->symbol, false);
                this->boardPtr->update_board(i, j, 0); // Undo move

                if (moveValue > bestValue) {
                    bestMove = {i, j};
                    bestValue = moveValue;
                }
            }
        }
    }

    return bestMove;
}


#endif //OOP_A2_T2_GAME1_H
