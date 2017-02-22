#include "BankAccount.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// Class Functions //

//Constructor
BankAccount::BankAccount()
	: m_name("BOB"), m_acctNum(1234), m_balance(0), m_socialNum(123)
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

