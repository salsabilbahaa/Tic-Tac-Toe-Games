#ifndef OOP_A2_T2_GAME4_H
#define OOP_A2_T2_GAME4_H

#include "BoardGame_Classes.h"
#include <set>

/// Word Tic-Tac-Toe
template <typename T>
class Game4_Board : public Board<T>{
public:
    Game4_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board ();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    void fileWords();
private:
    set<string> validWords;
};

template <typename T>
class Game4_Player : public Player<T> {
public:
    Game4_Player (string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class Game4_Random_Player : public RandomPlayer<T>{
public:
    Game4_Random_Player (T symbol);
    void getmove(int &x, int &y);
};




//---------------------- IMPLEMENTATION ----------------------




#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <limits>
#include <cctype>

using namespace std;

// Word Tic-Tac-Toe Board Constructor
template <typename T>
Game4_Board<T> :: Game4_Board(){
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    fileWords();
}

template <typename T>
bool Game4_Board<T> :: update_board(int x , int y , T mark){

    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && ((this->board[x][y] == 0 && isalpha(mark))
    || (this->board[x][y] != 0 && mark == 0))) {
        if (mark == 0){
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
void Game4_Board<T>::display_board() {
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

// Returns true if there is any winner
template<typename T>
bool Game4_Board<T>::is_win() {
    string word;

    // Check rows for valid words
    for (int i = 0; i < this->rows; ++i) {
        word = "";  // Reset word for each row
        for (int j = 0; j < this->columns; ++j) {
            if (this->board[i][j] == 0) {
                word = "";
                break;
            }
            word += this->board[i][j];
        }
        if (!word.empty() && validWords.find(word) != validWords.end()) {
            return true;
        }
    }

    // Check columns for valid words
    for (int j = 0; j < this->columns; ++j) {
        word = "";  // Reset word for each column
        for (int i = 0; i < this->rows; ++i) {
            if (this->board[i][j] == 0) {
                word = "";
                break;
            }
            word += this->board[i][j];
        }
        if (!word.empty() && validWords.find(word) != validWords.end()) {
            return true;
        }
    }

    // Check main diagonal for valid word
    word = "";
    for (int i = 0; i < this->rows; ++i) {
        if (this->board[i][i] == 0) {
            word = "";
            break;
        }
        word += this->board[i][i];
    }
    if (!word.empty() && validWords.find(word) != validWords.end()) {
        return true;
    }

    // Check anti-diagonal for valid word
    word = "";
    for (int i = 0; i < this->rows; ++i) {
        if (this->board[i][this->columns - 1 - i] == 0) {
            word = "";
            break;
        }
        word += this->board[i][this->columns - 1 - i];
    }
    if (!word.empty() && validWords.find(word) != validWords.end()) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Game4_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Game4_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
void Game4_Board<T>::fileWords() {
    ifstream inputFile("dic.txt");
    string word;
    while (inputFile >> word){
        validWords.insert(word);
    }
    inputFile.close();
}


//--------------------------------------


// Constructor for Game4_Player
template <typename T>
Game4_Player<T>::Game4_Player(string name, T symbol) : Player<T>(name, symbol)  {}

template <typename T>
void Game4_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x (0 to 2) and y (0 to 2) separated by spaces: \n";
    cin >> x >> y;
    cout << "Please enter the letter you want to play.\n";
    T letter;
    cin >> letter;
    this->symbol = letter;
}


//--------------------------------------


// Constructor for Game4_Random_Player
template <typename T>
Game4_Random_Player<T>::Game4_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Game4_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    this->symbol = 'A' + rand() % 26;
}


//--------------------------------------


#endif //OOP_A2_T2_GAME4_H
