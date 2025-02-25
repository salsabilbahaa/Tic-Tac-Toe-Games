#ifndef OOP_A2_T2_GAME8_H
#define OOP_A2_T2_GAME8_H

#include "BoardGame_Classes.h"
#include <map>

/// Ultimate tic-tac-toe
template <typename T>
class Game8_Board:public Board<T> {
public:
    Game8_Board ();
    bool update_board (int x, int y, T symbol);
    void display_board ();
    bool isWinSmallBoard();
    bool isDrawSmallBoard();
    bool canChooseBigCell();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    void setBigRow(int bigRow);
    void setBigColumn(int bigColumn);
    int getBigRow();
    int getBigColumn();
    char getBigCellValue(int i, int j);
private:
    bool isFirstTurn;
    int bigRow, bigColumn;
    map<pair<int,int>,T> isBigCellClosed; // the pair will contain bigRow, bigColumn indices.
    map<pair<int,int>,pair<int,int>> bigCellIndices; // to tell the next player which board he will play in.
};

template <typename T>
class Game8_Player:public Player<T> {
public:
    Game8_Player(string name, T symbol, Game8_Board<T>* boardPtr);
    void getmove(int& x, int& y);
private:
    Game8_Board<T>* game8BoardPtr;
};

template <typename T>
class Game8_Random_Player : public RandomPlayer<T>{
public:
    Game8_Random_Player (T symbol, Game8_Board<T>* boardPtr);
    void getmove(int &x, int &y) ;
private:
    Game8_Board<T>* game8BoardPtr;
};

//---------------------- IMPLEMENTATION ----------------------


#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for Game8_Board
template <typename T>
Game8_Board<T>::Game8_Board() {
    this->rows = this->columns = 3*3; // 9*9 grid
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; ++j) {
            this->board[i][j] = 0;
        }
    }
    this->isFirstTurn = true;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            isBigCellClosed[{i, j}] = 0; // Initialize to zero
        }
    }
}

template <typename T>
bool Game8_Board<T>::update_board(int x, int y, T symbol) {
    // Change coordinates to 9*9
    int currX = bigRow*3 + x;
    int currY = bigColumn*3 + y;

    // Only update if move is valid
    if (!(currX < 0 || currX > this->rows || currY < 0 || currY > this->columns) && (this->board[currX][currY] == 0 || symbol == 0)){
        if (symbol == 0){
            this->n_moves--;
            this->board[currX][currY] = 0;
        }
        else {
            this->n_moves++;
            this->board[currX][currY] = toupper(symbol);
        }

        // Check if a Big Cell will be closed.
        if (isWinSmallBoard()){
            isBigCellClosed[{bigRow, bigColumn}] = symbol;
        }
        else if (isDrawSmallBoard()){
            isBigCellClosed[{bigRow, bigColumn}] = 'D';
        }

        bigRow = x;
        bigColumn = y;

        return true;
    }
    return false;
}

template <typename T>
void Game8_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i%3 << "," << j%3 << ")";
            cout << setw(2) << this->board[i][j];
            if (j%3 == 2){
                cout << " *|* ";
            }
            else {
                cout << " |";
            }
        }

        if (i%3 == 2) {
            cout << "\n*****************************|*****************************|*****************************|*";
        }
        else {
            cout << "\n----------------------------*|*---------------------------*|*---------------------------*|*";
        }
    }
    cout << endl;
}

template<typename T>
bool Game8_Board<T>::canChooseBigCell() {
    if (this->isFirstTurn){
        this->isFirstTurn = false;
        return true;
    }
    else if (isBigCellClosed[{bigRow, bigColumn}] != 0) {
        return true;
    }
    else {
        return false;
    }
}

template<typename T>
bool Game8_Board<T>::isWinSmallBoard() {
    int startX = bigRow*3;
    int startY = bigColumn*3;

    // Check for rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((this->board[startX + i][startY] == this->board[startX + i][startY + 1] &&
            this->board[startX + i][startY + 1] == this->board[startX + i][startY + 2] &&
            this->board[startX + i][startY] != 0) ||
            (this->board[startX][startY + i] == this->board[startX + 1][startY + i] &&
            this->board[startX + 1][startY + i] == this->board[startX + 2][startY + i] &&
            this->board[startX][startY + i] != 0)) {
            return true;
        }
    }

    // Check for diagonals
    if ((this->board[startX][startY] == this->board[startX+1][startY+1] &&
        this->board[startX+1][startY+1] == this->board[startX+2][startY+2] &&
        this->board[startX][startY] != 0) ||
        (this->board[startX][startY+2] == this->board[startX+1][startY+1] &&
        this->board[startX+1][startY+1] == this->board[startX+2][startY] &&
        this->board[startX][startY+2] != 0)) {
        return true;
    }

    return false;
}

