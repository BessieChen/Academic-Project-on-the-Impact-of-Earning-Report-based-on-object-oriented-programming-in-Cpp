#ifndef Stock_h
#define Stock_h

#include <string> 
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <stdio.h>
#include "Accessories.h"

using namespace std;

class SPY
{
protected:
	string Symbol;
	vector<string> Date;
	vector<double> AdjClose;

public:
	void setvalue(string Symbol_);
	void import();
	vector<double> getAdjClose() { return AdjClose; }
	vector<string> getDate() { return Date; }
	string getSymbol() { return Symbol; }
};

class stock:public SPY
{
private:
	string DateZero, Type;
	double EstEPS, ActEPS, EPSpercentage;
	vector<double> Benchmark, DailyStockReturn, DailySPYReturn, DailyAR;
public:
	void setvalue(string Symbol_, string DateZero_, double EstEPS_, double ActEPS_);
	void setvalue(string Symbol_, map<string, stock> OldMap, vector<double> Benchmark_);
	void setType(string Type_) { Type = Type_; };
	void output();
	void arrangedate();
	void CalculateDailyAR();
	void displayonestock();

	vector<double> getDailyAR() { return DailyAR; }
	vector<double> getDailyStockReturn() { return DailyStockReturn; }//
	vector<double> getDailySPYReturn() { return DailySPYReturn; }//
	vector<double> getBenchmark() { return Benchmark; }//
	string getDateZero() { return DateZero; }
	string getType() { return Type; }
	double getEstEPS() { return EstEPS; }
	double getActEPS() { return ActEPS; }
	double getPercentage() { return EPSpercentage; }
};

void SPY::import()
{
	string Date1;
	double AdjClose2;
	vector<string> Temp1;
	vector<double> Temp2;
	ifstream fin;
	ofstream fout;
	fin.open(Symbol + ".bat");
	while (fin >> Date1 >> AdjClose2)
	{
		Temp1.push_back(Date1);
		Temp2.push_back(AdjClose2);
	}
	fin.close();
	Date = Temp1;
	AdjClose = Temp2;
}

void SPY::setvalue(string Symbol_)
{
	Symbol = Symbol_;
	import();
	//output();
}

void stock::setvalue(string Symbol_, string DateZero_, double EstEPS_, double ActEPS_)
{
	Symbol = Symbol_; DateZero = DateZero_; EstEPS = EstEPS_; ActEPS = ActEPS_;
	if (EstEPS >= 0) EPSpercentage = ActEPS / EstEPS - 1;
	else EPSpercentage = 1 - ActEPS / EstEPS;
	import();
}
void stock::setvalue(string Symbol_, map<string, stock> OldMap, vector<double> Benchmark_)
{
	Symbol = Symbol_;
	DateZero = OldMap.find(Symbol)->second.getDateZero();
	EstEPS = OldMap.find(Symbol)->second.getEstEPS();
	ActEPS = OldMap.find(Symbol)->second.getActEPS();
	Type = OldMap.find(Symbol)->second.getType();
	Date = OldMap.find(Symbol)->second.getDate();
	AdjClose = OldMap.find(Symbol)->second.getAdjClose();
	Benchmark = Benchmark_;
	arrangedate();
	CalculateDailyAR();
}

void stock::arrangedate()
{
	int index;
	vector<string> temp1;
	vector<double> temp2, temp3;
	for (int i = 0; i < Date.size(); i++)
	{
		if (Date[i] == DateZero)
		{
			index = i;
		}
	}
	for (int k = index - 30; k <= index + 30; k++)
	{
		temp1.push_back(Date[k]);
		temp2.push_back(AdjClose[k]);
		temp3.push_back(Benchmark[k]);
	}
	Date = temp1;
	AdjClose = temp2;
	Benchmark = temp3;
}
void stock::output()
{
	ofstream fout;
	fout.open(Symbol + ".dat");
	for (int i = 0; i < DailyAR.size(); i++)
	{
		fout << Symbol << " " << DateZero << " " << EstEPS << " " << ActEPS << " " << Type << " " << Date[i + 1] << " " << AdjClose[i + 1] << " " << Benchmark[i + 1] << " " << DailyAR[i] << "\n";
	}
	fout.close();
}

void stock::displayonestock()
{
	cout << "Stock Ticker: " << Symbol << endl;
	cout << "Release Date : " << DateZero << endl;
	cout << "Estimated EPS: " << EstEPS << endl;
	cout << "Actual EPS: " << ActEPS << endl;
	cout << "Stock Group : " << Type << endl << endl;

	cout << setiosflags(ios::fixed) << setprecision(3);

	cout << setiosflags(ios::right) << setw(10) << "Date" << " | " << setw(12) << "AdjClose" << " | " <<
		setw(7) << "Return" << " | " << setw(16) << "AdjClose (SPY)" << " | " << setw(16) << "Return (SPY)" << " | " << setw(7) << "Daily AR" << setw(7) << endl;

	cout << setiosflags(ios::right) << setw(10) << Date[0] << " | " << setw(12) << AdjClose[0] << " | " << setw(7) << "" << " | " << setw(16) << Benchmark[0] << " | " << setw(16) << "" << " | " << setw(7) << "" << setw(7) << endl;

	for (int i = 0; i < DailyAR.size(); i++)
	{
		cout << setiosflags(ios::right) << setw(10) << Date[i + 1] << " | " << setw(12) << AdjClose[i + 1] << " | " <<
			setw(7) << DailyStockReturn[i] << " | " << setw(16) << Benchmark[i + 1] << " | " << setw(16) << DailySPYReturn[i] << " | " << setw(7) << DailyAR[i] << setw(7) << endl;
	}
}

void stock::CalculateDailyAR()
{
	double stockreturn, SPYreturn, difference;
	vector<double> temp1, temp2, temp3;
	for (int i = 0; i < Date.size() - 1; i++)
	{
		stockreturn = (AdjClose[i + 1] - AdjClose[i]) / AdjClose[i];
		SPYreturn = (Benchmark[i + 1] - Benchmark[i]) / Benchmark[i];
		difference = stockreturn - SPYreturn;

		temp1.push_back(stockreturn);
		temp2.push_back(SPYreturn);
		temp3.push_back(difference);
	}
	DailyStockReturn = temp1;
	DailySPYReturn = temp2;
	DailyAR = temp3;
}
#endif