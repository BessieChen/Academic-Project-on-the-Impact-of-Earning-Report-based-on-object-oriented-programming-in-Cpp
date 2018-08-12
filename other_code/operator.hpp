//
//  operator.hpp
//  input
//
//  Created by 陈贝茜 on 2017/11/30.
//  Copyright © 2017年 陈贝茜. All rights reserved.
//

#ifndef operator_hpp
#define operator_hpp

#include <stdio.h>
#include <vector>

using namespace std;

typedef vector<double> Vector;

Vector operator+(const Vector& A, const Vector& B);
Vector operator-(const Vector& A, const Vector& B);
Vector operator/(const Vector& A, const double& B);

Vector operator+(const Vector& A, const Vector& B)
{
    int a = A.size();
    Vector C(a);
    for (int i = 0; i<a; i++)
        C[i] = A[i]+B[i];
    
    return C;
}

Vector operator-(const Vector& A, const Vector& B)
{
    int a = A.size();
    Vector C(a);
    for (int i = 0; i<a; i++)
        C[i] = A[i]-B[i];
    
    return C;
}

Vector operator/(const Vector& A, const double& B)
{
    int a = A.size();
    Vector C(a);
    for (int i = 0; i<a; i++)
        C[i] = A[i]/B;
    
    return C;
}


#endif /* operator_hpp */
