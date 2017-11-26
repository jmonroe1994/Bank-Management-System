/*
Jajuan Monroe
Banking System
November 2017
*/

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