/*
Jajuan Monroe
Banking System
November 2017
*/

#include <iostream>
#include <fstream>
//#include <cctype>
//#include <iomanip>
#include "Account.h"
using namespace std;

/*

In case you wanted it all in the same file. Just comment out Account.h and include cctype and iomanip

class Account{

	int accountNumber;
	char name[30];
	int money;
	char type;

public:
	void createAccount();	//function to get data from user
	void showAccount() const;	//function to show data on screen
	void modify();	//function to add new data
	void deposit(int);	//function to accept amount and add to balance amount
	void withdraw(int);	//function to accept amount and subtract from balance amount
	void report() const;	//function to show data in tabular format
	int returnAccountNumber() const;	//function to return account number
	int balance() const;	//function to return balance amount
	char returnAccountType() const;	//function to return type of account
};

void Account::createAccount(){

	cout<<"\nEnter the account number :";
	cin>>accountNumber;
	cout<<"\n\nEnter the name of the account holder : ";
	cin.ignore();
	cin.getline(name,30);
	cout<<"\nEnter type of the account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter the initial amount (>=500 for Saving and >=1000 for Checking ) : ";
	cin>>money;
	cout<<"\n\n\nAccount Created...";
}

void Account::showAccount() const{

	cout<<"\nAccount Number : "<<accountNumber;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance Amount : "<<money;
}

void Account::modify(){

	cout<<"\nAccount Number : "<<accountNumber;
	cout<<"\nModify the account holder's name : ";
	cin.ignore();
	cin.getline(name,30);
	cout<<"\nModify the type of account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nModify the balance amount : ";
	cin>>money;
}

void Account::deposit(int x){

	money+=x;
}
	
void Account::withdraw(int x){

	money-=x;
}
	
void Account::report() const{

	cout<<accountNumber<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<money<<endl;
}

int Account::returnAccountNumber() const{

	return accountNumber;
}

int Account::balance() const{

	return money;
}

char Account::returnAccountType() const{

	return type;
}

*/

void writeAccount();	//function to write record in binary file
void displayAccount(int);	//function to display account details given by user
void modifyAccount(int);	//function to modify record of file
void deleteAccount(int);	//function to delete record of file
void displayAll();		//function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account

int main(){

	char choice;
	int num;

	do{

		system("cls");
		cout<<"Welcome to the bank management system. Please choose an option.";
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t1. NEW ACCOUNT";
		cout<<"\n\n\t2. DEPOSIT AMOUNT";
		cout<<"\n\n\t3. WITHDRAW AMOUNT";
		cout<<"\n\n\t4. BALANCE ENQUIRY";
		cout<<"\n\n\t5. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t6. CLOSE AN ACCOUNT";
		cout<<"\n\n\t7. MODIFY AN ACCOUNT";
		cout<<"\n\n\t8. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>choice;

		system("cls");

		switch(choice){

		case '1':
			writeAccount();
			break;

		case '2':
			cout<<"\n\n\tEnter the account number : "; cin>>num;
			deposit_withdraw(num, 1);
			break;

		case '3':
			cout<<"\n\n\tEnter the account number : "; cin>>num;
			deposit_withdraw(num, 2);
			break;

		case '4': 
			cout<<"\n\n\tEnter the account number : "; cin>>num;
			displayAccount(num);
			break;

		case '5':
			displayAll();
			break;

		case '6':
			cout<<"\n\n\tEnter the account number : "; cin>>num;
			deleteAccount(num);
			break;

		 case '7':
			cout<<"\n\n\tEnter the account number : "; cin>>num;
			modifyAccount(num);
			break;

		 case '8':
			cout<<"\n\n\tThank you for using bank management system";
			break;

		 default :cout<<"\a";
		}

		cin.ignore();
		cin.get();

	} while(choice!='8');
	return 0;
}
//Need help? http://www.cplusplus.com/reference/fstream/
//function to write a file

void writeAccount(){

	Account a;
	ofstream output;
	output.open("account.dat",ios::binary|ios::app);
	a.createAccount();
	output.write(reinterpret_cast<char *> (&a), sizeof(Account));
	output.close();
}

//function to read from a specific file

void displayAccount(int n){

	Account a;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);

	if(!inFile){

		cout<<"File could not be opened. Press enter to go back to the main menu.";
		return;
	}

	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&a), sizeof(Account))){

			if(a.returnAccountNumber()==n){

			a.showAccount();
			flag=true;
		}
	}

	inFile.close();

	if(flag==false){
		cout<<"\n\nAccount number does not exist.";
	}
}

//function to modify record of file

void modifyAccount(int n){

	bool found=false;
	Account a;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);

	if(!File){

		cout<<"File could not be open. Press enter to go back to the main menu.";
		return;
	}

	while(!File.eof() && found==false){

		File.read(reinterpret_cast<char *> (&a), sizeof(Account));

		if(a.returnAccountNumber()==n){

			a.showAccount();
			cout<<"\n\nEnter the new details of account"<<endl;
			a.modify();
			int pos=(-1)*static_cast<int>(sizeof(Account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&a), sizeof(Account));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}

	File.close();

	if(found==false){
		cout<<"\n\n Record Not Found ";
	}
}

//function to delete record of file

void deleteAccount(int n){

	Account a;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);

	if(!inFile){

		cout<<"File could not be open !! Press any Key...";
		return;
	}

	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);

	while(inFile.read(reinterpret_cast<char *> (&a), sizeof(Account))){

		if(a.returnAccountNumber()!=n){

			outFile.write(reinterpret_cast<char *> (&a), sizeof(Account));
		}
	}

	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

//function to display all accounts deposit list

void displayAll(){

	Account a;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);

	if(!inFile){

		cout<<"File could not be open !! Press any Key...";
		return;
	}

	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type		Balance\n";
	cout<<"====================================================\n";

	while(inFile.read(reinterpret_cast<char *> (&a), sizeof(Account))){

		a.report();
	}

	inFile.close();
}

//function to deposit and withdraw amounts

void deposit_withdraw(int n, int option){

	int amount;
	bool found=false;
	Account a;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);

	if(!File){

		cout<<"File could not be open !! Press any Key...";
		return;
	}

	while(!File.eof() && found==false){

		File.read(reinterpret_cast<char *> (&a), sizeof(Account));

		if(a.returnAccountNumber()==n){

			a.showAccount();
			if(option==1){

				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amount;
				a.deposit(amount);
			}

			if(option==2){

				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amount;
				int bal=a.balance()-amount;

				if((bal<500 && a.returnAccountType()=='S') || (bal<1000 && a.returnAccountType()=='C')){

					cout<<"Insufficience balance";
				} else{
					a.withdraw(amount);
				}
			}

			int pos=(-1)*static_cast<int>(sizeof(a));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&a), sizeof(Account));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }

	File.close();

	if(found==false){

		cout<<"\n\n Record Not Found ";
	}
}
