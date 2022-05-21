/********************************************************************
 * @File name:		ModifiedQDF.h
 * @Author:			Yichen Luo
 * @Version:		1.0
 * @Date:			2022-4-24
 * @Description:	Implement MQDF algorithm
 ********************************************************************/

#pragma once

#ifndef MQDF_H
#define MQDF_H


 //-------------------------------------------------------------------
 // Includes
 //-------------------------------------------------------------------
#include "Algorithm.h"
#include "Matrix.h"


//-------------------------------------------------------------------
// Class Declaration
//-------------------------------------------------------------------

/********************************************************************
 * @name	ModifiedQDF
 * @brief	Implement MQDF algorithm
 * */
class ModifiedQDF : public Algorithm
{
//-------------------------------------------------------------------
// Member Variables
//-------------------------------------------------------------------
private:
	// The number of each type in the test set
	int number[3] = { 0 };
	// The mean matrix for each category in the test set
	Matrix mean[3] = { Matrix(1,4), Matrix(1,4), Matrix(1,4) };
	// Covariance matrix for each class in the test set
	Matrix cov[3] = { Matrix(4,4), Matrix(4,4), Matrix(4,4) };

//-------------------------------------------------------------------
// Member Function
//-------------------------------------------------------------------
private:
	double calculateCov(int indexClass, int indexX, int indexY);
	int testSingle(DataStruct testData);

public:
	ModifiedQDF(vector<DataStruct>* dataset);
	void train();
};

#endif