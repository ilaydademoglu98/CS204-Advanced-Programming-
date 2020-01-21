#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "DynIntStack.h"

using namespace std;

int main()
{
	string theFilename;
	ifstream input;
	do{ //GETTING INPUT
		cout << "Please enter a file name." << endl;
		cin >> theFilename;
		input.open(theFilename);
		if(input.fail()){
			cout << "Could not open the file" << endl;
		}
		else{
			cout << "Successfully opened file " << theFilename << endl;

		}

	}while(input.fail());

	DynIntStack stackindentation;
	string controlLine;
	bool keywordobserved = false;
	bool correct = true;
	int indentationlevel = 0; //buna gerek kalmayabiliur
	stackindentation.push(0); //en basta sifiri pushladim

	cout << "Initial indentation level is pushed to the stack as " << indentationlevel << "." << endl;
	cout << endl;

	int linenum = 1;
	while(getline(input,controlLine)){
		cout << endl;
		int currentindentationlevel;
		if(stackindentation.isEmpty()){
			currentindentationlevel = 0;
		}
		else{
			stackindentation.pop(currentindentationlevel); //stack icindeki last valueyi cikararak current indentation leveli aldim 
			stackindentation.push(currentindentationlevel);
		}


		cout << "Line number: "  << linenum << endl;
		cout << "Line: " << controlLine << endl;
		int blanknum = 0;
		for(int i= 0; i < controlLine.length(); i++){
			if(controlLine[i] == ' '){
				blanknum++;
			}
			if(controlLine[i] != ' '){
				break;
			}
		}
		cout << blanknum << " number of spaces observed before the start of the line." << endl;
		if(keywordobserved == true){
			cout << "This line proceeds a keyword containing line." << endl;
		}

		cout << "Current Level = " << currentindentationlevel;
		cout << " This Line = " << blanknum << endl;

		if(blanknum > currentindentationlevel && keywordobserved == true){
			//This is correct because bir oncekinde yeni bir keyword gozlemlendi yeni indentation leveli pushla
			stackindentation.push(blanknum);
			cout << "Line correct. Depth " << blanknum << " added to the stack." << endl;
			cout << endl;

		}
		else if (keywordobserved == true && blanknum <= currentindentationlevel){ //bu hata gozlemlendiyse kucuk olmamali
			cout << "Incorrect file structure. " << endl;
			cout << "Current line cannot be greater than the Current indentation level." << endl;
			cout << "Stopping file analysis... ";
			correct = false;
			break; //Burda stacki de bosaltman gerekiyor sonradan onu yap unutma 
		}
		else if(keywordobserved == false && blanknum < currentindentationlevel){
			bool error = false;
			cout << "Current line is smaller than Current indentation level; checking if line belongs to outer indentation." << endl;
			int x;
			stackindentation.pop(x);
			while(currentindentationlevel > blanknum){
				int num;
				stackindentation.pop(num);
				currentindentationlevel = num;
				cout << "Current Level = " << currentindentationlevel;
				cout << " This Line = " << blanknum << endl;
				if(currentindentationlevel == blanknum){
					cout << "Line belongs to outer block." << endl;
					stackindentation.push(num);
				}
			}

			if(currentindentationlevel != blanknum){
				correct = false;
				cout << "Incorrect file structure.";
				cout << " An indentation level same as the Current line is not found in outer blocks." << endl;
				cout << "Stopping file analysis... ";
				break; //Burda stacki de bosaltman gerekiyor sonradan onu yap unutma 
			}
		}

		else if(keywordobserved == false && blanknum > currentindentationlevel){
			correct = false;
			cout << "Incorrect file structure. " << endl;
			cout << "Current line cannot be greater than the Current indentation level." << endl;
			cout << "Stopping file analysis... ";
			break;
		}


		else if(keywordobserved == false && blanknum == currentindentationlevel){
			cout << "Line belongs to current block." << endl;
		}


		//bu elimizdeki line da keyword olup olmadigini kontrol ediyor bunu daha sonradan fonksyiona koyabilirsin 
		stringstream iss(controlLine);
		string word;
		while(iss >> word){
			if(word == "if" || word == "else" || word == "elif" || word == "for" || word == "while"){
				keywordobserved = true;
				cout << "Keyword " << word << " found on this line. "<< endl;
				cout << endl;
				break;
			}
			else{
				keywordobserved = false;
			}

		}
		linenum++;
	}
	if(correct == true){
		cout << "Finished file analysis. File structure is correct!" << endl;
	}
	while(stackindentation.isEmpty() == false){
		int randomnum;
		stackindentation.pop(randomnum);
	}
	cout << endl;
	cout << "Stack emptied and program ending." << endl;
}
