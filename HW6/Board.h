
////I am ilayda ademoglu and this is my board header file 


class Board{
private:
	int theBoard[6][6];
public:
	Board();
	void displayBoard();
	bool putShip(int playerID, int shipID, int row1, int col1, int row2, int col2);
	bool makeAHit(int row, int col);
	bool checkIfPlayerWon(int playerID);
};