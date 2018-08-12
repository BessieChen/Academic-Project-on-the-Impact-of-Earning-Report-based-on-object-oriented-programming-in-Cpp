//
//  stock.hpp
//  input
//
//  Created by 陈贝茜 on 2017/11/30.
//  Copyright © 2017年 陈贝茜. All rights reserved.
//

#ifndef stock_hpp
#define stock_hpp

#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <iomanip>
#include <algorithm>

using namespace std;

class stock
{
public:
    string Symbol, DateZero;
    vector<string> Date;
    vector<double> AdjClose, Benchmark;
    vector<double> DailyStockReturn;
    vector<double> DailySPYReturn;
    vector<double> DailyAR;
    

    stock() {};
    void setup(string Symbol_, string DateZero_);
    void display();
    void displayonestock();
    void CalculateDailyAR();
};

void stock::setup(string Symbol_, string DateZero_)
{
    Symbol = Symbol_;
    DateZero = DateZero_;
    string temp1;
    double temp2, temp3;
    vector<string> vector1;
    vector<double> vector2, vector3;
    ifstream fin;
    fin.open("_" + Symbol + ".txt");
    while (fin >> temp1 >> temp2 >> temp3)
    {
        vector1.push_back(temp1);
        vector2.push_back(temp2);
        vector3.push_back(temp3);
    }
    fin.close();
    Date = vector1;
    AdjClose = vector2;
    Benchmark = vector3;
}

void stock::display()
{
    for (int i = 0; i < Benchmark.size();i++)
    {
        cout << Date[i] << " " << AdjClose[i] << " " << Benchmark[i] << "\n";
    }
}

void stock::displayonestock()
{
    cout << "Stock Name: " << Symbol << endl;
    cout << "Release Date : " << DateZero << endl;
    
    cout << setiosflags(ios::fixed) << setprecision(3);
    
    cout << setiosflags(ios::right) << setw(10) << "Date" << " | " << setw(12) << "AdjClose" << " | " <<
    setw(7) << "Return" << " | " << setw(10) << "AdjClose (SPY)" << " | " << setw(7) << "Return (SPY)" << " | " << setw(7) <<"Daily AR"<< setw(7) <<endl;
    
    for (int i = 0; i < Date.size() - 1; i++)
    {
        cout << setiosflags(ios::right) << setw(10) << Date[i] << " | " << setw(12) << AdjClose[i] << " | " <<
        setw(7) << DailyStockReturn[i] << " | " << setw(10) << Benchmark[i] << " | " << setw(7) << DailySPYReturn[i] << " | " << setw(7) << DailyAR[i] << setw(7) <<endl;
    }
}
void stock::CalculateDailyAR()
{
    for (int i = 0; i < Date.size()-1;i++)
    {
        double stockreturn = 0.0;
        double SPYreturn = 0.0;
        double difference = 0.0;
        
        stockreturn = (AdjClose[i+1]-AdjClose[i])/AdjClose[i];
        SPYreturn = (Benchmark[i+1]-Benchmark[i])/Benchmark[i];
        difference = stockreturn - SPYreturn;
        
        DailyStockReturn.push_back(stockreturn);
        DailySPYReturn.push_back(SPYreturn);
        DailyAR.push_back(difference);
        
    }
}


#endif /* stock_hpp */
