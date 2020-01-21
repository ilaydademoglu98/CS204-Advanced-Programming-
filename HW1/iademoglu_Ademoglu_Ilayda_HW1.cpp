#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

//I am Ilayda Ademoglu(23856), this is the first homework of cs204 

vector<vector<char>>addPuzzleMatrix (ifstream & input,bool &lowercase,bool &charmi){ //THIS FUNCTION ADDS MATRIX INTO TWO DIMENSIONAL VECTOR
	vector<vector<char>> puzzlematris;
	string puzzleline;
	string puzzlechar;
	char realchars;
	vector<char> linevector;
	while(getline(input,puzzleline)){ 
		stringstream iss(puzzleline);
		stringstream issx(puzzleline);
		while(iss>>puzzlechar){
			if(puzzlechar.length() > 1){ //IF THE ENTRY IS A STRING IT STOPS BECAUSE IT NEEDS A CHAR
				cout << "Invalid matrix - cell entry is not a char" << endl;
				charmi = false;
				break;
			}
		}
		while(issx>>realchars){
			if(realchars < 'a' || realchars >'z'){
				lowercase = false;
				cout << "Invalid matrix - char not lowercase letter" << endl; //IF ITS NOT IN THE SCOPE OF THE ALPHABET IT STOPS
				break;
			}
			linevector.push_back(realchars);
		}
		puzzlematris.push_back(linevector);
		vector <char> empty;
		linevector = empty;
	}
	return puzzlematris;

}

void showmatrix(const vector<vector<char>>&puzzlemat){ // THIS FUNCTION DISPLAYS THE MATRIX 
	for(int i=0;i< puzzlemat.size();i++){
		for(int j=0; j < puzzlemat[0].size();j++){
			cout << puzzlemat[i][j] << " ";
		}
		cout << endl;
	}
}

vector<string>dictionary (ifstream & input){ //THIS FUNCTION ADDS DICTIONARY INTO A ATRING VECTOR
	vector <string> dictionaryvec;
	string word;
	while(getline(input,word)){
		dictionaryvec.push_back(word);
	}

	return dictionaryvec;

}

void controlfirst(const vector<vector<char>>&puzzlemat, int points,bool & checking){ //THIS FUNCTION CONTROLS WHETHER THE PUZZLE COMPLETED OR NOT
	bool allelements = true;
	for(int i = 0 ; i < puzzlemat.size(); i++){
		for(int j = 0; j < puzzlemat[0].size(); j++){
			if(puzzlemat[i][j] != '_'){
				allelements = false;
			}
		}
	}
	if(allelements == true){
		cout << endl;
		cout << "Congratulations, you have solved the puzzle perfectly!" << endl;		cout <<	"Your final score is " << points << endl;
		checking = false;
	}

}

void finishing(const vector<vector<char>>&puzzlemat, int points,bool & checking){ //THIS FUNCTION IS FOR USER TO ENTER -1 TO FINISH THE GAME
	bool allelements = true;
	for(int i = 0 ; i < puzzlemat.size(); i++){
		for(int j = 0; j < puzzlemat[0].size(); j++){
			if(puzzlemat[i][j] != '_'){
				allelements = false;
			}
		}
	}
	if(allelements == false){
		cout << "You didn't completely solve the puzzle." << endl;
		cout <<	"Your final score is " << points << endl;
		checking = false;
	}
}


void previoustwice(string &createdword,int &x, int & y,bool &previosly, bool & twice, vector<vector<char>> &puzzlemat, vector<vector<char>> &puzzlematcopy, vector<vector<char>> &puzzlematcopy2){
	//THIS FUNCTION CONTROL WHETHER THE PATH VISITED TWICE OR PREVIOSLY
	if(puzzlemat[x][y] == '_'){
		previosly = false;
		cout << "Invalid path - cell visited previously" << endl;
		return;
	}
	else{
		if(puzzlematcopy2[x][y] == '*'){
			twice = false;
			cout << "Invalid path - cell visited twice" << endl;
			return;
		}
		else{
			createdword += puzzlemat[x][y];
			puzzlematcopy2[x][y] = '*';
			puzzlematcopy[x][y] = '_';
		}
	}
}

