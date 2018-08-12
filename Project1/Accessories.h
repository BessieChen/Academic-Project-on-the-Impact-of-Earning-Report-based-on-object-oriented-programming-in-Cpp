#ifndef Accessories_h
#define Accessories_h

#include <string> 
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <ctime>
#include <locale>
#include "Extract.h"
#include "Stock.h"
#include "Operator.h"
using namespace std;

void Download()
{
	remove("Results.csv");
	string symbol, date;
	double est, act;
	vector<string> Symbols;
	ifstream fin;
	ofstream fout;
	fin.open("EPS.txt");
	while (fin >> symbol >> est >> act >> date)
	{
		Symbols.push_back(symbol);
	}
	Symbols.push_back("^GSPC");//adding benchmark ticker
	fin.close();
	Extract(Symbols);//download stock information including benchmark
	// distributing data into seperately files
	cout << "Distributing downloaded files . . ." << endl;
	int i = 0;
	string Date, Open, High, Low, Close, AdjClose1, Volume;
	double AdjClose2;
	vector<string> Temp1;
	vector<double> Temp2;
	fin.open("Results.csv");
	while (getline(fin, Date, ','), getline(fin, Open, ','), getline(fin, High, ','), getline(fin, Low, ','), getline(fin, Close, ','), getline(fin, AdjClose1, ','), getline(fin, Volume))
	{
		if (Date == "Date")
		{
			fout.close();
			Temp1.clear();
			Temp2.clear();
			fout.open(Symbols[i] + ".bat");//storage single stock data into .bat file
			i++;
		}
		else
		{
			AdjClose2 = stod(AdjClose1);
			fout << Date << " " << AdjClose1 << endl;
			Temp1.push_back(Date);
			Temp2.push_back(AdjClose2);
			//extract the date and adjclose into two vectors to support calculation
		}
	}
	fin.close();
}


