#include "BankAccount.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int main()
{
	// Variables and array declaration
	std::string userName;
	int accNum, socialNum;
	double balance;
	static std::vector <BankAccount> usersList;
	static std::vector <BankAccount>::iterator it;

	loadData(usersList, userName, accNum, socialNum, balance); 
	bool isDone = false;
	bool admin = false;
	while (isDone == false) // main while loop
	{
		printMenu();
		char menuInput = 'z';
		std::cout << "\nWhat would you like to do? ";
		std::cin >> menuInput;
		BankAccount access;
		switch ((toupper(menuInput)))
		{
		case 'A':
			access.createAccount(usersList, userName, accNum, socialNum, balance);
			
			break;
		case 'B':
			system("cls"); 
			if (admin == false) { passwordFunction(admin); }//password is 1234
			std::cout << "\nACCOUNT LIST\n";
			for (it = usersList.begin(); it < usersList.end(); it++) //loop through and showacctinfo using iterator 
				it->showAcctInfo();
			break;
		case 'C':
			system("cls"); std::cout << "Enter Account Number: "; std::cin >> accNum;
			if (access.findAcct(usersList, accNum) != -1)
			{
				std::cout << "Account accessed." << std::endl;
				int accessedAcct = access.findAcct(usersList, accNum); //place index of element from vector into variable
				access.AcctMenu(usersList, accessedAcct); //access new menu for withdraw/add to accessed account
			}
			else
				std::cout << "Account not found.\n";
			break;
		case 'Q':
			system("cls");
			isDone = true;
			break;
		}

	}
	saveData(usersList); //save data on exit to file
	std::cout << "\n Exiting Application... Have a good day! \n";
	return 0;
}

