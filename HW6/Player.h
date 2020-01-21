
//I am ilayda ademoglu and this is my player header file 
class Player{
private:
	Board & myBoard;	int playerID;
public:
	Player(Board & myBoard,int playerID);
	bool guess(int row, int col);
	bool wins();


};