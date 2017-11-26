#include <iostream>
#include <iomanip>
#include "Account.h"

using namespace std;

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