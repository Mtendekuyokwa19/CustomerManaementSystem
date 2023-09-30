#include <iostream>
#include "structure.h"
#include <fstream>
using namespace std;

void menu(){

cout<<"--------------------------------------------------------- \n";
	cout<<"PLEASE SELECT THE OPERATION YOU WANT TO RUN"<<endl;
    
	cout<<"1. Enter new record \n2.Show  a newBuyer's record \n3.Delete a newBuyer's record \n4.Change a newBuyer's record \n5.Display the contents of the file"<<endl;
}


void search(){

cout<<"---------------------SEARCH ENTRY-------------\n";

			string name;
			int position;
			string search;
			
			ifstream retrieve;
			retrieve.open("customers.dat");
			
			cout<<"Enter name:>";
			cin>>search;

			if(retrieve.is_open()){

				while(!retrieve.eof()){
					getline(retrieve,name);
					
//conditional expression that evaluates to true if the string search is found in the string name at or after index 0, and false otherwise.
					if(((position = name.find(search,0)) != string::npos)){


						cout<<name<<endl;
					
						retrieve.close();
						
					}
				}
			}
		

}


bool erase(){
			string name;
			int position;
			string search;
			bool status;
			bool value;
	
	ifstream retrive;
	retrive.open("customers.dat");
	ofstream writing;
	writing.open("toBeRemoved.dat");
	
	cout << "Remove Name: ";
	cin >> search;

//trying to retrieve and deleting the sentence
	if(writing.is_open()){

		while(!retrive.eof()){

			getline(retrive, name);

			if(((position = name.find(search, 0)) != string::npos)){

				status = 1;

		while(!name.empty()&&getline(retrive, name)){
			writing << name<< endl;
		}
	
}

		else {

			writing <<name<< endl;
		}
}
//if nothing was found it should tell the user not found
		if(name.empty()){

		 cout<<"not-found";
		value=0;
		}
		else{

			value=1;
			if(status){

			remove("customers.dat");
			
			rename("toBeRemoved.dat", "customers.dat");

			
		}
			}}

		writing.close();
		retrive.close();


	return value;

}

