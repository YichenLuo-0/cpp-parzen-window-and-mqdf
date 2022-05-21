/********************************************************************
 * @File name:		ParzenWindow.h
 * @Author:			Yichen Luo
 * @Version:		1.0
 * @Date:			2022-4-22
 * @Description:	Implement ParzenWindow algorithm
 ********************************************************************/

#pragma once

#ifndef PARZENWINDOW_H
#define PARZENWINDOW_H


//-------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------
#include "Algorithm.h"


//-------------------------------------------------------------------
// Class Declaration
//-------------------------------------------------------------------

/********************************************************************
 * @name	ParzenWindow
 * @brief	Implement ParzenWindow algorithm
 * */
class ParzenWindow : public Algorithm 
{
//-------------------------------------------------------------------
// Member Variables
//-------------------------------------------------------------------
private:
	// The number of each type in the test set
	double n_k[3] = { 0 };
	// Conditional probabilities for each of these categories
	double P_wk[3] = { 0 };
	// Hyperparameter
	double h = 1;

//-------------------------------------------------------------------
// Member Function
//-------------------------------------------------------------------
private:
	double gaussWindow(double param1, double param2, double param3, double param4);
	int testSingle(DataStruct testData);

public:
	void setH(double h);
	ParzenWindow(vector<DataStruct>* dataset);
	void train();
};

#endif