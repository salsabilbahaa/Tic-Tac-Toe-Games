
#ifndef _3X3X_O_Mis_H
#define _3X3X_O_Mis_H

#include "BoardGame_Classes.h"

bool loser = false;

template <typename T>
class Game6_Board:public Board<T> {
public:
    Game6_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    Player<T>* players[2];
    int altPlayer = 1;
};

template <typename T>
class Game6_Player : public Player<T> {
public:
    Game6_Player (string name, T symbol);
    void getmove(int& x, int& y);

};

template <typename T>
class Game6_Random_Player : public RandomPlayer<T>{
public:
    Game6_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
Game6_Board<T>::Game6_Board()
{
    loser = false;
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Game6_Board<T>::update_board(int x, int y, T mark)
{
    if (loser){
        return true;
    }

    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0))
    {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
            altPlayer *= -1;
          }
        return true;
    }

    return false;
}


template <typename T>
void Game6_Board<T>::display_board()
{
    for (int i = 0; i < this->rows; i++){
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;

}

template <typename T>
bool Game6_Board<T>::is_win()
{
    if (loser){
        if (altPlayer == 1){
            cout << players[0]->getname() << " wins\n";
        }
        return true;
    }
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            loser = true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        loser = true;
    }
    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Game6_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Game6_Board<T>::game_is_over() {
    if (is_win()){
        return true;
    }
    return (is_draw());
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
Game6_Player<T>::Game6_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Game6_Player<T>::getmove(int& x, int& y) {
    if (loser){
        return;
    }
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
Game6_Random_Player<T>::Game6_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Game6_Random_Player<T>::getmove(int& x, int& y) {
    if (loser){
        return;
    }
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}







#endif //_3X3X_O_Mis_H
