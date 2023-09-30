#include <iostream>
#include<fstream>
#include<customer1tdlib>
#include<customer1tring>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<string>
#include<map>
#include<limits>
#include<sstream>
using namespace std;

struct customer{
	char fullname[30];
	char gender[10];
	char address[20];
	char district[15];
	char phonenumber[10];
	char accountnumber[15];
	int openingbalance;
	char openingbalancedate[20];
};

void writer(customer customer1[], int s){
	for(int i = 0;i<s;i++){
	cout<<"-------------PUT IN YOUR DETAILS----------------------"<<endl;
	cout<<" Enter your full name: ";
	cin>>customer1.fullname,49);
	cout<<" Enter your sex: ";
	cin>>customer1.gender;
	cin.ignore();
	cout<<" Enter your address: ";
	cin>>customer1.address,49);
	cout<<" Enter your phone number: ";
	cin>>customer1.phonenumber,14);
	cout<<" Enter account number: ";
	cin>>customer1.accountnumber;
	cout<<" opening balance: ";
	cin>>customer1.openingbalance;
	cin.ignore();
	cout<<" Enter opening balance date: ";
	cin>>customer1.openingbalancedate,14);
	
bool swapped = false;
	for(int i = 0;i < s;i++){
	for(int n = 0;n < (s - i)-1;n++){
		if(customer1[n].accountnumber > customer1[n + 1].accountnumber){
			swap(customer1[n].accountnumber, customer1[n + 1].accountnumber);
			swapped = true;
		}
	}
	if(swapped == false)
	break;
	}








   
	
	  ofstream write;
	write.open("customers.dat",  ios::app);
	
	
	
	
	write<<customer1.fullname<<" ";
	write<<customer1.gender<<" ";
	write<<customer1.address<<" ";
	write<<customer1.district<<" ";
	write<<customer1.phonenumber<<" ";
	write<<customer1.accountnumber<<" ";
	write<<customer1.openingbalance<<" ";
	write<<customer1.openingbalancedate<<endl;
	
	
	write.close();
}
}



void menu(){
	cout<<" select any single option "<<endl;
	cout<<" 1. Enter new record "<<endl;
	cout<<" 2. Search for a record "<<endl;
    cout<<" 3. Delete a record "<<endl;
	cout<<" 4. Replace a record "<<endl;
	cout<<" 5. Display records "<<endl;
	cout<<" 6. Read records "<<endl;
	cout<<" 7. Customer analysis report  "<<endl;	
}

void deleterec(){
	string line;
	int offset;
	string search;
	bool finder;
	
	
	ifstream reader;
	reader.open("customers.dat");
	ofstream wfile;
	wfile.open("toBeRemoved.dat");
	
	cout << "Name to search: ";
	cin >> search;
	if(reader.is_open()){
		while(!reader.eof()){
			getline(reader, line);
			if(((offset = line.find(search, 0)) != string::npos)){
				finder = true;
		while(getline(reader, line) && !line.empty()){
			wfile << line << endl;
		}
		break;
}
		else {
			wfile << line << endl;
		}
}
		reader.close();
		wfile.close();
		if(finder){
			remove("customers.dat");
			rename("toBeRemoved.dat", "customers.dat");
			cout << endl << " Deleted!" << endl;
		}
}
}


