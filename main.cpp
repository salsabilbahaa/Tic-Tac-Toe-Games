#include <iostream>
#include "BoardGame_Classes.h"
#include "Game1.h"
#include "Game4.h"
#include "Game8.h"
#include "FourInARow_Board.h"
#include "NumberTicTacToe.h"
#include "5x5X_O.h"
#include "3x3X_O_Mis.h"
#include "4x4X_O.h"

using namespace std;

int main() {
    Player<char>* players[2];
    while (true) {
        cout << "------ Welcome to Tic-Tac-Toe Games -----\n"
                "Choose the number of the game you want to play:\n"
                "1) Pyramid Tic-Tac-Toe.\n"
                "2) Four-in-a-row Tic-Tac-Toe.\n"
                "3) 5x5 Tic Tac Toe.\n"
                "4) Word Tic-Tac-Toe.\n"
                "5) Numerical Tic-Tac-Toe.\n"
                "6) Misere Tic Tac Toe.\n"
                "7) 4x4 Tic-Tac-Toe.\n"
                "8) Ultimate Tic Tac Toe\n"
                "9) Exit.\n";
        string gameNum;
        cin >> gameNum;

        if (gameNum == "1") {
            Game1_Board<char>* B = new Game1_Board<char>();
            string player1Name, player2Name, playerType;

            // Set up player 1
            cout << "Enter Player X name: ";
            cin >> player1Name;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer (AI)\n";
            cin >> playerType;

            while (playerType != "1" && playerType != "2" && playerType != "3"){
                cout << "Please enter a valid choice (from 1 to 3).\n";
                cin >> playerType;
            }
            if (playerType == "1"){
                players[0] = new Game1_Player<char>(player1Name, 'X');
            }
            else if (playerType == "2"){
                players[0] = new Game1_Random_Player<char>('X');
            }
            else if (playerType == "3"){
                players[0] = new Game1_MinMax_Player<char>('X');
                players[0]->setBoard(B);
            }

            // Set up player 2
            cout << "Enter Player O name: ";
            cin >> player2Name;
            cout << "Choose Player O type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cout << "3. Smart Computer (AI)\n";
            cin >> playerType;

            while (playerType != "1" && playerType != "2" && playerType != "3"){
                cout << "Please enter a valid choice (from 1 to 3).\n";
                cin >> playerType;
            }
            if (playerType == "1"){
                players[1] = new Game1_Player<char>(player1Name, 'O');
            }
            else if (playerType == "2"){
                players[1] = new Game1_Random_Player<char>('O');
            }
            else if (playerType == "3"){
                players[1] = new Game1_MinMax_Player<char>('O');
                players[1]->setBoard(B);
            }

            // Create the game manager and run the game
            GameManager<char> game1(B, players);
            game1.run();

            // Clean up
            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
        }
        else if (gameNum == "2") {

            FourInARow_Board<char>* F = new FourInARow_Board<char>();
            string player1Name, player2Name, playerType;


            cout << "Enter Player X name: ";
            cin >> player1Name;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> playerType;

            while (playerType != "1" && playerType != "2" && playerType != "3") {
                cout << "Please enter a valid choice (from 1 to 3).\n";
                cin >> playerType;
            }
            if (playerType == "1") {
                players[0] = new FourInARow_Player<char>(player1Name, 'X');
            }
            else if (playerType == "2") {
                players[0] = new FourInARow_Random_Player<char>( 'X');
            }


            cout << "Enter Player O name: ";
            cin >> player2Name;
            cout << "Choose Player O type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> playerType;

            while (playerType != "1" && playerType != "2" && playerType != "3") {
                cout << "Please enter a valid choice (from 1 to 3).\n";
                cin >> playerType;
            }
            if (playerType == "1") {
                players[1] = new FourInARow_Player<char>(player2Name, 'O');
            }
            else if (playerType == "2") {
                players[1] = new FourInARow_Random_Player<char>( 'O');
            }

            GameManager<char> fourInARow(F, players);
            fourInARow.run();

            delete F;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
        }
        else if (gameNum == "3")
        {
            Player<char>* players[2];
            X_O_5x5_Board<char>* B = new X_O_5x5_Board<char>();
            string playerXName, playerOName;
            int choice;

            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch(choice) {
                case 1:
                    players[0] = new X_O_5x5_Player<char>(playerXName, 'X');
                    break;
                case 2:
                    players[0] = new X_O_5x5_Random_Player<char>('X');
                    break;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                    return 1;
            }

            cout << "Enter Player 2 name: ";
            cin >> playerOName;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch(choice) {
                case 1:
                    players[1] = new X_O_5x5_Player<char>(playerOName, 'O');
                    break;
                case 2:
                    players[1] = new X_O_5x5_Random_Player<char>('O');
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    return 1;
            }

            B->players[0] = players[0];
            B->players[1] = players[1];

            GameManager<char> x_o_game(B, players);
            x_o_game.run();

            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
        }
        else if (gameNum == "4"){
            Game4_Board<char>* B = new Game4_Board<char>();
            string player1Name, player2Name, playerType;

            // Set up player 1
            cout << "Enter Player 1 name: ";
            cin >> player1Name;
            cout << "Choose Player 1 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> playerType;

            while (playerType != "1" && playerType != "2"){
                cout << "Please enter a valid choice (1 or 2).\n";
                cin >> playerType;
            }
            if (playerType == "1"){
                players[0] = new Game4_Player<char>(player1Name, 'X');
            }
            else if (playerType == "2"){
                players[0] = new Game4_Random_Player<char>('X');
            }

            // Set up player 2
            cout << "Enter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> playerType;

            while (playerType != "1" && playerType != "2"){
                cout << "Please enter a valid choice (1 or 2).\n";
                cin >> playerType;
            }
            if (playerType == "1"){
                players[1] = new Game4_Player<char>(player2Name, 'O');
            }
            else if (playerType == "2"){
                players[1] = new Game4_Random_Player<char>('O');
            }

            // Create the game manager and run the game
            GameManager<char> game4(B, players);
            game4.run();

            // Clean up
            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
        }
        else if (gameNum == "5") {
            NumberTicTacToe<int>* B = new NumberTicTacToe<int>();
            Player<int>* players[2];
            string player1Name, player2Name, playerType;


            vector<int> player1Numbers = {1, 3, 5, 7, 9};
            vector<int> player2Numbers = {2, 4, 6, 8};


            cout << "Choose Player 1 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> playerType;

            while (playerType != "1" && playerType != "2") {
                cout << "Please enter a valid choice (1 or 2).\n";
                cin >> playerType;
            }
            if (playerType == "1") {
                cout << "Enter Player 1 name: ";
                cin >> player1Name;
                players[0] = new HumanPlayer<int>(player1Name, 'X');
            } else {
                players[0] = new N_RandomPlayer<int>('X',B);
            }

            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> playerType;

            while (playerType != "1" && playerType != "2") {
                cout << "Please enter a valid choice (1 or 2).\n";
                cin >> playerType;
            }
            if (playerType == "1") {
                cout << "Enter Player 2 name: ";
                cin >> player2Name;
                players[1] = new HumanPlayer<int>(player2Name, 'O');
            } else {
                players[1] = new N_RandomPlayer<int>('O',B);
            }

            players[0]->setBoard(B);
            players[1]->setBoard(B);

            bool gameOver = false;
            int currentPlayer = 0;

            while (!B->game_is_over()) {
                B->display_board();

                cout << players[currentPlayer]->getname() << "'s turn.\n";
                cout << "Available numbers: ";
                vector<int>& availableNumbers = (currentPlayer == 0) ? player1Numbers : player2Numbers;
                for (int num : availableNumbers) {
                    cout << num << " ";
                }
                cout << endl;

                int row, col, number;

                if (dynamic_cast<N_RandomPlayer<int>*>(players[currentPlayer])) {
                    N_RandomPlayer<int>* randomPlayer = dynamic_cast<N_RandomPlayer<int>*>(players[currentPlayer]);
                    randomPlayer->getmove(row, col);

                    number = availableNumbers[rand() % availableNumbers.size()];
                    cout << "Randomly selected number: " << number << endl;
                } else {

                    players[currentPlayer]->getmove(row, col);


                    cout << "Enter the number you want to place: ";
                    cin >> number;

                    while (find(availableNumbers.begin(), availableNumbers.end(), number) == availableNumbers.end()) {
                        cout << "Invalid number. Choose a valid number from your available numbers.\n";
                        cin >> number;
                    }
                }


                if (B->isValidPlace(row * 3 + col + 1)) {
                    B->makeMove(row * 3 + col + 1, number);
                    availableNumbers.erase(remove(availableNumbers.begin(), availableNumbers.end(), number), availableNumbers.end());
                } else {
                    cout << "Invalid move. Try again.\n";
                    continue;
                }

                if (B->is_win()) {
                    B->display_board();
                    cout << players[currentPlayer]->getname() << " wins!\n";
                    gameOver = true;
                    break;
                }


                currentPlayer = 1 - currentPlayer;
            }

            if (!gameOver) {
                cout << "It's a draw!\n";
            }


            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
        }
        else if (gameNum == "6"){
            Player<char>* players[2];
            Game6_Board<char>* B = new Game6_Board<char>();
            string playerXName, playerOName;
            int choice;

            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch(choice) {
                case 1:
                    players[0] = new Game6_Player<char>(playerXName, 'X');
                    break;
                case 2:
                    players[0] = new Game6_Random_Player<char>('X');
                    break;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                    return 1;
            }

            cout << "Enter Player 2 name: ";
            cin >> playerOName;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch(choice) {
                case 1:
                    players[1] = new Game6_Player<char>(playerOName, 'O');
                    break;
                case 2:
                    players[1] = new Game6_Random_Player<char>('O');
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    return 1;
            }

            B->players[0] = players[0];
            B->players[1] = players[1];

            GameManager<char> x_o_game(B, players);
            x_o_game.run();

            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
        }
        else if (gameNum == "7"){
            Player<char>* players[2];
            X_O_4x4_Board<char>* B = new X_O_4x4_Board<char>();
            string playerXName, playerOName;
            int choice;

            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch(choice) {
                case 1:
                    players[0] = new X_O_4x4_Player<char>(playerXName, 'X');
                    break;
                case 2:
                    players[0] = new X_O_4x4_Random_Player<char>('X');
                    break;
                default:
                    cout << "Invalid choice for Player 1. Exiting the game.\n";
                    return 1;
            }

            cout << "Enter Player 2 name: ";
            cin >> playerOName;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch(choice) {
                case 1:
                    players[1] = new X_O_4x4_Player<char>(playerOName, 'O');
                    break;
                case 2:
                    players[1] = new X_O_4x4_Random_Player<char>('O');
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    return 1;
            }

            B->players[0] = players[0];
            B->players[1] = players[1];

            GameManager<char> x_o_game(B, players);
            x_o_game.run();

            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
        }
        else if (gameNum == "8"){
            Game8_Board<char>* B = new Game8_Board<char>();
            string player1Name, player2Name, playerType;

            // Set up player 1
            cout << "Enter Player 1 name: ";
            cin >> player1Name;
            cout << "Choose Player 1 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> playerType;

            while (playerType != "1" && playerType != "2"){
                cout << "Please enter a valid choice (1 or 2).\n";
                cin >> playerType;
            }
            if (playerType == "1"){
                players[0] = new Game8_Player<char>(player1Name, 'X',B);
            }
            else if (playerType == "2"){
                players[0] = new Game8_Random_Player<char>('X', B);
            }

            // Set up player 2
            cout << "Enter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> playerType;

            while (playerType != "1" && playerType != "2"){
                cout << "Please enter a valid choice (1 or 2).\n";
                cin >> playerType;
            }
            if (playerType == "1"){
                players[1] = new Game8_Player<char>(player2Name, 'O', B);
            }
            else if (playerType == "2"){
                players[1] = new Game8_Random_Player<char>('O', B);
            }

            // Create the game manager and run the game
            GameManager<char> game8(B, players);
            game8.run();

            // Clean up
            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }

        }
        else if (gameNum == "9") {
            cout << "Exiting the game. Bye!\n";
            break;
        }
        else {
            cout << "Please enter a valid choice (from 0 to 9).\n";
        }
    }

    return 0;
}
