/*
Written by: SaEeD

Description:
*/

#include <iostream>
#include <limits>
#include "MyMACAddr.h"



//-----------------------------------------------
//Main Menu
void Menu() {

	cout << "Please select one of below options:\n" <<
		"\t1)Generate Random MAC Address Only.\n" <<
		"\t2)Show Network Adapters Details.\n" <<
		"\t3)Assing Random MAC Address to Network Interface.\n" <<
		"\t4)Network Interfaces Summary.\n"
		"\t5)Exit.\nSelection: ";

}
//-----------------------------------------------
// Short Summary of network interfaces
void AdaptersSummary(MyMACAddr &ptr)
{
	unordered_map<string, string> list = ptr.getAdapters();
	for (auto &itm : list)
	{
		cout << "Name: " << itm.first << "\t\tMAC Address: " << itm.second << endl;
	}
}


int main(int argc, char **argv)
{
	cout << "\t===================================\n"
		<< "\t|   SaEeD's MAC Address Changer   |\n"
		<< "\t===================================\n" << endl;

	//-----------------------------------------------
	//Initializing  the MAC address class
	MyMACAddr *ptr = new MyMACAddr();

	while (true)
	{
		Menu();

		//-----------------------------------------------
		// Input validation
		int selection = 0;
		cin >> selection;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cerr << "[!]Invalid Selection Input!" << endl;
			continue;
		}
		//-----------------------------------------------

		//-----------------------------------------------
		// Menu selection
		switch (selection)
		{
		case 1:
			cout << "\n[+]Generated Random MAC Address:\t" << ptr->GenRandMAC() << "\n" << endl;;
			break;
		case 2:
			cout << "----------- Details: -----------" << endl;
			ptr->showAdapterList();
			cout << "-------------  End  ------------\n" << endl;
			break;
		case 3:
			ptr->AssingRndMAC();
			break;
		case 4:
			cout << "----------- Details: -----------" << endl;
			AdaptersSummary(*ptr);
			cout << "-------------  End  ------------\n" << endl;
			break;
		case 5:
			return EXIT_SUCCESS;
		default:
			cout << "[!]Invalid Selection. Try again!" << endl;
			break;
		}
	}		

	return EXIT_SUCCESS;
}