int main(){
	ifstream input;
	ifstream inputfordic;
	string puzzleFileName;
	string dictionaryFileName;

	do{ //PUZZLE FILE NAMEI DOGRU GIRENE KADAR SOR
		cout << "Please enter the name of the puzzle file: ";
		cin >> puzzleFileName;
		input.open(puzzleFileName);
		if(!input.is_open()){
			cout << "File could not be opened." << endl;
		}
	}while(input.fail());

	bool charmi = true;
	bool lowercase = true;
	static vector<vector<char>> puzzlemat = addPuzzleMatrix(input,lowercase,charmi);

	if(charmi == true && lowercase == true){
		
		for(int i = 1; i < puzzlemat.size();i++){  //MATRIXIN BOYUTLARI FARKLIYSA EGER
			if(puzzlemat[i].size() != puzzlemat[i-1].size()){
				cout << "Invalid matrix - inconsistent dimensions" << endl;
				return 0;
			}
		}

		do{
			cout << "Please enter the name of the dictionary file: ";
			cin >> dictionaryFileName;
			inputfordic.open(dictionaryFileName);
			if(!inputfordic.is_open()){
				cout << "File could not be opened." << endl;
			}
		}while(inputfordic.fail());

		vector <string> dictionaryvec = dictionary(inputfordic); //DICTIONARY FILEI VECTORE KOYDUM
		static int current = 0; //kazanicagi puanlar
		while(true){
			bool checking = true;
			controlfirst(puzzlemat,current,checking); //BITMIS MI BITMEMIS MI DIYE BAK BITMISSE PROGRAMI BITIR
			if(checking	== false){
				break;
			}
			cout << endl;
			showmatrix(puzzlemat); 
			cout << endl;


			vector<vector<char>> puzzlematcopy = puzzlemat; //KOPYA YARATIYORUM
			vector<vector<char>> puzzlematcopy2 = puzzlemat; //TWICE OLUP OLMADIGINI KONTROL ETMEK ICIN
			int x,y;
			string s; //skipping the invalid value;
			string createdword = "";
			for(;;){
				cout << "Enter the starting location for word (x, y): ";
				if(cin >> x >> y){
					break;
				}
				else{
					cout << "Invalid x and y coordination. " << endl;
					cin.clear();
					cin>> s;
					cin.ignore();
				}
			}
			if (x == -1 || y == -1){ //EGER -1 GIRERLERSE BITIR
				finishing(puzzlemat,current,checking);
				break;

			}
			bool outofrange	= true;
			if(x >= puzzlemat.size() || x < 0 || y < 0 || y>= puzzlemat[0].size()){
				outofrange = false;
				cout << "Invalid coordinate - out of range" << endl;
			}
			if(outofrange == true){
				string path;
				cout << "Enter the path:";
				cin >> path;
				bool nonrdlu = true;
				for(int i = 0; i < path.length(); i++){
					if(path[i] != 'r' && path[i] != 'd' && path[i] != 'l' && path[i] != 'u'){
						nonrdlu	= false;
						cout << "Invalid path - non-RLUD input" << endl;
						break;
					}
				}
				if(nonrdlu == true){ // R D L U HARFLERI DISINDA BASKA BI SEY GIRERSE DEVAM ETMIYOR
					bool pathlength	= true;
					if(path.length() < 2){
						cout << "Invalid path - path too short" << endl;
						pathlength	= false;
					}
					if(pathlength == true){ //UZUNLUGUN 2 KARAKTERDEN DAHA BUYUK VE ESIT OLMASI ICIN
						bool stayinlimit = true;
						bool previosly = true;
						bool twice = true;
						createdword	+= puzzlemat[x][y];
						bool contin	= true;
						if(puzzlemat[x][y] == '_'){ //BURDAKI IF ELSE I COK SONRADAN EKLEDIM KONTROL ET
							contin = false;
							previosly = false;
							cout << "Invalid path - cell visited previously" << endl;
						}
						else
							puzzlematcopy[x][y] = '_';

						if(contin	== true){
						for(int i = 0; i < path.length(); i++){
							if(path[i] == 'r'){
								y++;
								if(y >= puzzlemat[0].size()){
									stayinlimit	= false;
									cout << " Invalid path - out of range" << endl;
									break;
								}
								else{
									previoustwice(createdword,x,y,previosly,twice,puzzlemat,puzzlematcopy,puzzlematcopy2);
									if(previosly == false || twice	== false){
										break;
									}

								}
							}
							else if(path[i] == 'd'){
								x++;
								if(x >= puzzlemat[0].size()){
									stayinlimit	= false;
									cout << "Invalid path - out of range" << endl;
									break;
								}
								else{
									previoustwice(createdword,x,y,previosly,twice,puzzlemat,puzzlematcopy,puzzlematcopy2);
									if(previosly == false || twice	== false){
										break;
									}
								}
							}
							else if(path[i] == 'u'){
								x--;
								if(x < 0){
									stayinlimit	= false;
									cout << "Invalid path - out of range" << endl;
									break;
								}
								else{
									previoustwice(createdword,x,y,previosly,twice,puzzlemat,puzzlematcopy,puzzlematcopy2);
									if(previosly == false || twice	== false){
										break;
									}
								}
							}
							else if(path[i] == 'l'){
								y--;
								if(y < 0){
									stayinlimit	= false;
									cout << "Invalid path - out of range" << endl;
									break;
								}
								else{
									previoustwice(createdword,x,y,previosly,twice,puzzlemat,puzzlematcopy,puzzlematcopy2);
									if(previosly == false || twice	== false){
										break;
									}
								}
							}

						}
						}

						if(stayinlimit == true && twice == true && previosly == true){
							bool wordexist = false;
							for(int i = 0 ; i < dictionaryvec.size(); i++){
								if(createdword == dictionaryvec[i]){
									wordexist = true;
									continue;
								}
							}
							if(wordexist == true){
								int points = createdword.length() * createdword.length();
								current += points;
								puzzlemat = puzzlematcopy;

								cout << "Word found: " <<  createdword << endl;
								cout << "Word length: " << createdword.length() << endl;
								cout << "Points gained: " << points << endl;
								cout << "Current score: " <<  current << endl;
								controlfirst(puzzlemat,current,checking); //BITMIS MI BITMEMIS MI DIYE BAK BITMISSE PROGRAMI BITIR
								if(checking	== false){
									break;
								}

							}
							else if(wordexist == false){
								cout << "Invalid word - non-existent word " << createdword << endl;
							}
						}

					}

				}
			}

		}

	}

} 
