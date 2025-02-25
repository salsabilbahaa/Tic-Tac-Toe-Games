#ifndef _5X5X_O_H
#define _5X5X_O_H

#include "BoardGame_Classes.h"
#include <ctime>
#include <iomanip>


using namespace std;


template <typename T>
class X_O_5x5_Board : public Board<T> {
public:
    X_O_5x5_Board();
    bool update_board (int x , int y , T symbol);
    void display_board();
    int count_seq(char mark);
    bool is_win();
    bool is_draw();
    bool game_is_over();
    Player<T>* players[2];

};

template <typename T>
class X_O_5x5_Player : public Player<T> {
public:
    X_O_5x5_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class X_O_5x5_Random_Player : public RandomPlayer<T>{
public:
    X_O_5x5_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};

//////////////////////////////////////////////

#include <iostream>

using namespace std;

template <typename T>
X_O_5x5_Board<T>::X_O_5x5_Board()
{

    this->n_moves = 0;
    this->rows = 5;
    this->columns = 5;
    this->board = new char*[5];

    for (int i = 0; i < 5; i++){
        this->board[i] = new char[5];
        for (int j = 0; j < 5; j++){
            this->board[i][j] = 0;
        }
    }
}


template <typename T>
bool X_O_5x5_Board<T>::update_board(int x, int y, T mark)
{
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        cout << "Updated (" << x << "," << y << ") to " << this->board[x][y] << "\n";
        return true;
    }
    return false;
}



template <typename T>
void X_O_5x5_Board<T>::display_board()
{
    for (int i = 0; i < 5; i++)
    {
        cout << "\n| ";
        for (int j = 0; j < 5; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}


template <typename T>
int X_O_5x5_Board<T>::count_seq(char mark)
{
    int cnt = 0;

    //rows
    for (int i = 0; i < this->rows; i++){
        for (int j = 0; j <= this->columns - 3; j++){
            if (this->board[i][j] == mark &&
                this->board[i][j+1] == mark &&
                this->board[i][j+2] == mark) {
                cnt++;

            }
        }
    }

    //cols
    for (int i = 0; i <= this->rows - 3; i++){
        for (int j = 0; j < this->columns; j++){
            if (this->board[i][j] == mark &&
                this->board[i+1][j] == mark &&
                this->board[i+2][j] == mark) {
                cnt++;
            }
        }
    }

    //diagonals
    for (int i = 0; i <= this->rows - 3; i++){
        for (int j = 0; j <= this->columns - 3; j++){
            if (this->board[i][j] == mark &&
                this->board[i+1][j+1] == mark &&
                this->board[i+2][j+2] == mark) {
                cnt++;
            }
        }
    }

    //anti-diagonals
    for (int i = 0; i <= this->rows - 3; i++){
        for (int j = 2; j < this->columns; j++){
            if (this->board[i][j] == mark &&
                this->board[i+1][j-1] == mark &&
                this->board[i+2][j-2] == mark) {
                cnt++;
            }
        }
    }

    return cnt;
}

template <typename T>
bool X_O_5x5_Board<T>::is_win()
{
    int xCount = count_seq('X');
    int oCount = count_seq('O');

    if (this->n_moves == 24){
        if (oCount > xCount){
            return true;
        }
        else if (xCount > oCount){
            cout << players[0]->getname() << " wins\n";
        }
    }
    return false;
}

template <typename T>
bool X_O_5x5_Board<T>::is_draw() {
    if (this->n_moves == 24) {
        int xCount = count_seq('X');
        int oCount = count_seq('O');

        return xCount == oCount;
    }
    return false;
}

template <typename T>
bool X_O_5x5_Board<T>::game_is_over()
{
    int xCount = count_seq('X');
    int oCount = count_seq('O');

    if (this->n_moves ==  24 && xCount > oCount){
        return true;
    }
    return is_win() || is_draw();
}

template <typename T>
X_O_5x5_Player<T>::X_O_5x5_Player(string name, T symbol) : Player<T>(name, symbol) {}


template <typename T>
void X_O_5x5_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

template <typename T>
X_O_5x5_Random_Player<T>::X_O_5x5_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void X_O_5x5_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}


#endif // _5X5X_O_H