vector<map<string, stock>> Classification(vector<string> type)
{
	cout << "Importing downloaded files and classifying the types . . ." << endl;
	string symbol, date;
	double est, act, upper = 0.05, lower = -0.03;//screening conditions
	stock onestock;
	vector<string> multisymbol;
	vector<stock> multistock;
	vector<map<string, stock>> OldMap(type.size());
	ifstream fin;
	ofstream fout;
	fin.open("EPS.txt");
	while (fin >> symbol >> est >> act >> date)
	{
		multisymbol.push_back(symbol);
		onestock.setvalue(symbol, date, est, act);//using function from stcok.h
		multistock.push_back(onestock);
	}
	fin.close();
	for (int i = 0; i < multistock.size(); i++)//size=498
	{
		if (multistock[i].getPercentage() >= upper)//using getPercentage function from stock.h
		{
			multistock[i].setType(type[0]);
			OldMap[0][multisymbol[i]] = multistock[i];//beat
		}
		else if (multistock[i].getPercentage() <= lower)
		{
			multistock[i].setType(type[2]);
			OldMap[2][multisymbol[i]] = multistock[i];//miss
		}
		else
		{
			multistock[i].setType(type[1]);
			OldMap[1][multisymbol[i]] = multistock[i];//meet
		}
		//storage the group into a three-element vector, every element is a map
	}
	return OldMap;
}
//matching and adding benchmark adj close
vector<map<string, stock>> benchmark(vector<map<string, stock>> OldMap, vector<double> Benchmark)
{
	cout << "Adding SPY as the benchmark and matching the dates . . ." << endl;
	vector<map<string, stock>> Stocks;
	stock Stock;
	map<string, stock>::iterator itr;
	for (int i = 0; i < OldMap.size(); i++)
	{
		map<string, stock> temp;
		for (itr = OldMap[i].begin(); itr != OldMap[i].end(); itr++)
		{
			Stock.setvalue(itr->first, OldMap[i], Benchmark);
			temp[itr->first] = Stock;
		}
		Stocks.push_back(temp);
	}
	return Stocks;
}
//randomly select 40 stocks for every group
vector<map<string, stock>> Random40(vector<string> type, vector<vector<string>> & Symbol40, vector<map<string, stock>> OldMap)
{
	cout << "Randomly selecting 40 stocks for each type . . ." << endl;
	vector<map<string, stock>> Clean40;
	int samples = 40;
	ofstream fout;
	srand(time(NULL));
	map<string, stock>::iterator itr;

	for (int j = 0; j < OldMap.size(); j++)
	{
		map<string, stock> temp;
		for (int i = 0; i < samples; i++)
		{
			itr = OldMap[j].begin();
			std::advance(itr, rand() % OldMap[j].size());//random select
			if (find(Symbol40[j].begin(), Symbol40[j].end(), itr->first) != Symbol40[j].end())
				i--;
			else
			{
				Symbol40[j].push_back(itr->first);
				temp[itr->first] = itr->second;
			}
		}
		Clean40.push_back(temp);
	}
	return Clean40;
}
//calculaying AAR by using matrix
vector<vector<double>> CalculateAAR(vector<map<string, stock>> MapsForThreeTypes)
{
	cout << "Calculating AARs . . ." << endl;
	vector<vector<double>> AARForThreeTypes;
	for (int n = 0; n < MapsForThreeTypes.size(); n++) // n =0,1,2
	{
		int days;
		map<string, stock>::iterator it;
		it = MapsForThreeTypes[n].begin();
		days = it->second.getDailyAR().size(); //60 days
		vector<double> temp(days);

		while (it != MapsForThreeTypes[n].end())
		{
			temp = temp + it->second.getDailyAR();
			it++;
		}
		temp = temp / MapsForThreeTypes[n].size();
		AARForThreeTypes.push_back(temp);
	}
	return AARForThreeTypes;
}
//calculaying AAR by using matrix
vector<vector<double>> CalculateCAAR(vector<map<string, stock>> MapsForThreeTypes, vector<vector<double>> AARForThreeTypes)
{
	cout << "Calculating CAARs . . ." << endl;
	vector<vector<double>> CAARForThreeTypes;
	for (int n = 0; n < MapsForThreeTypes.size(); n++)
	{
		int days;
		map<string, stock>::iterator it;
		it = MapsForThreeTypes[n].begin();
		days = it->second.getDailyAR().size();
		vector<double> temp(days);
		double sum = 0.0;

		for (int i = 0; i < days; i++)
		{
			sum += AARForThreeTypes[n][i];
			temp[i] = sum;
		}
		CAARForThreeTypes.push_back(temp);
	}
	return CAARForThreeTypes;
}
//calculating average AAR & CAAR from three(can be more than three) outcomes by using matrix and operator overloading
void Average(int rounds, vector<string> type, vector<map<string, stock>> Symbolmap, vector<vector<double>> & AARs, vector<vector<double>> & CAARs)
{
	vector<map<string, stock>> temp1;
	vector<vector<string>> Symbols(type.size());
	cout << "Averaging Round 1:" << endl;
	temp1 = Random40(type, Symbols, Symbolmap);
	AARs = CalculateAAR(temp1);
	CAARs = CalculateCAAR(temp1, AARs);
	for (int i = 0; i < rounds - 1; i++)
	{
		Symbols.clear(); Symbols.resize(type.size()); temp1.clear();
		cout << "Averaging Round " << i + 2 << ":" << endl;
		temp1 = Random40(type, Symbols, Symbolmap);
		vector<vector<double>> temp2 = CalculateAAR(temp1);
		vector<vector<double>> temp3 = CalculateCAAR(temp1, temp2);
		AARs = AARs + temp2;
		CAARs = CAARs + temp3;
	}
	AARs = AARs / rounds;
	CAARs = CAARs / rounds;
}
//storage AAR & CAAR into a cube
vector<vector<vector<double>>> Cube(vector<vector<double>> AARForThreeTypes, vector<vector<double>> CAARForThreeTypes)
{
	cout << "Combining AARs and CAARs . . ." << endl;
	vector<vector<vector<double>>> Cube;
	Cube.push_back(AARForThreeTypes);
	Cube.push_back(CAARForThreeTypes);
	return Cube;
}
void OutputAARandCAAR(vector<vector<vector<double>>> AARandCAAR)
{
	ofstream fout;
	fout.open("Test.csv");
	for (int i = 0; i < AARandCAAR[0][0].size(); i++)
		fout << i - 29 << "," << AARandCAAR[0][0][i] << "," << AARandCAAR[0][1][i] << "," << AARandCAAR[0][2][i] << "," << AARandCAAR[1][0][i] << "," << AARandCAAR[1][1][i] << "," << AARandCAAR[1][2][i] << "\n";
	fout.close();
}
//using Gnuplot to draw CAAR trend
void Plot(vector<vector<vector<double>>> AARandCAAR)
{
	ofstream fout;
	fout.open("CAAR.txt");
	for (int i = 0; i < AARandCAAR[1][0].size(); i++)
	{
		fout << i - 29 << " " << AARandCAAR[1][0][i] << " " << AARandCAAR[1][1][i] << " " << AARandCAAR[1][2][i] << endl;
	}
	fout.close();

	fout.open("Plot.txt");
	fout << "set title \"CAAR\"" << endl;
	fout << "plot 'CAAR.txt' using 1:2 title 'Beat' with lines, 'CAAR.txt' using 1:3 title 'Meet' with lines, 'CAAR.txt' using 1:4 title 'Miss' with lines" << endl;
	fout << "pause -1" << endl;
	fout.close();
	system("C:\\gnuplot\\bin\\gnuplot Plot.txt");
}


