/********************************************************************
 * @File name:		Algorithm.cpp
 * @Author:			Yichen Luo
 * @Version:		1.0
 * @Date:			2022-4-22
 * @Description:	Algorithm class method implementation
 ********************************************************************/

 //-------------------------------------------------------------------
 // Includes
 //-------------------------------------------------------------------
#include "Algorithm.h"


//-------------------------------------------------------------------
// Function implementation
//-------------------------------------------------------------------

/********************************************************************
 * @name	Algorithm
 * @brief	The constructor
 * @param	dataset - The data set passed in for training
 * */
Algorithm::Algorithm(vector<DataStruct>* dataset)
{
	this->dataset = dataset;
}


/********************************************************************
 * @name	~Algorithm
 * @brief	The destructor
 * @param	none
 * */
Algorithm::~Algorithm()
{
}


/********************************************************************
 * @name	showClass
 * @brief	Prints the class to the console
 * @param	index - Class index
 * @return	none
 * */
void Algorithm::showClass(int index)
{
	if (index == IRIS_SETOSA)
	{
		cout << "Iris-setosa" << endl;
	}
	else if (index == IRIS_VERSICOLOR)
	{
		cout << "Iris-versicolor" << endl;
	}
	else {
		cout << "Iris-virginica" << endl;
	}
}


/********************************************************************
 * @name	~Algorithm
 * @brief	Set whether to show the execution process
 * @param	b - Whether to show the execution process
 * @return	none
 * */
void Algorithm::ifShowProcess(bool b)
{
	this->showProcess = b;
}


/********************************************************************
 * @name	getTestResult
 * @brief	Get test data
 * @param	none
 * @return	Test result
 * */
vector<TestResult>* Algorithm::getTestResult()
{
	return &testResults;
}


/********************************************************************
 * @name	preprocessing
 * @brief	Used to divide the data set into five sections
 * @param	none
 * @return	none
 * */
void Algorithm::preprocessing()
{
	int dataSize = this->dataset->size();
	int spiltIndex = dataSize / 5;
	// The dataset was randomly divided into 5 parts
	while (true)
	{
		int remainingSize = this->dataset->size();
		if (remainingSize == 0)
		{
			break;
		}
		int index = rand() * remainingSize / RAND_MAX;
		DataStruct data = this->dataset->at(index);
		this->datasetSplit[(remainingSize - 1) / spiltIndex].push_back(data);
		this->dataset->erase(this->dataset->begin() + index);
	}
	// Output result
	if (showProcess)
	{
		for (DataStruct data : datasetSplit[0])
		{
			cout << "Data: " << data.data[0] << " " << data.data[1] << " " << data.data[2] << " " << data.data[3];
			cout << ", Category: ";
			showClass(data.classIndex);
		}
	}
	cout << "Done: Preprocessing." << endl;
}


/********************************************************************
 * @name	test
 * @brief	Tests all data except the training set
 * @param	none
 * @return	none
 * */
void Algorithm::test()
{
	// Test all data
	for (int i = 0; i < 5; i++)
	{
		if (i != currentTrainDataset) {
			for (int j = 0; j < datasetSplit[i].size(); j++)
			{
				DataStruct testData = datasetSplit[i].at(j);
				TestResult result;
				result.predictIndex = testSingle(testData);
				result.actualIndex = testData.classIndex;
				result.data[0] = testData.data[0];
				result.data[1] = testData.data[1];
				result.data[2] = testData.data[2];
				result.data[3] = testData.data[3];
				testResults.push_back(result);
				if (showProcess)
				{
					cout << "predict: ";
					showClass(result.predictIndex);
					cout << "actual: ";
					showClass(result.actualIndex);
					cout << "____________________________________ " << endl;
				}
			}
		}
	}
	cout << "Done: Test." << endl;
}


/********************************************************************
 * @name	setTrainDataset
 * @brief	Select a section as the training set
 * @param	index - The section index that selected as train set
 * @return	none
 * */
void Algorithm::setTrainDataset(int index)
{
	this->currentTrainDataset = index;
}
