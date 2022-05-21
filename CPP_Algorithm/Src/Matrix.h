/********************************************************************
 * @File name:		Matrix.h
 * @Author:			Yichen Luo
 * @Version:		1.0
 * @Date:			2022-4-25
 * @Description:	Declare matrix class
 ********************************************************************/

#pragma once

#ifndef MATRIX_H
#define MATRIX_H


 //-------------------------------------------------------------------
 // Includes
 //-------------------------------------------------------------------
#include <iostream>
#include <vector>


//-------------------------------------------------------------------
// Namespace
//-------------------------------------------------------------------
using namespace std;


//-------------------------------------------------------------------
// Class Declaration
//-------------------------------------------------------------------

/********************************************************************
 * @name	Matrix
 * @brief	Used for matrix operations.
 * */
class Matrix
{
//-------------------------------------------------------------------
// Member Variables
//-------------------------------------------------------------------
private:
	// Matrix columns
	int row = 0;
	// Matrix columns
	int column = 0;
	// Vectors used to store matrices
	vector<vector<double>> mat;

//-------------------------------------------------------------------
// Member Function
//-------------------------------------------------------------------
public:
	Matrix(int row, int column);
	Matrix(int row, int column, double* mat);
	~Matrix();
	void print();
	double get(int row, int column);
	void set(int row, int column, double value);
	Matrix operator+(const Matrix B);
	Matrix operator-(const Matrix B);
	Matrix operator*(const Matrix B);
	Matrix operator*(const double B);
	static Matrix cofactor(const Matrix matrix, const int row, const int column);
	static Matrix trans(const Matrix matrix);
	static Matrix inverse(const Matrix matrix);
	static double det(const Matrix matrix);
};

#endif