void displayhistoricalprice(vector<map<string, stock>> Symbolmap)//Question1：Retrieve historical price data for all stocks.
{
	cout << setiosflags(ios::fixed) << setprecision(4);

	for (int n = 0; n < Symbolmap.size(); n++)
	{
		map<string, stock>::iterator it;
		it = Symbolmap[n].begin();

		while (it != Symbolmap[n].end())
		{
			cout << "Stock Name : " << it->second.getSymbol() << endl;
			cout << setiosflags(ios::internal) << setw(10) << "Date" << " | "
				<< setw(12) << "AdjClose" << "  " << setw(7) << endl;

			for (int i = 0; i < it->second.getDate().size(); i++)
			{
				cout << setiosflags(ios::internal) << setw(10) << it->second.getDate()[i] << " | "
					<< setw(12) << it->second.getAdjClose()[i] << setw(7) << endl;
			}
			it++;
		}
	}
}

//question 2
void displayinformation(vector<map<string, stock>> Symbolmap)

{
	map<string, stock>::iterator itr;
	for (int n = 0; n < Symbolmap.size(); n++)
	{
		itr = Symbolmap[n].begin();
		while (itr != Symbolmap[n].end())
		{
			cout << itr->first << "\n";
			itr++;
		}
	}
	cout << "Please choose a specific stock ticker listed above only: " << endl;
	bool test, execute = true;
	while (execute)
	{
		string Symbol;
		cin >> Symbol;
		if (Upper(Symbol) == "BACK")
		{
			execute = false;
			break;
		}
		for (int n = 0; n < Symbolmap.size(); n++)
		{
			if (Symbolmap[n].find(Upper(Symbol)) != Symbolmap[n].end())
			{
				Symbolmap[n].find(Upper(Symbol))->second.displayonestock();
				test = true;
				cout << "Please enter an additional stock ticker \nOr please enter 'Back' to return to the main menu: " << endl;
				break;
			}
			else test = false;
		}
		if (test == false)
		{
			for (int n = 0; n < Symbolmap.size(); n++)
			{
				itr = Symbolmap[n].begin();
				while (itr != Symbolmap[n].end())
				{
					cout << itr->first << "\n";
					itr++;
				}
			}
			cout << "Tikcer undetected, please input another stock ticker listed above only: " << endl;
		}
	}
}

//question 3
void displayAARandCAARforThreeGroup(vector<vector<vector<double>>> Cube, vector<string> type)
{
	cout << setiosflags(ios::fixed) << setprecision(4);
	cout << setiosflags(ios::left) << setw(6) << " Type |" << setw(17) << "     Beat" << setw(17) << "        Meet" << setw(17) << "       Miss" << setw(7) << endl;
	cout << setiosflags(ios::left) << setw(6) << " Date |" << setw(10) << "    AAR  " << setw(7) << "  CAAR " << "  ||" << setw(10) << "    AAR  " << setw(7) << "  CAAR " << "  ||" << setw(10) << "    AAR  " << "" << setw(7) << "  CAAR " << "  ||" << endl;

	for (int i = 0; i < Cube[0][0].size(); i++)
		cout << setiosflags(ios::right) << setw(6) << i - 29 << "|" << setw(10) << Cube[0][0][i] << " " << setw(7) << Cube[0][1][i] << " " << "||" << setw(10) << Cube[0][2][i] << " " << setw(7) << Cube[1][0][i] << " " << "||" << setw(10) << Cube[1][1][i] << " " << "" << setw(7) << Cube[1][2][i] << " " << "||" << endl;

}
#endif
