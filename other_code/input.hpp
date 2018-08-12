//
//  input.hpp
//  input
//
//  Created by 陈贝茜 on 2017/11/30.
//  Copyright © 2017年 陈贝茜. All rights reserved.
//

#ifndef input_hpp
#define input_hpp

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "stock.hpp"
using namespace std;

map<string, string> Symbol40(string type)
{
    string symbol, announcement;
    map<string, string> temp;
    ifstream fin;
    fin.open(type + "40.txt");
    while (fin >> symbol >> announcement)
    {
        temp[symbol] = announcement;
    }
    fin.close();
    return temp;
}

vector<stock> reconversion(map<string, string> Symbols)
{
    stock Stock;
    vector<stock> Stocks;
    map<string, string>::iterator itr;
    for (itr = Symbols.begin();itr != Symbols.end();itr++)
    {
        Stock.setup(itr->first, itr->second);
        Stocks.push_back(Stock);
    }
    return Stocks;
}

typedef map<string, stock> Map;
Map reconversion2(map<string, string> Symbols)
{
    stock Stock;
    Map StocksMap;
    map<string, string>::iterator itr;
    for (itr = Symbols.begin();itr != Symbols.end();itr++)
    {
        Stock.setup(itr->first, itr->second);
        Stock.CalculateDailyAR();
        StocksMap[Stock.Symbol] = Stock;
    }
    return StocksMap;
}

#endif /* input_hpp */
