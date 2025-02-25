

#ifndef UNTITLED44_FOURINAROW_BOARD_H
#define UNTITLED44_FOURINAROW_BOARD_H


#include "BoardGame_Classes.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
class FourInARow_Board : public Board<char> {
public:
    FourInARow_Board();
    bool update_board(int column,int y ,T symbol );
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    bool isValidPlace(int position) ;

};

template <typename T>
class FourInARow_Player : public Player<T> {
public:
    FourInARow_Player(const string& name, T symbol);
    void getmove(int& column, int& y);
};

template <typename T>
class FourInARow_Random_Player : public RandomPlayer<T> {
public:
    FourInARow_Random_Player(T symbol);

    void getmove(int& column, int& y);
};

// ---------------------------- IMPLEMENTATION ----------------------------

template <typename T>
FourInARow_Board<T>::FourInARow_Board() {
    this->rows = 6;
    this->columns = 7;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' '; 
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool FourInARow_Board<T>::update_board(int column,  int y,T symbol ) {
    if (column < 0 || column >= this->columns) return false;

    for (int r = 0; r < this->rows; r++) {
        if (this->board[r][column] == ' ') {
            this->board[r][column] = symbol;
            this->n_moves++;
            return true;
        }
    }
    return false;
}

template <typename T>
void FourInARow_Board<T>::display_board() {
    for (int r = this->rows - 1; r >= 0; --r) {
        cout << "| ";
        for (int c = 0; c < this->columns; ++c) {
            cout << this->board[r][c] << " | ";
        }
        cout << endl;
    }
    cout << "-----------------------------\n";
    cout << "  0   1   2   3   4   5   6\n";
}

template <typename T>
bool FourInARow_Board<T>::is_win() {
    // Check horizontal, vertical, and diagonal for a winner
    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->columns - 3; c++) {
            if (this->board[r][c] != ' ' &&
                this->board[r][c] == this->board[r][c + 1] &&
                this->board[r][c] == this->board[r][c + 2] &&
                this->board[r][c] == this->board[r][c + 3]) {
                return true;
            }
        }
    }

    for (int c = 0; c < this->columns; c++) {
        for (int r = 0; r < this->rows - 3; r++) {
            if (this->board[r][c] != ' ' &&
                this->board[r][c] == this->board[r + 1][c] &&
                this->board[r][c] == this->board[r + 2][c] &&
                this->board[r][c] == this->board[r + 3][c]) {
                return true;
            }
        }
    }

    for (int r = 0; r < this->rows - 3; r++) {
        for (int c = 0; c < this->columns - 3; c++) {
            if (this->board[r][c] != ' ' &&
                this->board[r][c] == this->board[r + 1][c + 1] &&
                this->board[r][c] == this->board[r + 2][c + 2] &&
                this->board[r][c] == this->board[r + 3][c + 3]) {
                return true;
            }
        }
    }

    for (int r = 3; r < this->rows; r++) {
        for (int c = 0; c < this->columns - 3; c++) {
            if (this->board[r][c] != ' ' &&
                this->board[r][c] == this->board[r - 1][c + 1] &&
                this->board[r][c] == this->board[r - 2][c + 2] &&
                this->board[r][c] == this->board[r - 3][c + 3]) {
                return true;
            }
        }
    }

    return false;
}

template <typename T>
bool FourInARow_Board<T>::is_draw() {
    return this->n_moves == this->rows * this->columns && !is_win();
}

template <typename T>
bool FourInARow_Board<T>::game_is_over() {
    return is_win() || is_draw();
}



template <typename T>
bool FourInARow_Board<T>::isValidPlace(int position) {

    int row = (position - 1) / this->columns;
    int col = (position - 1) % this->columns;


    return this->board[row][col] == ' ';
}

template <typename T>
FourInARow_Player<T>::FourInARow_Player(const string& name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void FourInARow_Player<T>::getmove(int& column, int& y) {
    cout << this->getname() << " (" << this->getsymbol() << "), enter column: ";
    cin >> column;
}

template <typename T>
FourInARow_Random_Player<T>::FourInARow_Random_Player(T symbol): RandomPlayer<T>(symbol)
{
    srand(static_cast<unsigned int>(time(0))); 
}


template <typename T>
void FourInARow_Random_Player<T>::getmove(int& column, int& y) {

        column = rand() % 7; // Random column between 0 and 6

}


#endif //UNTITLED44_FOURINAROW_BOARD_H
