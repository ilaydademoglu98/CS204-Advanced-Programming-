#include <iostream>
#include "Board.h"   //change this with your header file name
#include "Player.h"  //change this with your header file name

using namespace std;

void shipPlacement(Board &theBoard, int playerID, int shipID)
{
    int row1, col1, row2, col2;
    cout << "Player " << playerID << " please give the starting and ending positions of the ship with ID : " << shipID << " in the following order; row1, col1, row2, col2." << endl;
    cin >> row1 >> col1 >> row2 >> col2;
	while (!theBoard.putShip(playerID, shipID, row1, col1, row2, col2))
    {
        cout << "Invalid coordinates OR bad ship shape OR place is already occupied by another ship." << endl;
        cout << "Please try again." << endl;
        cin >> row1 >> col1 >> row2 >> col2;
    }
    cout << "Ship placement successful." << endl;
}

int main()
{
    cout << "Game is starting..." << endl;
    Board myBoard = Board();
    cout << "Board created." << endl;
    myBoard.displayBoard();

    Player player1 = Player(myBoard, 1);
    cout << "Player 1 registered to the game." << endl;
    Player player2 = Player(myBoard, 2);
    cout << "Player 2 registered to the game." << endl;

	shipPlacement(myBoard, 1, 1); // player 1 ship 1
    myBoard.displayBoard();

    shipPlacement(myBoard, 1, 2); // player 1 ship 2
    myBoard.displayBoard();

    shipPlacement(myBoard, 2, 1); // player 2 ship 1
    myBoard.displayBoard();

    shipPlacement(myBoard, 2, 2); // player 2 ship 2
    myBoard.displayBoard();

    int row, col;
    bool gameEnded = false;
    for (int i = 0; !gameEnded; i++)
    { //start bombing
        if (i % 2 == 0)
        {
            cout << "Player1's turn." << endl;
            cout << "Please enter the cordinate to be bombed." << endl;
            cin >> row >> col;
            //input check
            int colStart = 3;
            int colEnd = colStart + 2;
            while (!(row >= 0 && row <= 5 && col >= colStart && col <= colEnd))
            {
                cout << "Invalid input. Row must be between 0-5 and column must be between 3-5" << endl;
                cout << "Please enter the cordinate to be bombed." << endl;
                cin >> row >> col;
            }
            if (player1.guess(row, col))
            {
                cout << "Player1 made a hit!" << endl;
                if (player1.wins())
                {
                    gameEnded = true;
                    cout << "Player1 won the game!" << endl;
                }
            }
            else
            {
                cout << "Player 1 missed." << endl;
            }
        }
        else
        {
            cout << "Player2's turn." << endl;
            cout << "Please enter the coordinate to be bombed." << endl;
            cin >> row >> col;
            //input check
            int colStart = 0;
            int colEnd = colStart + 2;
            while (!(row >= 0 && row <= 5 && col >= colStart && col <= colEnd))
            {
                cout << "Invalid input. Row must be between 0-5 and column must be between 0-2" << endl;
                cout << "Please enter the coordinate to be bombed." << endl;
                cin >> row >> col;
            }
            if (player2.guess(row, col))
            {
                cout << "Player2 made a hit!" << endl;
                if (player2.wins())
                {
                    gameEnded = true;
                    cout << "Player2 won the game!" << endl;
                }
            }
            else
            {
                cout << "Player 2 missed." << endl;
            }
        }
        cout << "After turn: " << endl;
        myBoard.displayBoard();
    }
	cin.ignore();
	cin.get();
	return 0;

}