#include <iostream>
#include "iademoglu_Ademoglu_Ilayda_HW3.h"

using namespace std;

linkedlist::linkedlist(){ //HEAD STARTED WITH NULL
	head = NULL;
}


void linkedlist::addHouseNode(string hname){ //THIS FUNCTION ADDS THE HOUSE NODE ONE AFTER OTHER 
	if(head == NULL){
		head = new houseNode(hname,NULL,NULL);
	}
	else{
		if(hnExists(hname) == false){
			houseNode * ptr = head;  
			while (ptr->next != NULL)
			{    
				ptr = ptr->next;
			}
			houseNode * temp = new houseNode(hname,NULL,NULL);
			ptr->next = temp;
		}

	}
}



void linkedlist::addNeighborNode (string hname, string nname){ //THIS FUNCTION ADDS THE NEIGHBORING NODES OF A CERTAIN HOUSE

	if(nnExists(hname,nname) == false){
		houseNode * ptr = head;  
		while (ptr->next != NULL && ptr->houseName != hname)
		{    
			ptr = ptr->next;
		}

		if(ptr->neighborListHead == NULL){
			ptr->neighborListHead = new neighborNode(nname,NULL);
		}
		else{
			neighborNode * temp = ptr->neighborListHead;
			while(temp->next != NULL){
				temp = temp ->next;
			}
			neighborNode * ekleme = new neighborNode(nname,NULL);
			temp->next = ekleme;
		}
	}

}


bool linkedlist::hnExists(string hname){ //THIS FUNCTION CONTROLS IF HOUSE EXITST
	houseNode * ptr = head; 
	while (ptr != NULL)
	{    
		if(ptr->houseName == hname){
			return true;
		}
		ptr = ptr->next;
	}
	return false;
}


bool linkedlist::nnExists(string hname, string nname){ // THIS UNCTION CONTROLS IF NEIGHBOR EXISTS
	houseNode * ptr = head;  
	while (ptr->next != NULL && ptr->houseName != hname)
	{    
		ptr = ptr->next;
	}
	if(ptr->neighborListHead == NULL){
		return false;
	}
	neighborNode * tempo = ptr->neighborListHead;
	while(tempo != NULL){
		if(tempo->neighborName == nname){
			return true;
		}
		tempo = tempo->next;
	}
	return false;
}

void linkedlist::printAll(){ //THIS FUNCTION PRINTS THE WHOLE MAP
	cout << endl;
	cout << "######## MAP ########" << endl;
	cout << endl;
	houseNode * temphouse = head;
	while(temphouse != NULL){
		neighborNode * neighbortemp = temphouse->neighborListHead;
		cout << temphouse->houseName << ": ";
		while(neighbortemp != NULL){
			cout << neighbortemp->neighborName << ", ";
			neighbortemp = neighbortemp->next;
		}
		cout << endl;
		temphouse = temphouse->next;
	}
}

void linkedlist::conquer(string hname, string h2name){  // THIS FUNCTION IS FOR ANNEXATION 
	houseNode * ptr = head;  
	while (ptr->next != NULL && ptr->houseName != h2name) //ISTILA EDILEN EZIK LISTENIN HOUSE NAMEI
	{    
		ptr = ptr->next;
	}
	houseNode * ptrforek = head;  
	while (ptrforek->next != NULL && ptrforek->houseName != hname) //CONQUER HOUSE NAME
	{    
		ptrforek = ptrforek->next;
	}
	neighborNode * eklen = ptrforek->neighborListHead;
	neighborNode * prev;
	neighborNode * tempo = ptr->neighborListHead;

	while(eklen->next != NULL){ //SEARCH ICIN 
		prev = eklen;
		eklen = eklen->next;
	}
	while(tempo != NULL){ // YOKSA EKLENIYOR 
		if(nnExists(hname,tempo->neighborName) == false && hname != tempo->neighborName){
			eklen->next = new neighborNode(tempo->neighborName,NULL);
			eklen = eklen->next;
		}
		tempo = tempo->next;
	}
	houseNode * headcopy = head; 
	houseNode * silinecekhouse = ptr;
	neighborNode * temp;

	while(ptr->neighborListHead != NULL){
		temp =  ptr->neighborListHead->next;			
		delete  ptr->neighborListHead;
		ptr->neighborListHead = temp;
	}
	if(h2name == headcopy->houseName){  // EGER BASTAYSA HEAD DEGISIYOR VE KALAN SILINIYOR

		houseNode * tut = headcopy;
		head = head-> next;
		delete tut;
	}
	else{ //EGER BASTA DEGILSE VAR OLAN SILINIP GERI KALANLAR BAGLANIYOR
		while(headcopy->next != NULL && headcopy->next->houseName != h2name){
			headcopy = headcopy->next;
		}
		if(headcopy->next->houseName == h2name){
			houseNode * sil = headcopy-> next;
			headcopy-> next= headcopy->next->next;
			delete sil;
		}
	}

}

void linkedlist::replacethename(string hname, string h2name){ //THIS FUNCTION CHANGES NAMES AFTER ANNEXATION
	houseNode * ptr = head;
	while(ptr != NULL){
		neighborNode * ptrdevam = ptr->neighborListHead;
		if(nnExists(ptr->houseName,hname) == false && nnExists(ptr->houseName,h2name) == true && ptr->houseName != hname){ //eger istenen house yoksa ve degistirmek istedigimiz house varsa
			while(ptrdevam!= NULL){
				if(ptrdevam->neighborName == h2name){
					ptrdevam->neighborName = hname;
				}
				else{
					ptrdevam = ptrdevam->next;
				}
			}
		}
		else if(ptr->houseName == hname && nnExists(ptr->houseName,h2name) == true){ // eger istenen house ve degistirmek istedigimiz house beraber varsa sadece degistirmek isteneni sil 
			neighborNode * ptrdevam = ptr->neighborListHead;
			if(ptrdevam->neighborName == h2name){ // headdeyse ayri sil
				neighborNode * del = ptrdevam;
				ptr->neighborListHead = ptr->neighborListHead->next;
				delete del;
			}
			else{ // head degilse ayri sil
				while(ptrdevam->next!= NULL){
					if(ptrdevam->next->neighborName == h2name){
						neighborNode * del = ptrdevam->next;
						ptrdevam->next = ptrdevam->next->next;
						delete del;
						break;
					}
					else{
						ptrdevam = ptrdevam->next;
					}
				}
			}
		}
		else if(nnExists(ptr->houseName,hname) == true && nnExists(ptr->houseName,h2name) == true &&ptr->houseName != hname){ 
			if(ptrdevam->neighborName == h2name){
				neighborNode * del = ptrdevam;
				ptr->neighborListHead = ptr->neighborListHead->next;
				delete del;
			}
			else{
				while(ptrdevam->next!= NULL){ 
					if(ptrdevam->next->neighborName == h2name){
						neighborNode * deletes = ptrdevam->next;
						ptrdevam->next = ptrdevam->next->next;
						delete deletes;
						break;

					}
					else{
						ptrdevam = ptrdevam->next;
					}
				}
			}
		}
		ptr = ptr-> next;
	}


}

void linkedlist::deleteAll(){ //THIS FUCNTION DELETES ALL THE LINKED LIST ALL THE MAP
	houseNode *tempdeleted;				
	while (head != NULL) {
		neighborNode * temp;
		while(head->neighborListHead != NULL){
			temp = head->neighborListHead->next;			
			delete head->neighborListHead;
			head->neighborListHead = temp;
		}
		tempdeleted = head->next;			
		delete head;
		head = tempdeleted;
	}

}