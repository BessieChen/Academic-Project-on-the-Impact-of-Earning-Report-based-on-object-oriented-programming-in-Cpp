//
//  calculation.hpp
//  input
//
//  Created by 陈贝茜 on 2017/11/30.
//  Copyright © 2017年 陈贝茜. All rights reserved.
//

#ifndef calculation_hpp
#define calculation_hpp

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include "operator.hpp"
#include "stock.hpp"
#include "input.hpp"
#include "operator.hpp"


class Calculation: public stock
{
public:
    
    vector<map<string, stock>> MapsForThreeTypes;
    vector<vector<double>> DailyARForThreeTypes;
    vector<vector<double>> AARForThreeTypes;
    vector<vector<double>> CAARForThreeTypes;
    
    void setupMapsForThreeTypes();
    void setupDailyARForThreeTypes();
    void CalculateAAR();
    void CalculateCAAR();
    
    void displayhistoricalprice();//用于回答菜单第一个问题：Retrieve historical price data for all stocks.
    void displayinformation();//用于回答菜单第2个问题
    void showAARandCAAR();//第三个问题
    void showExcelGraph();
};

void Calculation::setupMapsForThreeTypes()
{
    string type[3] = { "Beat", "Meet", "Miss" };
    vector<map<string, string>> Type;
    for (int i = 0;i < 3;i++)
        Type.push_back(Symbol40(type[i]));
    
    vector<map<string, stock>> classfication;
    
    for (int k = 0;k < Type.size();k++)
        classfication.push_back(reconversion2(Type[k]));
    
    MapsForThreeTypes = classfication;
    
}

void Calculation::setupDailyARForThreeTypes()
{
    int type;
    type = MapsForThreeTypes.size();
    
    for(int i = 0; i<type; i++)
    {
        map<string, stock>::iterator it;
        for(it = MapsForThreeTypes[i].begin(); it!= MapsForThreeTypes[i].end(); it++)
        {
            DailyARForThreeTypes.push_back(it->second.DailyAR);
        }
    }
    
}


void Calculation::CalculateAAR()
{
    
    /*int days;
    
    Map::iterator it;
    it = stockmap.begin();
    days = it->second.DailyAR.size();
    
    vector<double> temp(days);
    while(it != stockmap.end())
    {
        temp = temp + it->second.DailyAR;
        it++;
    }
    temp = temp/days;
     */
    
    for (int n = 0; n < MapsForThreeTypes.size(); n++) // n =0,1,2
    {
        int days;
        map<string, stock>::iterator it;
        it = MapsForThreeTypes[n].begin();
        days = it->second.Date.size(); //61天
        vector<double> temp(days);
        
        while(it != MapsForThreeTypes[n].end()) //it = 40个股票
        {
            temp = temp + it->second.DailyAR;
            it++;
        }
        temp = temp/days;
        AARForThreeTypes.push_back(temp);
    }
    
}

void Calculation::CalculateCAAR()
{
    for (int n = 0; n < MapsForThreeTypes.size(); n++)
    {
        int days;
        map<string, stock>::iterator it;
        it = MapsForThreeTypes[n].begin();
        days = it->second.Date.size();
        vector<double> temp(days);
        double sum = 0.0;
        
        for(int i = 0; i<days; i++)
        {
            sum += AARForThreeTypes[n][i];
            temp[i] = sum;
        }
        
        CAARForThreeTypes.push_back(temp);
}



void Calculation::displayhistoricalprice()//用于回答菜单第一个问题：Retrieve historical price data for all stocks.
{
    cout << setiosflags(ios::fixed) << setprecision(4);
    
    for (int n = 0; n < MapsForThreeTypes.size(); n++)
    {
        map<string, stock>::iterator it;
        it = MapsForThreeTypes[n].begin();
        
        while(it != MapsForThreeTypes[n].end())
        {
            for (int i = 0; i < it->second.Date.size(); i++)
            {
                cout << "Stock Name : "<<it->second.Symbol <<endl;
                cout << setiosflags(ios::right) << setw(10) << "Date" << " | "
                << setw(12) << "AdjClose" << " | "<<setw(7) << endl;
                
                cout << setiosflags(ios::right) << setw(10) << it->second.Date[i] << " | "
                << setw(12) << it->second.AdjClose[i] << " | " <<setw(7) <<endl;
                
            }
            it++;
        }
    }

}

void Calculation::displayinformation()
{
    cout<<"Please choose an number which represent a specific stock group: for 1 is Beat, for 2 is Meet, for 3 is Miss."<<endl;
    
    int z = 0;
    int grouptype;
    
    Map newmap;
    
    if(z==0);
    {
        cin>>grouptype;
        if(grouptype == 1)
        {
            newmap = MapsForThreeTypes[0];
            z = 1;
            cout<<"Names of all stocks in group Beat are : "<<endl;
        }
        
        else if(grouptype == 2)
        {
            newmap = MapsForThreeTypes[1];
            z = 2;
            cout<<"Names of all stocks in group Meet are : "<<endl;
        }
        
        else if(grouptype == 3)
        {
            newmap = MapsForThreeTypes[2];
            z = 3;
            cout<<"Names of all stocks in group Miss are : "<<endl;
        }
        else
        {
            cout<<"Illegal input, please input again."<<endl;
        }
    }
    
    Map::iterator it;
    
    while (it != newmap.end())
    {
        cout<<it->first<<endl;
        it ++;
    }
    
    cout<<"Please choose a specific stock for this group: "<<endl;
    
    string Symbol;
    cin>>Symbol;
    
    it = newmap.begin();
    while(it != newmap.end())
    {
        if(it->first == Symbol)
        {
            it->second.displayonestock();
            break;
        }
        else{it++;}
    }
}

void Calculation::showAARandCAAR()
{
   
    cout << "Please choose a group for AAR, in the form of meet-1/beat-2/miss-3/" << endl;
    int a = 0;

    while (a == 0)
    {
        cin >> a;
        if (a == 1)
        {
            cout << "the AAR for Beat is" << endl;
        }
        else if (a == 2)
        {
            cout << "the AAR for Meet is" << endl;
        }
        else if (a == 3)
        {
            cout << "the AAR for Miss is" << endl;
        }
        else
        {
            cout << "Illegal input, please input again" << endl;
        }
        
    }
    
    cout << setiosflags(ios::fixed) << setprecision(4);
    for (int i = 0; i < AARForThreeTypes[0].size(); i++)
    {
        cout << setiosflags(ios::right);
        cout << setw(12) << AARForThreeTypes[a-1][i] << " | ";
        cout << endl;
    }
    
    cout << "Please choose a group for CAAR, in the form of meet-1/beat-2/miss-3/" << endl;
    int b = 0;
    while (b == 0)
    {
        cin >> b;
        if (b == 1)
        {
            cout << "the CAAR for meet is" << endl;
        }
        else if (b == 2)
        {
            cout << "the CAAR for beat is" << endl;
        }
        else if (b == 3)
        {
            cout << "the CAAR for miss is" << endl;
        }
        else
        {
            cout << "wrong input, please do that again" << endl;
        }
        
    }
    for (int i = 0; i < CAARForThreeTypes[0].size(); i++)
    {
        cout << setiosflags(ios::right);
        cout << setw(12) << CAARForThreeTypes[b-1][i] << " | ";
        cout << endl;
    }
}


#endif /* calculation_hpp */
