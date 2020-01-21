#include <iostream>
#include "Board.h"   //change this with your header file name
#include "Player.h"  //change this with your header file name
#include <iomanip>
using namespace std;

////I am ilayda ademoglu and this is my board cpp file 


Board :: Board(){
	for(int i = 0 ; i < 6 ; i++){
		for(int j = 0 ; j < 6 ; j++){
			theBoard[i][j] = 0;
		}
	}
}

void Board ::displayBoard(){
	cout << setw(8) <<  "P1"  <<  setw(8) << "|" << setw(8) <<  "P2" << endl;
	for(int i = 0 ; i < 6 ; i++){
		for(int j = 0 ; j < 3 ; j++){
			cout << setw(4) << theBoard[i][j] << setw(4);
		}
		cout << "|";
		for(int j = 3 ; j < 6 ; j++){
			cout << setw(4) << theBoard[i][j];
		}
		cout << endl;
	}
}

bool Board :: putShip(int playerID, int shipID, int row1, int col1, int row2, int col2){
	bool hata = true;
	if(shipID == 1){ //for the shape
		if(col1 != col2 && row1 != row2){
			return false;
		}

		if(row1 == row2 && abs(col2 - col1) != 1){
			hata = false;
			return false;
		}
		if(col1 == col2 && abs(row2 - row1) != 1){
			hata = false;
			return false;
		}
	}
	else if(shipID == 2){ //for the shape
		if(col1 != col2 && row1 != row2){
			hata = false;
			return false;
		}
		if(row1 == row2 && abs(col2 - col1) != 2){
			hata = false;
			return false;
		}
		if(col1 == col2 && abs(row2 - row1) != 2){
			hata = false;
			return false;
		}
	}
	if(shipID != 1 && shipID!= 2){ //ship id lerin dogrulugunu kontrol etmek icin 
		hata = false;
		return false;
	}

	if(playerID == 1){
		if(((col1 > 2 && col1 < 0) || (row1 < 0 && row1 > 5) || (col2 > 2 && col2 < 0) || (row2 < 0 && row2 > 5))){ //invalid coordinates
			hata = false;
			return false;
		}
	}
	if(playerID == 2){
		if(((col1 > 5 && col1 < 3) || (row1 < 0 && row1) > 5 || (col2 < 3 && col2 > 5) || (row2 < 0 && row2 > 5))){ //invalid coordinates
			hata = false;
			return false;
		}
	}
	if(shipID == 1){
		if(theBoard[row1][col1] != 0 || theBoard[row2][col2] != 0){ // if do not coincide with any other ship 
			hata = false;
			return false;
		}
	}

	 if(shipID == 2){
		if(theBoard[row1][col1] != 0 || theBoard[row2][col2] != 0){ // if do not coincide with any other ship 
			hata = false;
			return false;
		}
		if(col1 == col2 && theBoard[row1+1][col2] != 0){
			hata = false;
			return false;
		}
		else if(row1 == row2 && theBoard[row1][col1+1] != 0){
			hata = false;
			return false;
		}
	} 
	//eger hic bir engele takilmadiysa 
	if(hata  == true){
		if(shipID == 1){
			theBoard[row1][col1] = 1;
			theBoard[row2][col2] = 1;

		}
		else if(shipID == 2){
			theBoard[row1][col1] = 1;
			theBoard[row2][col2] = 1;
			if(col1 == col2){
				theBoard[row1+1][col2] = 1;
			}
			else if(row1 == row2){
				theBoard[row1][col1+1] = 1;
			}
		}
		return true;
	}
}

bool Board ::makeAHit(int row, int col){ // eger 1 ise -1 ile degistir
	if(theBoard[row][col] == 1){
		theBoard[row][col] = -1;
		return true;
	}
	else{
		return false;
	}

}


bool Board ::checkIfPlayerWon(int playerID){ //it checks the number of -1s
	int num = 0;
	if(playerID == 1){
		for(int i = 0 ; i < 6 ; i++){
			for( int j = 3 ; j < 6; j++){
				if(theBoard[i][j] == -1){
					num++;
				}
			}
		}

	}
	else if(playerID == 2){
		for(int i = 0 ; i < 6 ; i++){
			for( int j = 0 ; j < 3; j++){
				if(theBoard[i][j] == -1){
					num++;
				}
			}
		}
	}
	if(num == 5){
		return true;
	}
	else
		return false;

}