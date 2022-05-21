/********************************************************************
 * @File name:		ParzenWindow.cpp
 * @Author:			Yichen Luo
 * @Version:		1.0
 * @Date:			2022-4-24
 * @Description:	Implementation Parzen Window algorithm
 ********************************************************************/

//-------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------
#include "ParzenWindow.h"

#include <math.h>


//-------------------------------------------------------------------
// Function implementation
//-------------------------------------------------------------------

/********************************************************************
 * @name	ParzenWindow
 * @brief	The constructor
 * @param	dataset - Input data set
 * */
ParzenWindow::ParzenWindow(vector<DataStruct>* dataset) : Algorithm(dataset)
{
}


/********************************************************************
 * @name	train
 * @brief	Training data set
 * @param	none
 * @return	none
 * */
void ParzenWindow::train()
{
	int n_total = datasetSplit[currentTrainDataset].size();
	for (const DataStruct data : datasetSplit[currentTrainDataset])
	{
		n_k[data.classIndex - 1]++;
	}
	// Calculate the mean
	P_wk[0] = n_k[0] / n_total;
	P_wk[1] = n_k[1] / n_total;
	P_wk[2] = n_k[2] / n_total;
	cout << "Done: Train." << endl;
}

/********************************************************************
 * @name	testSingle
 * @brief	Test one data in the data set
 * @param	testData - Data to test
 * @return	Result of predict
 * */
int ParzenWindow::testSingle(DataStruct testData)
{
	double h_d = pow(h, 4);
	double sum[3] = { 0 ,0, 0 };
	// Computational Gaussian window
	for (const DataStruct trainData : datasetSplit[currentTrainDataset])
	{
		double u1 = (testData.data[0] - trainData.data[0]) / h;
		double u2 = (testData.data[1] - trainData.data[1]) / h;
		double u3 = (testData.data[2] - trainData.data[2]) / h;
		double u4 = (testData.data[3] - trainData.data[3]) / h;
		sum[trainData.classIndex - 1] += (gaussWindow(u1, u2, u3, u4) / h_d);
	}
	double result[3] = { 0, 0, 0 };
	result[0] = P_wk[0] * (sum[0] / n_k[0]);
	result[1] = P_wk[1] * (sum[1] / n_k[1]);
	result[2] = P_wk[2] * (sum[2] / n_k[2]);
	// The maximum value is classified
	int maxIndex = 0;
	double maxValue = 0;
	for (int i = 0; i < 3; i++)
	{
		if (result[i] > maxValue)
		{
			maxIndex = i;
			maxValue = result[i];
		}
	}
	return maxIndex + 1;
}


/********************************************************************
 * @name	gaussWindow
 * @brief	Implement gaussian window function
 * @param	param1 - The feature vectors
 * @param	param2 - The feature vectors
 * @param	param3 - The feature vectors
 * @param	param4 - The feature vectors
 * @return	Result of gauss window
 * */
double ParzenWindow::gaussWindow(double param1, double param2, double param3, double param4)
{
	double i = pow(2 * PI, 2);
	double j = exp(-(pow(param1, 2) + pow(param2, 2) + pow(param3, 2) + pow(param4, 2)) / 2);
	return j / i;
}


/********************************************************************
 * @name	setH
 * @brief	Setting hyperparameter
 * @param	h - hyperparameter
 * @return	none
 * */
void ParzenWindow::setH(double h)
{
	this->h = h;
}
