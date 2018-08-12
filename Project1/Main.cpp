#include <stdio.h>
#include <string> 
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include "curl.h"
#include "Accessories.h"
#include "Extract.h"
#include "Stock.h"
using namespace std;

int main()
{
	Download();
	int rounds = 3; //Default is 3
	cout << "##########  Welcome! Professor Tang! ############" << endl << endl;
	cout << "Please read instruction carefully and enter the number accordingly." << endl << endl;
	vector<string> type = { "Beat", "Meet", "Miss" };
	vector<map<string, stock>> OldMap = Classification(type);
	SPY SP500; 
	SP500.setvalue("^GSPC");
	vector<map<string, stock>> Symbolmap = benchmark(OldMap, SP500.getAdjClose());

	cout << "Dear user, please enter the rounds of sampling:  " << endl;
	cin >> rounds; //Default is 3, you can type a new value here
	vector<vector<double>> AARs, CAARs;
	Average(rounds, type, Symbolmap, AARs, CAARs);
	vector<vector<vector<double>>> AARandCAAR = Cube(AARs, CAARs);

	cout << endl << endl << endl;
	cout << "##########################" << endl << "########## Menu ##########" << endl << "##########################" << endl;
	bool execute = true;
	int choice;
	while (execute) {
		cout << "Menu Choice: 1, 2, 3, 4, or 5 " << endl;
		cout << "1)Retrieve historical price data for all stocks" << endl;
		cout << "2)Information for one stock" << endl;
		cout << "3)Show AAR or CAAR for one group" << endl;
		cout << "4)Show the graph with CAAR for all 3 groups" << endl;
		cout << "5)Exit the program" << endl << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			displayhistoricalprice(Symbolmap);
			continue;
		case 2:
			displayinformation(Symbolmap);
			continue;
		case 3:
			displayAARandCAARforThreeGroup(AARandCAAR, type);
			continue;
		case 4:
			Plot(AARandCAAR);
			continue;
		case 5:
			execute = false;
			break;
		}
	}
	return 0;
}