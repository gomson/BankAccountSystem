#include "BankAccount.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// Class Functions //

//Constructor
BankAccount::BankAccount()
	: m_name(""), m_acctNum(1234), m_balance(0), m_socialNum(123)
{

}

//Overloaded constructor
BankAccount::BankAccount(std::string userName, int accNum, double balance, int socialNum)
	: m_name(userName), m_acctNum(accNum), m_balance(balance), m_socialNum(socialNum)
{

}

//functions returning member variables to fill
void saveData(std::vector <BankAccount> &usersList)
{
	std::string fileName;
	std::vector <BankAccount>::iterator it;
	std::cin.ignore();
	std::cout << "Enter full name of savefile: ";
	getline(std::cin, fileName);
	std::ofstream outFile;
	outFile.open(fileName);
	if (outFile.is_open())
	{
		std::cout << "Saving data to file... \n";
		for (it = usersList.begin(); it < usersList.end(); it++)
		{
			outFile << it->saveUser() << std::endl;
			outFile << it->saveAccNum() << std::endl;
			outFile << it->saveBalance() << std::endl;
			outFile << it->saveSocial() << std::endl;
		}
		outFile.close();
	}
	else
		std::cout << "File error!\n";
}
bool is_file_exist(std::string fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}
void loadData(std::vector <BankAccount> &usersList, std::string &userName, int &accNum, int &socialNum, double &balance)
{
	std::ifstream infile;
	std::string ifilename, line;
	std::cout << "Please input full name of file to load: ";
	std::cin >> ifilename;
	if (is_file_exist(ifilename))
	{
		std::cout << "Loading File...\n";
	}
	else
		std::cout << "Created new file." << std::endl;
	infile.open(ifilename);
	if (infile.is_open())
	{
		while (getline(infile, userName))
		{
			getline(infile, line);
			accNum = stoi(line);

			getline(infile, line);
			socialNum = stoi(line);

			getline(infile, line);
			balance = stod(line);

			BankAccount newUser(userName, accNum, socialNum, balance);
			usersList.push_back(newUser);
		}
		infile.close();
		std::cout << "File loaded! \n\n";
	}
}

BankAccount & BankAccount::operator+=(double & amt)
{
	this->m_balance = this->m_balance + amt;
	return *this;
}

BankAccount & BankAccount::operator-=(double & amt)
{
	this->m_balance = this->m_balance - amt;
	return *this;
}

std::string BankAccount::saveUser()
{
	return m_name;
}

double BankAccount::saveBalance()
{
	return m_balance;
}

int BankAccount::saveAccNum()
{
	return m_acctNum;
}

int BankAccount::saveSocial()
{
	return m_socialNum;
}

void BankAccount::showAcctInfo()
{
	using std::cout;
	cout << "______________________________" << std::endl;
	cout << "Name: " << m_name << std::endl;
	cout << "Account Number: #" << m_acctNum << std::endl;
	cout << "Social Security Number: " << m_socialNum << "-XX-XXXX" << std::endl;
	cout << "Balance: $" << m_balance << std::endl;
	cout << "______________________________" << std::endl;
}

int BankAccount::findAcct(std::vector <BankAccount> &usersList, int accNum)
{
	int count = 0;
	for (auto p = usersList.begin(); p != usersList.end(); p++)
	{
		if (p->m_acctNum == accNum)
		{
			std::cout << "Account accessed." << std::endl;
			return count;
		}
		count++;
	}
	
	return -1;
}

void BankAccount::AcctMenu(std::vector <BankAccount> &usersList, int accessedAcct)
{
	BankAccount access;
	bool newMenu = true;
	while (newMenu == true)
	{
		std::cout << "Welcome " << usersList.at(accessedAcct).m_name << ", Please select an option: \n";
		std::cout << "1. Deposit to Account\n";
		std::cout << "2. Withdraw from Account\n";
		//show account info #3
		std::cout << "Q. Return to Main Menu\n";
		char newMenuInput = '0';
		double amt;
		std::cin >> newMenuInput;
		switch (toupper(newMenuInput)) 
		{
		case '1':
			std::cout << "Please enter the amount you would like to deposit: "; std::cin >> amt;
			usersList.at(accessedAcct).Deposit(amt);
			break;
		case '2':
			if (usersList.at(accessedAcct).m_balance != 0)
			{
				std::cout << "Please enter the amount you would like to withdraw: "; std::cin >> amt;
				if (amt <= usersList.at(accessedAcct).m_balance) // if the amt is less than or equal to the balance 
					usersList.at(accessedAcct).Withdraw(amt); //then withdraw the amt
				else
					std::cout << "You entered an amount larger than your current balance.\n";
			}
			else
				std::cout << "No balance on account!\a\n";
			break;
		case 'Q':
			newMenu = false;
			break;
		}
	}

}

void BankAccount::Deposit(double amt)
{
	this->m_balance += amt;
	std::cout << "New balance: " << m_balance << std::endl;
}

void BankAccount::Withdraw(double amt)
{
	this->m_balance -= amt;
	std::cout << "New balance: " << m_balance << std::endl;
}

//Password
void passwordFunction()
{
	int password = 54321;
	int passwordInc = 0;
	std::cout << "Please input your 4 digit password: " << std::endl;
	while (password != 1234) //breaks out of password input loop 
	{
		std::cin >> password;
		if (std::cin.fail())
		{
			std::cout << "ERROR -- You did not enter an integer\n";

			// get rid of failure state
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (password == 1234)
			break;

		std::cout << "\aIncorrect Password - Please try again." << std::endl;
		passwordInc++;
		if (passwordInc >= 3)
			std::cout << "psst! The password is 1234! \n";
	}
	std::cout << "Correct password. Logged in as administrator.\n\n" << std::endl;
}

void printMenu()
{
	std::cout << " _______________________\n";
	std::cout << "|*     MAIN MENU     *  |\n";
	std::cout << "|-----------------------|\n";
	std::cout << "| A. Add Account        |\n";
	std::cout << "| B. List Accounts      |\n";
	std::cout << "| C. Access Account	|\n";
	std::cout << "| Q. Save and Quit      |\n";
	std::cout << "|_______________________|\n";
}