#ifndef _4X4X_O_H
#define _4X4X_O_H

#include "BoardGame_Classes.h"

int altPlayer = 1;
int iStart, jStart, iEnd, jEnd;

template <typename T>
class X_O_4x4_Board:public Board<T> {
public:
    X_O_4x4_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    Player<T>* players[2];
    bool check_win(char mark);
    void startMove(int& w, int& z);
    void RandomStartMove(int& w, int& z);
    void setBoardCell(int x, int y, char mark);
};

template <typename T>
class X_O_4x4_Player : public Player<T> {
public:
    X_O_4x4_Player (string name, T symbol);
    void getmove(int& x, int& y);

};

template <typename T>
class X_O_4x4_Random_Player : public RandomPlayer<T>{
public:
    X_O_4x4_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_4x4_Board
template <typename T>
X_O_4x4_Board<T>::X_O_4x4_Board() {
    this->rows = this->columns = 4;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            if ((i == 0 && j == 0) || (i == 0 && j == 2) || (i == 3 && j == 1) || (i == 3 && j == 3)){
                this->board[i][j] = 'O';
            }
            else if ((i == 0 && j == 1) || (i == 0 && j == 3) || (i == 3 && j == 0) || (i == 3 && j == 2)){
                this->board[i][j] = 'X';
            }
            else {
                this->board[i][j] = 0;
            }
        }
    }
    this->n_moves = 0;
}

template <typename T>
void X_O_4x4_Board<T>::setBoardCell(int x, int y, char mark) {
    this->board[x][y] = mark;
}

template <typename T>
bool X_O_4x4_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
            this->board[iStart][jStart] = 0;
            altPlayer *= -1;
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void X_O_4x4_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
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
bool X_O_4x4_Board<T>::check_win(char mark)
{
    //rows
    for (int i = 0; i < this->rows; i++){
        for (int j = 0; j <= this->columns - 3; j++){
            if (this->board[i][j] == mark &&
                this->board[i][j+1] == mark &&
                this->board[i][j+2] == mark) {
                return true;

            }
        }
    }

    //cols
    for (int i = 0; i <= this->rows - 3; i++){
        for (int j = 0; j < this->columns; j++){
            if (this->board[i][j] == mark &&
                this->board[i+1][j] == mark &&
                this->board[i+2][j] == mark) {
                return true;
            }
        }
    }

    //diagonals
    for (int i = 0; i <= this->rows - 3; i++){
        for (int j = 0; j <= this->columns - 3; j++){
            if (this->board[i][j] == mark &&
                this->board[i+1][j+1] == mark &&
                this->board[i+2][j+2] == mark) {
                return true;
            }
        }
    }

    //anti-diagonals
    for (int i = 0; i <= this->rows - 3; i++){
        for (int j = 2; j < this->columns; j++){
            if (this->board[i][j] == mark &&
                this->board[i+1][j-1] == mark &&
                this->board[i+2][j-2] == mark) {
                return true;
            }
        }
    }
    return false ;

}

// Returns true if there is any winner
template <typename T>
bool X_O_4x4_Board<T>::is_win() {
    return check_win('X') || check_win('O');
}

template <typename T>
bool X_O_4x4_Board<T>::is_draw() {
    return false;
}

template <typename T>
bool X_O_4x4_Board<T>::game_is_over() {
    return is_win();
}

template<typename T>
void X_O_4x4_Board<T>::startMove(int& w, int& z)
{
    here:
    cout << "\nPlease enter your starting position x and y (0 to 3) separated by spaces: ";
    cin >> iStart >> jStart;

    if (altPlayer == 1 && this->board[iStart][jStart] == 'O'){
        goto here;
    }
    else if (altPlayer == -1 && this->board[iStart][jStart] == 'X'){
        goto here;
    }


}

template <typename T>
void X_O_4x4_Board<T>::RandomStartMove(int& w, int& z)
{
    vector<pair<int, int>> startPos;
    vector<pair<int, int>> endPos;
    char mark = altPlayer == 1 ? 'X' : 'O';

    for (int i = 0; i < this->rows; i++){
        for (int j = 0; j < this->columns; j++){
            if (this->board[i][j] == mark){
                startPos.emplace_back(i, j);
            }
        }
    }

    int randPos = rand() % startPos.size();
    iStart = startPos[randPos].first;
    jStart = startPos[randPos].second;

    this->board[iStart][jStart] = 0;

    if (iStart - 1 >= 0 && this->board[iStart - 1][jStart] == 0){
        endPos.emplace_back(iStart - 1, jStart);
    }
    if (iStart + 1 < this->rows && this->board[iStart + 1][jStart] == 0){
        endPos.emplace_back(iStart + 1, jStart);
    }
    if (jStart - 1 >= 0 && this->board[iStart][jStart - 1] == 0){
        endPos.emplace_back(iStart, jStart - 1);
    }
    if (jStart + 1 < this->columns && this->board[iStart][jStart + 1] == 0){
        endPos.emplace_back(iStart, jStart + 1);
    }

    int randEnd = rand() % endPos.size();
    iEnd = endPos[randEnd].first;
    jEnd = endPos[randEnd].second;

    this->board[iEnd][jEnd] = mark;
}


//--------------------------------------

// Constructor for X_O_4x4_Player
template <typename T>
X_O_4x4_Player<T>::X_O_4x4_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_4x4_Player<T>::getmove(int& x, int& y) {
    X_O_4x4_Board<T> b;
    b.startMove(iStart, jStart);
    here:
    cout << "\nPlease enter your new position x and y (0 to 3) separated by spaces: ";
    cin >> x >> y;
    if (!(x == iStart + 1 && y == jStart) &&
        !(x == iStart - 1 && y == jStart) &&
        !(x == iStart && y == jStart + 1) &&
        !(x == iStart && y == jStart - 1)) {
        goto here;
    }

}

// Constructor for X_O_4x4_Random_Player
template <typename T>
X_O_4x4_Random_Player<T>::X_O_4x4_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void X_O_4x4_Random_Player<T>::getmove(int& x, int& y) {
    X_O_4x4_Board<T> b;
    b.RandomStartMove(iStart, jStart);
    x = iEnd;
    y = jEnd;

}







#endif //_4X4X_O_H
