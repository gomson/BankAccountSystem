#ifndef BANKACCOUNT
#define BANKACCOUNT
#include "BankAccount.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class BankAccount
{
private:
	std::string m_name;
	int m_acctNum;
	double m_balance;
	int m_socialNum;
public:
	//Functions
	void createAccount(std::vector<BankAccount>& usersList, std::string &userName, int &accNum, int &socialNum, double &balance);
	void showAcctInfo();
	void AcctMenu(std::vector <BankAccount> &usersList, int accessedAcct);
	void Deposit(double amt);
	void Withdraw(double amt);
	int findAcct(std::vector <BankAccount> &usersList, int accNum);
	//constructors
	BankAccount();
	BankAccount(std::string userName, int accNum, double balance, int socialNum);
	//overloaded operators
	BankAccount &operator+=(double &amt);
	BankAccount &operator-=(double &amt);
	//data save 
	std::string saveUser();
	int saveAccNum();
	double saveBalance();
	int saveSocial();
};
//other functions
void passwordFunction();
void printMenu();
//save/load from file functions
void saveData(std::vector <BankAccount> &usersList);
void loadData(std::vector <BankAccount> &usersList, std::string &userName, int &accNum, int &socialNum, double &balance);
bool is_file_exist(std::string fileName);

#endif
