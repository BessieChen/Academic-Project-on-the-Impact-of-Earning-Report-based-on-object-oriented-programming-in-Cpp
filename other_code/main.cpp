//
//  main.cpp
//  input
//
//  Created by 陈贝茜 on 2017/11/30.
//  Copyright © 2017年 陈贝茜. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include "stock.hpp"
#include "input.hpp"
#include "calculation.hpp"
//#include "curl.h"

using namespace std;

int main()
{
    /*string type[3] = { "Beat", "Meet", "Miss" };
     map<string, string> Beat40 = Symbol40(type[0]);
     map<string, string> Meet40 = Symbol40(type[1]);
     map<string, string> Miss40 = Symbol40(type[2]);
     
     vector<stock> Beat = reconversion(Beat40);
     vector<stock> Meet = reconversion(Meet40);
     vector<stock> Miss = reconversion(Miss40);
     
     for (int i = 0;i < Beat.size();i++)
     Beat[i].display();*/
    
    Calculation MyCal;
    
    MyCal.setupMapsForThreeTypes();
    MyCal.setupDailyARForThreeTypes();
    MyCal.CalculateAAR();
    MyCal.CalculateCAAR();
    
    bool execute = true;
    int choice;
    while (execute) {
        cout << "Menu Choice: 1, 2, 3, 4, or 5 " << endl;
        cout << "1)retrieve historical price data for all stocks" << endl;
        cout << "2)information for one stock" << endl;
        cout << "3)show AAR or CAAR for one group" << endl;
        cout << "4)show the excel graph with CAAR for all 3 groups" << endl;
        cout << "5)exit the program" << endl<<endl;
        cin >> choice;
        switch (choice)
        {
            case 1:
                MyCal.displayhistoricalprice();
                break;
            case 2:
                MyCal.displayinformation();
                break;
            case 3:
                MyCal.showAARandCAAR();
                break;
            case 4:
                MyCal.showExcelGraph();
                break;
            case 5:
                execute = false;
                break;
        }
    }
    system("pause");
    //curl_global_cleanup();
    return 0;
}
