#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "iademoglu_Ademoglu_Ilayda_HW3.h"

using namespace std;

void addHouseNode(string hname);

//Hello I am Ilayda Ademoglu(23856) this is the third homework of cs204 about game of thrones maps.

int main(){
	linkedlist x;
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
			cout << "Successfully opened file  " << theFilename << endl;
			cout << endl;
			cout << "######## TOPOLOGY ######## " << endl;
			cout << endl;
		}

	}while(input.fail());

	string bothof;
	string housename;
	string neighbors;

	while(getline(input,bothof)){
		stringstream iss(bothof);
		while(iss >> housename >> neighbors){
			cout << "Processing " << housename << ", " << neighbors << endl;

			if((x.hnExists(housename) == true) && x.nnExists(housename,neighbors) == true){
				cout << "Redundant information! An entry with " << housename << " and " << neighbors << " is already processed." << endl; 
				cout << endl;
			}
			else{
				x.addHouseNode(housename);
				x.addNeighborNode(housename,neighbors);
				x.addHouseNode(neighbors);
				x.addNeighborNode(neighbors,housename);
				cout << "Topology information successfully added." << endl; 
				cout << endl;
			}
		}
	}
	int userenter;
	x.printAll();

	while(true){ //FOR THE OPTIONS
		cout << endl;
		cout << " Please select an option [1-2-3]" << endl;
		cout << " 1. Annexation! War for the iron throne continues..." << endl;
		cout << " 2. Tyrion must travel, do a path check for the famous imp." <<  endl;
		cout << " 3. Exit " << endl;
		cin >> userenter;
		if(userenter == 1){
			string housename1;
			string housename2;
			cout << "Please enter two houses first the annexer and the annexed. " << endl;
			cin >> housename1 >> housename2;
			if(housename1 == housename2){
				cout << "A House cannot conquer itself!" << endl;
				cout << "Update failed." << endl;
			}
			else if(x.hnExists(housename1) == false){

				cout << housename1 << " does not exist" << endl;
				cout << "Update failed." << endl;
			}
			else if(x.hnExists(housename2) == false){

				cout << housename2 << " does not exist" << endl;
				cout << "Update failed." << endl;
			}
			else if(x.nnExists(housename1,housename2) == false){
				cout << "A house can only conquer a neighboring house!" << housename2 << " is not a neighbor of " << housename1 << endl; 
				cout << "Update failed." << endl;
			}
			else{
				cout << housename1 << " conquered " << housename2 << "!"<< endl;
				x.conquer(housename1,housename2);
				x.replacethename(housename1,housename2);
				x.printAll();
			}
		}
		else if(userenter == 2){ //IF USER ENTERS 2 THE NECESSARY THINGS ARE DONE LIKE CHECKING EXISTINCE FOR PAIRS EVERYTIME 
			string path;
			cout << "Please enter a path" << endl;
			cin.ignore();
			getline(cin,path);
			vector <string> pathnames;
			string takenpath;
			istringstream iss(path);
			bool pathcorrect = true;
			while(iss>>path){ // THE INPUT IS STORED IN A VECTOR 
				pathnames.push_back(path);
			}
			bool devam = true;
			for(int i = 0; i < pathnames.size() ; i++){ //IF NOT EXIST DO NOT CONTINUE AT FIRST 
				if(x.hnExists(pathnames[i]) == false){
					cout << pathnames[i] << " does not exist in the map." << endl;
					cout << "Path search failed!";
					devam = false;
					break;
				}
			}
			if(devam == true){
			for(int i = 0; i < pathnames.size()-1 ; i++){
				if(pathnames[i] == pathnames[i+1]){
					cout << "You are already in " << pathnames[i] << endl;
				}
				else if(x.nnExists(pathnames[i],pathnames[i+1]) == true){
					cout << "Path found between " << pathnames[i] << " and " << pathnames[i+1] << endl;
				}
				else if(x.nnExists(pathnames[i],pathnames[i+1]) == false){
					pathcorrect = false;
					cout << pathnames[i+1] << " is not a neighbor of " << pathnames[i] << endl;
				} 
				if(pathcorrect == false){
					cout << "Path search failed!";
					break;
				}
			}
			if(pathcorrect == true){
				cout << "Path search succeeded. " << endl;
			}
			}
		}
		else if(userenter == 3){ //THIS DELETES THE MAP AND ENDS THE PROGRAM
			cout << "List deleted and program ended." << endl;
			x.deleteAll();
			break;
		}
		else{
			cout << "Invalid option please select from the menu." << endl;
		}

	}
}