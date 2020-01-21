#include <iostream>
#include <time.h> 
#include <sstream>
#include <ctime>  
#include <fstream>
#include <thread>
#include <mutex> 
#include <chrono>        
#include <random>
#include <iomanip> 

//Hello I am Ilayda Ademoglu(23856) This is my 7th homework of cs204 course

using namespace std;

int globalSum = 0; //I keep global sum and global index for usage of threads because they work concurrently and I cant write them in a function
#define numThread 5
int globalIndex = 0;
mutex Mutex1;


int random_range(const int & min, const int & max); //Funciton decleration of random number generator function

void threadsfunctiontoadd(int maxrange,int minrange,int i,int *arraynum,int sayi){ //This function is the function which 5 threads adds numbers 


	while(globalIndex < sayi){ //Until number reaches the size of the array


		this_thread::sleep_for (chrono::seconds(random_range(minrange,maxrange)));  //This creates waiting time 
		time_t tt = chrono::system_clock::to_time_t (chrono::system_clock::now()); 
		struct tm *ptm = new struct tm;  
		localtime_s(ptm, &tt); 



		Mutex1.lock();
		if(globalIndex >= sayi){
			Mutex1.unlock();
			break;

		}
		
		cout << "Thread " << i+1 << " added number index" << globalIndex << " to the total sum at " <<  put_time(ptm,"%X") << endl;
		globalSum += arraynum[globalIndex];
		cout << "Current sum:" << globalSum << endl;
		globalIndex++;
	

		Mutex1.unlock();


	}

}


int main()
{
	string theFileName;
	int minrange,maxrange;
	ifstream inputcin;
	cout<<"Please enter a file name"<<endl; //Entering file name
	cin >> theFileName;
	cout << "Please enter the wait range of threads."<<endl; //Entering waiting time
	cin >> minrange >> maxrange;
	inputcin.open(theFileName);


	int sizeofarray;
	string line;
	if(getline(inputcin,line)) //read line by line and converts them to integers
	{
		sizeofarray = stoi(line);
	}
	int *arrayofints = new int[sizeofarray];



	int sayac=0;
	string line222;
	int x;
	time_t tt11 = chrono::system_clock::to_time_t (chrono::system_clock::now());  //gets the current time
	struct tm *ptm11 = new struct tm;  //creating the time struct to be used in thread
	localtime_s(ptm11, &tt11); 
	cout << "Starting reading the array at " << put_time(ptm11,"%X") << endl;

	while(getline(inputcin,line222))
	{
		arrayofints[sayac]= stoi(line222);
		sayac++;
	}
	cout << "Array stored in the memory. Starting the summation at " << put_time(ptm11,"%X") << endl;
	cout << endl;
	thread aThread[numThread];

	for(int i= 0; i < numThread; i++){
		aThread[i] = thread(&threadsfunctiontoadd, maxrange, minrange, i,arrayofints,sizeofarray);
	}
	for (int i=0; i < numThread; i++)
	{
		aThread[i].join();
	}
	time_t n = chrono::system_clock::to_time_t (chrono::system_clock::now());  //gets the current time
	struct tm *p = new struct tm;  //creating the time struct to be used in thread
	localtime_s(p, &n); 
	cout << endl;
	cout << "Adding finished at " << put_time(p,"%X") << endl;
	cout << "Sum: " << globalSum << endl;

}

int random_range(const int & min, const int & max) {    //In order to create a random time we use this function 
	static mt19937 generator(time(0));    
	uniform_int_distribution<int> distribution(min, max);    
	return distribution(generator); 
}
