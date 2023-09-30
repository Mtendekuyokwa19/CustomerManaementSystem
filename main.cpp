#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <iomanip> 

using namespace std;

// Define a structure to represent a record
struct CustomerAccount {
  int accountNumber;
  string fullName;
  char gender;
  string address;
  string district;
  int phoneNumber;
  double balance;
  string date;
};

// Function to add an account to the data file
void addRecord(fstream& dataFile, CustomerAccount& account) {
    dataFile.write(reinterpret_cast<char*>(&account), sizeof(CustomerAccount));
}

// Function to search for an account by account number
CustomerAccount searchRecord(fstream& dataFile, int accountNumber) {
    CustomerAccount account;
    dataFile.seekg(0, ios::beg);

    while (dataFile.read(reinterpret_cast<char*>(&account), sizeof(CustomerAccount))) {
        if (account.accountNumber == accountNumber) {
            return account;
        }
    }

    // Return an empty record if not found
    return { -1, "", '\0', "", "", -1, -1.0, ""  };
}

// Function to modify an account by account number
bool modifyRecord(fstream& dataFile, int accountNumber, const CustomerAccount& modifiedAccount) {
    fstream tempFile("temp.dat", ios::out | ios::binary);

    if (!tempFile) {
        cerr << "Failed to open temporary file." << endl;
        return false;
    }

    CustomerAccount account;
    bool modified = false;

    dataFile.seekg(0, ios::beg);

    while (dataFile.read(reinterpret_cast<char*>(&account), sizeof(CustomerAccount))) {
        if (account.accountNumber == accountNumber) {
            modified = true;
            tempFile.write(reinterpret_cast<const char*>(&modifiedAccount), sizeof(CustomerAccount));
        } else {
            tempFile.write(reinterpret_cast<const char*>(&account), sizeof(CustomerAccount));
        }
    }

    tempFile.close();

    if (modified) {
        dataFile.close();
        remove("records.dat");
        rename("temp.dat", "records.dat");
        dataFile.open("records.dat", ios::in | ios::out | ios::binary | ios::app);
    }

    return modified;
}

// Function to delete an account by account number
bool deleteRecord(fstream& dataFile, int accountNumber) {
    fstream tempFile("temp.dat", ios::out | ios::binary);

    if (!tempFile) {
        cerr << "Failed to open temporary file." << endl;
        return false;
    }

    CustomerAccount account;
    bool deleted = false;

    dataFile.seekg(0, ios::beg);

    while (dataFile.read(reinterpret_cast<char*>(&account), sizeof(CustomerAccount))) {
        if (account.accountNumber == accountNumber) {
            deleted = true;
            continue; // Skip writing this record to the temp file
        }
        tempFile.write(reinterpret_cast<const char*>(&account), sizeof(CustomerAccount));
    }

    tempFile.close();

    if (deleted) {
        dataFile.close();
        remove("records.dat");
        rename("temp.dat", "records.dat");
        dataFile.open("records.dat", ios::in | ios::out | ios::binary | ios::app);
    }

    return deleted;
}

// Function to get new account record from user input
void handleNewUserInput(CustomerAccount& account){
  cout << "Enter Account Number: ";
  cin >> account.accountNumber;
  cin.ignore(); // Clear newline character
  cout << "Enter Full Name: ";
  getline(cin, account.fullName);
  cout << "Enter Gender (M/F): ";
  cin >> account.gender;
  cin.ignore(); // Clear newline character
  cout << "Enter Address: ";
  getline(cin, account.address);
  cout << "Enter District: ";
  getline(cin, account.district);
  cout << "Enter Phone Number: ";
  cin >> account.phoneNumber;
  cout << "Enter Balance: ";
  cin >> account.balance;
  cin.ignore(); // Clear newline character
  cout << "Enter Date (MM/DD/YYYY): ";
  getline(cin, account.date);
}
//function to display customer records
void displayRecord(const CustomerAccount& account) {
    cout << "Account Number: " << account.accountNumber << endl;
    cout << "Full Name: " << account.fullName << endl;
    cout << "Gender: " << account.gender << endl;
    cout << "Address: " << account.address << endl;
    cout << "District: " << account.district << endl;
    cout << "Phone Number: " << account.phoneNumber << endl;
    cout << "Balance: $" << fixed << setprecision(2) << account.balance << endl;
    cout << "Date: " << account.date << endl;
}

int main() {
    fstream dataFile("customers.dat", ios::in | ios::out | ios::binary | ios::app);

    if (!dataFile) {
        cerr << "Failed to open data file." << endl;
        return 1;
    }

    int choice;
   
        cout << "1. Add Record" << endl;
        cout << "2. Search Record" << endl;
        cout << "3. Delete Record" << endl;
        cout << "4. Modify Record" << endl;
        cout << "5. Display entire file" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                CustomerAccount newAccount;
                handleNewUserInput(newAccount);
                addRecord(dataFile, newAccount);
                cout << "Account added successfully." << endl;
                break;
            }
            case 2: {
                int accountNumber;
                cout << "Enter Account Number to search: ";
                cin >> accountNumber;

                CustomerAccount foundAccount = searchRecord(dataFile, accountNumber);
                if (foundAccount.accountNumber != -1) {
                    cout << "Account Found:" << endl;
                    displayRecord(foundAccount);
                } else {
                    cout << "Account not found." << endl;
                }
                break;
            }
            case 3: {
                int accountNumber;
                cout << "Enter Account Number to delete: ";
                cin >> accountNumber;

                if (deleteRecord(dataFile, accountNumber)) {
                    cout << "Account deleted successfully." << endl;
                } else {
                    cout << "Account not found or deletion failed." << endl;
                }
                break;
            }
            case 4: {
                int accountNumber;
                cout << "Enter Account Number to modify: ";
                cin >> accountNumber;

                CustomerAccount modifiedAccount;
                handleNewUserInput(modifiedAccount);

                if (modifyRecord(dataFile, accountNumber, modifiedAccount)) {
                    cout << "Account modified successfully." << endl;
                } else {
                    cout << "Account not found or modification failed." << endl;
                }
                break;
            }
            case 5:{
   //             string line;
			// fstream reader;
			// reader.open("customers.dat");

			// while(!reader.eof()){
			// 	getline(reader,line);
			// 	cout<<line<<endl;
        		
			// }
	 	// 	break; 
			
            }   
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }



    dataFile.close();
    return 0;

}



