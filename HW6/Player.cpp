#include <iostream>
#include "Board.h"   //change this with your header file name
#include "Player.h"  //change this with your header file name
using namespace std;

//I am ilayda ademoglu and this is my player cpp file 


Player:: Player(Board & Board,int playerid)
	: playerID(playerid), myBoard(Board)
{}

 bool Player:: guess(int row, int col){
	 if(myBoard.makeAHit(row,col) == true){
		 return true;
	 }
	 else
		 return false;
}

 bool Player:: wins(){
	 if(myBoard.checkIfPlayerWon(playerID) == true)
		 return true;
	 else 
		 return false;
 }