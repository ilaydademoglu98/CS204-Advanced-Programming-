#include "iademoglu_ademoglu_ilayda_hw5_header.h"
#include <iostream>
using namespace std;


Matrix::Matrix(){ //initilization default constructor
	rowNumber = 0;
	columnNumber = 0;
}

Matrix :: Matrix(int rowNum, int columnNum, int init){ //constructor with parameters
	if(rowNum <= 0 || columnNum <= 0){
		rowNumber = 0;
		columnNumber = 0;
	}
	else{
		rowNumber = rowNum;
		columnNumber = columnNum;
		elements = new int *[rowNumber]; //Allocation for rows 
		for(int i = 0 ; i < rowNumber ; i++){ //Allocation for columns
			elements[i] = new int[columnNumber];
		}


		for(int i = 0 ; i < rowNumber; i++){ // Tüm value'leri inite eşitlemen gerek 
			for(int j = 0 ; j < columnNumber; j++){
				elements[i][j] = init;
			}	
		}
	}

}

Matrix::Matrix(const Matrix & copy){ //copy constructor which makes deep copy
	rowNumber = copy.rowNumber;
	columnNumber = copy.columnNumber;

	elements = new int *[rowNumber];
	for(int i = 0 ; i < rowNumber; i++){
		elements[i] = new int[columnNumber];
	}

	for(int i = 0 ; i < rowNumber;i++){
		for(int j = 0 ; j < columnNumber; j++){
			elements[i][j] = copy.elements[i][j];
		}
	}
}

Matrix::~Matrix(){ // destructor returns memory to the heap
	for(int i = 0 ; i < rowNumber; i++){
		delete []elements[i];
	}
	delete []elements;
}


int  Matrix::getRowNumber() const {
	return rowNumber;
}

int  Matrix::getColumnNumber() const {
	return columnNumber;
}

int Matrix::getElementAt(int row, int column) const{
	return elements[row][column];
}
void Matrix::setElementAt(int row,int column, int value){
	elements[row][column] = value;
}

void Matrix::print(){ //this prints elements of the matrix
	for(int i = 0 ; i < rowNumber ; i++){
		for(int j = 0; j < columnNumber; j++){
			cout << elements[i][j] << " ";
		}
		cout << endl;
	}
}

void Matrix::deletematrix(){ //this is the same as destructor deletes matrix
	for(int i = 0 ; i < rowNumber; i++){
		delete []elements[i];
	}
	delete []elements;
}

const Matrix & Matrix::operator = (const Matrix & rhs){  //this operator checks if the rhs is equal to lhs
	if(this != &rhs){
		if(rowNumber > 0 || columnNumber > 0){
			deletematrix();
		}
		rowNumber = rhs.rowNumber;
		columnNumber = rhs.columnNumber;

		elements = new int *[rowNumber];
		for(int i = 0 ; i < rowNumber; i++){
			elements[i] = new int[columnNumber];
		}

		for(int i = 0 ; i < rowNumber;i++){
			for(int j = 0 ; j < columnNumber; j++){
				elements[i][j] = rhs.elements[i][j];
			}
		}
	}
	return *this;
}

bool Matrix::equals(const Matrix & a, const Matrix & b){ //this is a boolean function and checks equality
	if(a.rowNumber != b.rowNumber || a.columnNumber != b.columnNumber)
		return false;
	else{
		for(int i = 0 ; i < a.rowNumber; i++){
			for(int j = 0 ; j < a.columnNumber; j++){
				if(a.elements[i][j] != b.elements[i][j])
					return false;
			}
		}
		return true;
	}
}

bool Matrix::operator==(const Matrix& b){ //returns the functions value which checks equality
	return equals(*this,b);
}