template<typename T>
bool Game8_Board<T>::isDrawSmallBoard() {
    bool isMoves9 = true;
    int startX = bigRow*3;
    int startY = bigColumn*3;

    // Check if all cells of the small board is filled.
    for (int i = startX; i < startX + 3; ++i) {
        for (int j = startY; j < startY + 3; ++j) {
            if (this->board[i][j] == 0){
                isMoves9 = false;
                break;
            }
        }
        if (!isMoves9){
            break;
        }
    }
    return (isMoves9 && !isWinSmallBoard());
}

template <typename T>
bool Game8_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((isBigCellClosed[{i,0}] == isBigCellClosed[{i,1}] && isBigCellClosed[{i,1}] == isBigCellClosed[{i,2}] && isBigCellClosed[{i,0}] != 0 && isBigCellClosed[{i,0}] != 'D') ||
        (isBigCellClosed[{0,i}] == isBigCellClosed[{1,i}] && isBigCellClosed[{1,i}] == isBigCellClosed[{2,i}] && isBigCellClosed[{0,i}] != 0 && isBigCellClosed[{0,i}] != 'D')) {
            return true;
        }
    }

    // Check diagonals
    if ((isBigCellClosed[{0,0}] == isBigCellClosed[{1,1}] && isBigCellClosed[{1,1}] == isBigCellClosed[{2,2}] && isBigCellClosed[{0,0}] != 0 && isBigCellClosed[{0,0}] != 'D') ||
            (isBigCellClosed[{0,2}] == isBigCellClosed[{1,1}] && isBigCellClosed[{1,1}] == isBigCellClosed[{2,0}] && isBigCellClosed[{0,2}] != 0 && isBigCellClosed[{0,2}] != 'D')) {
        return true;
    }

    return false;
}

template<typename T>
bool Game8_Board<T>::is_draw() {
    bool isAllClosed = true;
    for (auto i : isBigCellClosed) {
        if (i.second == 0){
            isAllClosed = false;
        }
    }

    return isAllClosed && !is_win();
}

template <typename T>
bool Game8_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template<typename T>
void Game8_Board<T>::setBigRow(int row) {
    bigRow = row;
}

template<typename T>
void Game8_Board<T>::setBigColumn(int column) {
    bigColumn = column;
}

template<typename T>
int Game8_Board<T>::getBigRow() {
    return bigRow;
}

template<typename T>
int Game8_Board<T>::getBigColumn() {
    return bigColumn;
}

template<typename T>
char Game8_Board<T>::getBigCellValue(int i, int j) {
    return isBigCellClosed[{i,j}];
}
// -----------------------------------

template <typename T>
Game8_Player<T>::Game8_Player(string name, T symbol, Game8_Board<T>* boardPtr)
            : Player<T>(name, symbol), game8BoardPtr(boardPtr) {}

template <typename T>
void Game8_Player<T>::getmove(int &x, int &y) {
    if (this->game8BoardPtr->canChooseBigCell()) {
        int bigRow, bigColumn;
        cout << "Please enter indices of the Big Cell.\n"
                "Big Row (from 0 to 2): ";
        cin >> bigRow;
        cout << "Big Column (from 0 to 2): ";
        cin >> bigColumn;

        this->game8BoardPtr->setBigRow(bigRow);
        this->game8BoardPtr->setBigColumn(bigColumn);
    }
    cout << "\nYou will play in the Big Cell of indices: (" << this->game8BoardPtr->getBigRow() << "," <<
    this->game8BoardPtr->getBigColumn() << ")\n";
    cout << "Please enter indices of the Small Cell.\n"
            "Small Row (from 0 to 2): ";
    cin >> x;
    cout << "Small Column (from 0 to 2): ";
    cin >> y;
}

// -----------------------------------

template<typename T>
Game8_Random_Player<T>::Game8_Random_Player(T symbol, Game8_Board<T> *boardPtr):RandomPlayer<T>(symbol), game8BoardPtr(boardPtr) {
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}


template<typename T>
void Game8_Random_Player<T>::getmove(int &x, int &y) {
    if (this->game8BoardPtr->canChooseBigCell()) {
        int bigRow, bigColumn;

        do {
            bigRow = rand() % 3;
            bigColumn = rand() % 3;
        } while (this->game8BoardPtr->getBigCellValue(bigRow, bigColumn) != 0);

        this->game8BoardPtr->setBigRow(bigRow);
        this->game8BoardPtr->setBigColumn(bigColumn);
    }
    x = rand() % 3;
    y = rand() % 3;
}

#endif //OOP_A2_T2_GAME8_H
