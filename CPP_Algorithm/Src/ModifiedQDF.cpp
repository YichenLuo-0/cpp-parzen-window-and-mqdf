/********************************************************************
 * @File name:		ParzenWindow.cpp
 * @Author:			Yichen Luo
 * @Version:		1.0
 * @Date:			2022-4-26
 * @Description:	Implementation MQDF algorithm
 ********************************************************************/

//-------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------
#include "ModifiedQDF.h"

#include<cmath>


//-------------------------------------------------------------------
// Function implementation
//-------------------------------------------------------------------

/********************************************************************
 * @name	ModifiedQDF
 * @brief	The constructor
 * @param	dataset - Input data set
 * */
ModifiedQDF::ModifiedQDF(vector<DataStruct>* dataset) :Algorithm(dataset)
{
}


/********************************************************************
 * @name	train
 * @brief	Training the dataset using MQDF
 * @param	none
 * @return	none
 * */
void ModifiedQDF::train()
{
	// Calculate the mean
	Matrix sum[3] = { Matrix(1,4), Matrix(1,4), Matrix(1,4) };
	for (const DataStruct data : datasetSplit[currentTrainDataset])
	{
		for (int i = 0; i < 4; i++)
		{
			double current = sum[data.classIndex - 1].get(0, i);
			sum[data.classIndex - 1].set(0, i, current + data.data[0]);
		}
		number[data.classIndex - 1]++;
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mean[i].set(0, j, sum[i].get(0, j) / number[i]);
		}
	}
	// Calculate the covariance matrix
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				cov[i].set(j, k, calculateCov(i + 1, j, k));
			}
		}
	}
	cout << "Done: Train." << endl;
}


/********************************************************************
 * @name	testSingle
 * @brief	Test one data in the data set
 * @param	testData - Data to test
 * @return	Result of predict
 * */
int ModifiedQDF::testSingle(DataStruct testData) {
	double g_x[3] = { 0, 0, 0 };
	// Calculate the MQDF
	for (int i = 0; i < 3; i++)
	{
		Matrix mat1(1, 4, testData.data);
		Matrix mat2 = mat1 - mean[i];
		Matrix mat3 = mat2 * Matrix::inverse(cov[i]) * Matrix::trans(mat2);
		g_x[i] = -mat3.get(0, 0) - log(Matrix::det(cov[i]));
		if (g_x[i] < 0)
		{
			g_x[i] = -g_x[i];
		}
	}
	// The minimum is the classification
	int minIndex = 0;
	double mimValue = g_x[0];
	for (int i = 0; i < 3; i++)
	{
		if (g_x[i] < mimValue)
		{
			minIndex = i;
			mimValue = g_x[i];
		}
	}
	return minIndex + 1;
}


/********************************************************************
 * @name	calculateCov
 * @brief	Computed covariance
 * @param	indexClass - Classes that need to be evaluated
 * @param	indexX - X value
 * @param	indexY - Y value
 * @return	covariance
 * */
double ModifiedQDF::calculateCov(int indexClass, int indexX, int indexY)
{
	double sum = 0;
	for (const DataStruct data : datasetSplit[currentTrainDataset])
	{
		if (data.classIndex == indexClass)
		{
			sum += (data.data[indexX] - mean[indexClass - 1].get(0, indexX))
				* (data.data[indexY] - mean[indexClass - 1].get(0, indexY));
		}
	}
	return sum / (number[indexClass - 1] - 1);
}