void overwrite(){
	deleterec();
	
	cout << "---------------------NEW RECORD-----------------------" << endl;
	
	customer customer1[1];
	
	for(int i = 0;i < 1;i++){
	cout << "FUll name ::";
	cin.ignore();
	cin>>customer1.fullname,49);
	cout << "Gender ::";
	cin >> customer1.gender;
	cin.ignore();
	
//	cout << endl;
	cout << "address ::";
	cin>>customer1.address, 49);
	
	cout << "Phone number ::";
	cin>>customer1.phonenumber, 14);
	
	cout << "District ::";
	cin>>customer1.district, 19);
	
	cout << "Account number ::";
	cin >> customer1.accountnumber;
	
	cout << "Opening balance :: ";
	cin >> customer1.openingbalance;
	cin.ignore();
	
	cout << "opening date balance ::";
	cin>>customer1.openingbalancedate, 14);
	
	ofstream write;
	write.open("customers.dat",ios::app);
	
	write << "|Full name: " << customer1.fullname<< "  |";
	write <<  customer1.gender<< "|  ";
	write << " Phone number : " << customer1.phonenumber<< "|  ";
	write << " District: " << customer1.district<< "|  ";
	write << " Address: " << customer1.address<< "|  ";
	write << " opening date balance " << customer1.openingbalancedate<< "|  ";
	write << " account balance " << customer1.accountnumber << "|  ";
	write << " Opening balance " << customer1.openingbalance << endl;
	
		write.close();
		
}
	


}
void generateCustomerAnalysisReport() {
    ifstream inFile("customers.dat");
    ofstream write("CustomerAnalysis.dat");

map<std::string, int> districtfrequency;
    if (!inFile || !write) {
        cerr << "Error opening files for analysis report." << endl;
        return;
    }

    customer highestOpeningBalanceCustomer;
    customer lowestOpeningBalanceCustomer;
    double totalOpeningBalance = 0.0;
    int customerCount = 0;
    map<string, int> districtFrequency; // To store district frequency

    // Initialize highest and lowest opening balances with extreme values
    highestOpeningBalanceCustomer.openingbalance = -1.0;
    lowestOpeningBalanceCustomer.openingbalance = numeric_limits<double>::max();

    string line;
    while (getline(inFile, line)) {
        istringstream iss(line);
        customer customer;
        iss >> customer.fullname >> customer.gender
            >> customer.address >> customer.district
            >> customer.phonenumber >> customer.accountnumber
            >> customer.openingbalance >> customer.openingbalancedate;

        // Update highest and lowest opening balances
        if (customer.openingbalance > highestOpeningBalanceCustomer.openingbalance) {
            highestOpeningBalanceCustomer = customer;
        }
        if (customer.openingbalance < lowestOpeningBalanceCustomer.openingbalance) {
            lowestOpeningBalanceCustomer = customer;
        }

        // Update total opening balance and count for mean calculation
        totalOpeningBalance += customer.openingbalance;
        customerCount++;

        // Update district frequency
        districtFrequency[customer.district]++;
    }

    // Calculate the mean opening balance
    double meanopeningbalance = totalOpeningBalance / static_cast<double>(customerCount);

    // Write analysis report to the output file
    write << "Customer Analysis Report" << endl;
    write << "------------------------" << endl;
    write << "Customer with the highest opening balance:" << endl;
    write << "Full Name: " << highestOpeningBalanceCustomer.fullname << endl;
    write << "Opening Balance: " << highestOpeningBalanceCustomer.openingbalance << endl;
    write << "------------------------" << endl;
    write << "Customer with the lowest opening balance:" << endl;
    write << "Full Name: " << lowestOpeningBalanceCustomer.fullname << endl;
    write << "Opening Balance: " << lowestOpeningBalanceCustomer.openingbalance << endl;
    write << "------------------------" << endl;
    write << "Mean Opening Balance: " << meanopeningbalance << endl;
    write << "------------------------" << endl;
    write << "District Frequency Table:" << endl;
    std::map<string, int>::iterator it;
    for (it = districtfrequency.begin(); it !=districtfrequency.end(); ++it) {
    	const string& district = it->first;
    	int frequency = it->second;
        std::cout<<"District: " <<district <<"| frequency: "<< std::endl;
    }

    cout << "Customer analysis report generated and saved in CustomerAnalysis.dat." << endl;

    inFile.close();
    write.close();
}


int main(){
	int choice = 0;
	menu();
	cin>>choice;
	int num = 0;
	customer customer1[num];
	
	
	while((choice <= 0) ||  (choice >= 8)){
		cout<<" Enter a number between 1 and 7! :: ";
		cin>>choice;
		
	}
	
	switch(choice){
		case 1:{
			cout<<" Enter new record "<<endl;
			cout<<" Enter number of customers to add:: ";
			cin>>num;
			cin.ignore();
			writer(customer1,num);
			break;
		}
		
		case 2:{
			cout<<" search for a record ";
			string line;
			int offset;
			string search;
			
			ifstream reader;
			reader.open("customers.dat");
			
			cout<<" Name to search ";
			cin>>search;
			if(reader.is_open()){
				while(!reader.eof()){
					getline(reader,line);
					if(((offset = line.find(search,0)) != string::npos)){
						cout<<" Found it! :: "<<line<<endl;
						reader.close();
						
					}
				}
			}
			break;
		}
		
		case 3:{
			cout<<" Delete a record ";
				deleterec();
			break;
		}
		
		case 4:{
			cout<<" Replace a record ";
			overwrite();
			break;
		}
		
		case 5:{
			cout<<" Display a record "<<endl;
			char r;
			ifstream reader;
			reader.open("customers.dat");
			while(!reader.eof()){
				r = reader.get();
				cout<<r;
			}
			break;
		}
		
		case 6:{
			cout<<" reading record "<<endl;
			ifstream read;
				for(int i = 0;i < num;i++){
				read.open("custs.dat", ios::binary);
				read.get((char*)(customer1+i), sizeof(customer));
				
				cout << customer1.fullname << endl;
				
				
			}
				
				break;
			}
			
	    case 7:{
	    	cout<<"Generate customer analysis report";
	    	generateCustomerAnalysisReport();
			break;
		}
		
		case 8:{
			cout<<" exit  ";
			break;
		}
	
	}

	 
	
	
	
	return 0;
}

