//
//  operator.hpp
//  input
//
//  Created by ??? on 2017/11/30.
//  Copyright © 2017? ???. All rights reserved.
//

#ifndef Operator_h
#define Operator_h

#include <stdio.h>
#include <vector>
#include <locale>
#include <string>

using namespace std;

typedef vector<double> Vector;
typedef vector<Vector> Matrix;

Vector operator+(const Vector& A, const Vector& B);
Vector operator-(const Vector& A, const Vector& B);
Vector operator/(const Vector& A, const double& B);
Matrix operator+(const Matrix& A, const Matrix& B);
Matrix operator-(const Matrix& A, const Matrix& B);
Matrix operator/(const Matrix& A, const double& B);

Vector operator+(const Vector& A, const Vector& B)
{
	int a = A.size();
	Vector C(a);
	for (int i = 0; i<a; i++)
		C[i] = A[i] + B[i];

	return C;
}

Vector operator-(const Vector& A, const Vector& B)
{
	int a = A.size();
	Vector C(a);
	for (int i = 0; i<a; i++)
		C[i] = A[i] - B[i];

	return C;
}

Vector operator/(const Vector& A, const double& B)
{
	int a = A.size();
	Vector C(a);
	for (int i = 0; i<a; i++)
		C[i] = A[i] / B;

	return C;
}

Matrix operator+(const Matrix& A, const Matrix& B)
{
	int a = A.size();
	Matrix C(a);
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < A[i].size(); j++)
			C[i].push_back(A[i][j] + B[i][j]);
	}
	return C;
}

Matrix operator-(const Matrix& A, const Matrix& B)
{
	int a = A.size();
	Matrix C(a);
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < A[i].size(); j++)
			C[i].push_back(A[i][j] - B[i][j]);
	}
	return C;
}

Matrix operator/(const Matrix& A, const double& B)
{
	int a = A.size();
	Matrix C(a);
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < A[i].size(); j++)
			C[i].push_back(A[i][j] / B);
	}
	return C;
}

string Upper(string str) //For menu use only
{
	string temp;
	locale loc;
	for (string::size_type i = 0; i<str.length(); i++)
		temp.push_back(toupper(str[i], loc));
	return temp;
}
#endif /* operator_hpp */
