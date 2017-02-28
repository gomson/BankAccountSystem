#include "BankAccount.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>


int main()
{
	passwordFunction(); //password input 1234
	std::string userName;
	int accNum, socialNum;
	double balance;
	static std::vector <BankAccount> usersList;
	static std::vector <BankAccount>::iterator it;
	loadData(usersList, userName, accNum, socialNum, balance);
	bool isDone = false;
	while (isDone == false)
	{
		printMenu();
		char menuInput = 'z';
		std::cout << "\nWhat would you like to do? ";
		std::cin >> menuInput;
		BankAccount access;
		switch ((toupper(menuInput)))
		{
		case 'A':
			std::cin.ignore();
			std::cout << "\n Please enter the user's full name: ";
			std::getline(std::cin, userName);
			std::cout << "\n Enter the user's account number (4 Numbers): ";
			std::cin >> accNum;
			std::cout << "\n Enter the user's account balance: ";
			std::cin >> balance;
			std::cout << "\n Enter the user's social security number (first three numbers): ";
			std::cin >> socialNum;
			{
				BankAccount newUser(userName, accNum, balance, socialNum);
				usersList.push_back(newUser);
				std::cout << "\n* Account Created *\n\n";
			}
			break;
		case 'B':
			std::cout << "\nACCOUNT LIST\n";
			for (it = usersList.begin(); it < usersList.end(); it++) //loop through and showacctinfo using iterator 
				it->showAcctInfo();
			break;
		case 'C':
			std::cout << "Enter Account Number: "; std::cin >> accNum;
			if (access.findAcct(usersList, accNum) != -1)
			{
				int accessedAcct = access.findAcct(usersList, accNum);
				access.AcctMenu(usersList,accessedAcct);//access new menu for withdraw/add to accessed account
			}
			else
				std::cout << "Account not found.\n";
			break;
		case 'Q':
			isDone = true;
			break;
		}

	}
	saveData(usersList);
	std::cout << "Exiting Application... GoodBye!\n";
	return 0;
}
