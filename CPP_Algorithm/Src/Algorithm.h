/********************************************************************
 * @File name:		Algorithm.h
 * @Author:			Yichen Luo
 * @Version:		1.0
 * @Date:			2022-4-22
 * @Description:	Declare algorithm abstract classes
 ********************************************************************/

#pragma once

#ifndef ALGORITHM_H
#define ALGORITHM_H


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
// Constants and Typedefine
//-------------------------------------------------------------------

// Iris species 1
#define IRIS_SETOSA 1
// Iris species 2
#define IRIS_VERSICOLOR 2
// Iris species 3
#define IRIS_VIRGINICA 3
// Iris unknown species
#define IRIS_UNKNOWN 0

// circumference
const double PI = 3.1415926536;

/********************************************************************
 * @name	DataStruct
 * @brief	Data set structure
 * */
typedef struct
{
	// parameter
	double data[4];
	// species
	int classIndex;
}DataStruct;

/********************************************************************
 * @name	TestResult
 * @brief	Test result structure
 * */
typedef struct
{
	// parameter
	float data[4];
	// predict result
	int predictIndex;
	// actual result
	int actualIndex;
}TestResult;


//-------------------------------------------------------------------
// Class Declaration
//-------------------------------------------------------------------

/********************************************************************
 * @name	Algorithm
 * @brief	Abstract class. Used to perform common operations for both
 *			algorithms, such as splitting datasets. With the factory
 *			pattern, code reuse can be increased.
 * */
class Algorithm
{
//-------------------------------------------------------------------
// Member Variables
//-------------------------------------------------------------------
protected:
	// Data set variable
	vector<DataStruct>* dataset;
	// A data set divided into five pieces
	vector<DataStruct> datasetSplit[5];
	// The data set currently used as a training set
	int currentTrainDataset = 0;
	// The test results
	vector<TestResult> testResults;
	// Whether to show the execution process
	bool showProcess = false;

//-------------------------------------------------------------------
// Member Function
//-------------------------------------------------------------------
private:
	void showClass(int index);

protected:
	virtual int testSingle(DataStruct testData) = 0;

public:
	Algorithm(vector<DataStruct>* dataset);
	~Algorithm();
	void ifShowProcess(bool b);
	vector<TestResult>* getTestResult();
	void preprocessing(void);
	void setTrainDataset(int index);
	virtual void train(void) = 0;
	void test(void);
};

#endif
