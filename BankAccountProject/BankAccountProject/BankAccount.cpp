#include "BankAccount.h"
#include <string>
#include <vector>
#include <fstream>

//Default Constructor
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
std::string BankAccount::saveUser()
{return m_name;}

double BankAccount::saveBalance()
{return m_balance;}

int BankAccount::saveAccNum()
{return m_acctNum;}

int BankAccount::saveSocial()
{return m_socialNum;}

//Unused overloaded operators

/*
BankAccount &BankAccount::operator+=(double & amt)
{
	this->m_balance = this->m_balance + amt;
	return *this;
}

BankAccount &BankAccount::operator-=(double & amt)
{
	this->m_balance = this->m_balance - amt;
	return *this;
}
*/

// Class Functions //

void BankAccount::createAccount(std::vector<BankAccount>& usersList, std::string &userName, int &accNum, int &socialNum, double &balance)
{
	system("cls");
	using std::string;
	std::cin.ignore();
	std::cout << "\n Please enter the user's full name: ";
	getline(std::cin, userName);
	do {
		std::cout << "\n Enter the user's account number (4 Numbers): ";
		std::cin >> accNum;
		if (findAcct(usersList, accNum) != -1)
			std::cout << "Incorrect account number! (Account # in use)\n";
	} while (findAcct(usersList, accNum) != -1);

	std::cout << "\n Enter the user's account balance: ";
	std::cin >> balance;
	std::cout << "\n Enter the user's social security number (first three numbers): ";
	std::cin >> socialNum;
	{
		BankAccount newUser(userName, accNum, balance, socialNum);
		usersList.push_back(newUser);
		std::cout << "\n* Account Created *\n\n";
	}
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

int BankAccount::findAcct(std::vector <BankAccount> &usersList, int accNum) //returns index of element in the vector
{
	int index = 0;
	for (auto p = usersList.begin(); p < usersList.end(); p++)
	{
		if (p->m_acctNum == accNum)
		{
			return index; //if account is at position 0 return count as 0
		}
		index++; //else increment
	}
	
	return -1;
}

void BankAccount::Deposit(double amt)
{
	this->m_balance += amt; //didnt need to use overloading
	std::cout << "New balance updated: $" << m_balance << std::endl;
}

void BankAccount::Withdraw(double amt)
{
	this->m_balance -= amt;
	std::cout << "New balance updated: $" << m_balance << std::endl;
}

void BankAccount::AcctMenu(std::vector <BankAccount> &usersList, int accessedAcct)
{
	bool newMenu = true;
	while (newMenu == true)
	{
		std::cout << "__________________________________________\n";
		std::cout << "Welcome " << usersList.at(accessedAcct).m_name << ", Please select an option: \n";
		std::cout << "1. Deposit to Account\n";
		std::cout << "2. Withdraw from Account\n";
		std::cout << "3. Show my account info\n";
		//transfer balance
		std::cout << "Q. Return to Main Menu\n";
		char newMenuInput = '0';
		double amt;
		std::cin >> newMenuInput;
		switch (toupper(newMenuInput))
		{
		case '1':
			std::cout << "Please enter the amount you would like to deposit: "; std::cin >> amt;
			usersList.at(accessedAcct).Deposit(amt); //this actually worked
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
		case '3':
			usersList.at(accessedAcct).showAcctInfo();
			break;
		case 'Q':
			newMenu = false;//exit
			break;
		}
	}

}

// Other functions //

void printMenu()
{
	std::cout << " _______________________\n";
	std::cout << "|*     MAIN MENU     *  |\n";
	std::cout << "|-----------------------|\n";
	std::cout << "| A. Add Account        |\n";
	std::cout << "| B. List All Accounts  |\n";
	std::cout << "| C. Access Account	|\n";
	std::cout << "| Q. Save and Quit      |\n";
	std::cout << "|_______________________|\n";
}

void passwordFunction(bool &admin)
{
	int password = 54321;
	int passwordInc = 0;
	std::cout << "In order to view all user accounts, Please input your 4 digit admin password: " << std::endl;
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
	admin = true;
	std::cout << "\nCorrect password. Logged in as Administrator\nDisplaying all accounts..\n" << std::endl;
}
