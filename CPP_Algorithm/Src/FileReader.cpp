/********************************************************************
 * @File name:		FileReader.cpp
 * @Author:			Yichen Luo
 * @Version:		1.0
 * @Date:			2022-4-20
 * @Description:	Use to read the dataset and load it as a list
 ********************************************************************/

 //-------------------------------------------------------------------
 // Includes
 //-------------------------------------------------------------------
#include "FileReader.h"

#include <fstream>
#include <iostream>


//-------------------------------------------------------------------
// Private function declaration
//-------------------------------------------------------------------
vector<string>* readFile(string filename);
vector<string> stringSplit(const string& str, char delim);


//-------------------------------------------------------------------
// Function implementation
//-------------------------------------------------------------------

/********************************************************************
 * @name	readAsDataList
 * @brief	Use to read the data set and load it as a vector
 * @param	filename - Name and path of the file to be read
 * @return	Pointer of a vector of the dataset
 * */
vector<DataStruct>* readAsDataList(string filename)
{
	vector<string>* datasetOld = readFile(filename);
	vector<DataStruct>* datasetNew = new vector<DataStruct>;
	for (string data : *datasetOld)
	{
		vector<string> dataSplit = stringSplit(data, ',');
		DataStruct dataStruct;
		dataStruct.data[0] = stof(dataSplit.at(0));
		dataStruct.data[1] = stof(dataSplit.at(1));
		dataStruct.data[2] = stof(dataSplit.at(2));
		dataStruct.data[3] = stof(dataSplit.at(3));
		if (dataSplit.at(4) == "Iris-setosa")
		{
			dataStruct.classIndex = IRIS_SETOSA;
		}
		else if (dataSplit.at(4) == "Iris-versicolor")
		{
			dataStruct.classIndex = IRIS_VERSICOLOR;
		}
		else if (dataSplit.at(4) == "Iris-virginica")
		{
			dataStruct.classIndex = IRIS_VIRGINICA;
		}
		else
		{
			dataStruct.classIndex = IRIS_UNKNOWN;
		}
		datasetNew->push_back(dataStruct);
	}
	delete datasetOld;
	return datasetNew;
}


/********************************************************************
 * @name	readFile
 * @brief	Use to read the data set and load it as a vector
 * @param	filename - Name and path of the file to be read
 * @return	Pointer of a vector of the dataset
 * */
vector<string>* readFile(string filename)
{
	// Open the file read stream
	fstream fst;
	fst.open(filename, ios::in);
	// If opening fails, print it in the console
	if (!fst.is_open())
	{
		cout << "File opening failure!\n";
		return nullptr;
	}
	// Read the data line by line
	vector<string>* readBuff = new vector<string>;
	string line;
	while (getline(fst, line))
	{
		readBuff->push_back(line);
	}
	// Close the file read stream
	fst.close();
	return readBuff;
}


/********************************************************************
 * @name	stringSplit
 * @brief	Use to read the data set and load it as a list
 * @param	str - String to be split
 * @param	delim - Split by this character
 * @return	Pointer of a vector of the dataset
 * */
vector<string> stringSplit(const string& str, char delim)
{
	size_t previous = 0;
	size_t current = str.find(delim);
	vector<string> elems;
	while (current != string::npos)
	{
		if (current > previous)
		{
			elems.push_back(str.substr(previous, current - previous));
		}
		previous = current + 1;
		current = str.find(delim, previous);
	}
	if (previous != str.size())
	{
		elems.push_back(str.substr(previous));
	}
	return elems;
}