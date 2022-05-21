/********************************************************************
 * @File name:		Controller.cpp
 * @Author:			Yichen Luo
 * @Version:		1.0
 * @Date:			2022-4-20
 * @Description:	Used to control the entire system. Contains the
 *					main function, where the program begins and ends.
 ********************************************************************/

 //-------------------------------------------------------------------
 // Includes
 //-------------------------------------------------------------------
#include "Controller.h"
#include "FileReader.h"
#include "ParzenWindow.h"
#include "ModifiedQDF.h"
#include "Matrix.h"

#include <iostream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#include <mysql.h>

//-------------------------------------------------------------------
// Namespace
//-------------------------------------------------------------------
using namespace std;


//-------------------------------------------------------------------
// Global Function
//-------------------------------------------------------------------
bool connectDatabase(MYSQL* mysql, const char* serveIp, const char* uid,
	const char* pwd, const char* databaseName);

bool storeResult(MYSQL* mysql, TestResult result, string table);


//-------------------------------------------------------------------
// Function implementation
//-------------------------------------------------------------------

/********************************************************************
 * @name	main
 * @brief	The program starts and ends here
 * @param	none
 * @return	none
 * */
int main()
{
	cout << "Start operation!" << endl;
	// Load data set
	vector<DataStruct>* dataset = readAsDataList("Dataset/iris.data");
	// Gets the program start time
	DWORD start_time = GetTickCount();

	// Enter the algorithm you want to test
	cout << "Enter 1 to run Parzen Window and 2 to run MQDF:";
	int i;
	cin >> i;
	Algorithm* algorithm;
	if (i == 1)
	{
		algorithm = new ParzenWindow(dataset);
	}
	else
	{
		algorithm = new ModifiedQDF(dataset);
	}
	algorithm->ifShowProcess(false);

	// Training data set and test
	algorithm->preprocessing();
	for (int i = 0; i < 5; i++)
	{
		cout << endl << "--------round " << i + 1 << "--------" << endl;
		algorithm->setTrainDataset(i);
		algorithm->train();
		algorithm->test();
	}
	vector<TestResult>* results = algorithm->getTestResult();
	double correct = 0;
	for (TestResult result : *results)
	{
		if (result.actualIndex == result.predictIndex)
		{
			correct++;
		}
	}
	double rate = correct / results->size();
	cout << endl << "Classification accuracy: " << rate * 100 << "%" << endl;

	// Get the program end time
	DWORD end_time = GetTickCount();
	std::cout << "The run time is " << (end_time - start_time) << " ms" << std::endl;

	// Initialize the database connection
	MYSQL* mysql = mysql_init(NULL);
	// Connecting to the database
	connectDatabase(mysql, SERVER_IP, UID, PWD, DATABASE);
	// Store test results in a database
	for (TestResult result : *results)
	{
		//storeResult(mysql, result, "result_mqdf");
	}
	cout << "Save test results successful!" << endl;
}


/********************************************************************
 * @name	connectDatabase
 * @brief	Connect the mysql
 * @param	mysql - MySQL object
 * @param	serveIp - The database IP
 * @param	uid - The database user ID
 * @param	pwd - The database user password
 * @param	databaseName - Database name
 * @return	Whether the connection is successful
 * */
bool connectDatabase(MYSQL* mysql, const char* serveIp, const char* uid,
	const char* pwd, const char* databaseName)
{
	// Connecting to the database
	if (!mysql_real_connect(mysql, serveIp, uid, pwd, databaseName, 0, NULL, 0))
	{
		cout << "Mysql connection error!" << endl;
		return false;
	}
	else
	{
		char value = 1;
		mysql_options(mysql, MYSQL_OPT_RECONNECT, &value);
		mysql_query(mysql, "SET NAMES GB2312");
		cout << "Mysql connection successful!" << endl;
		return true;
	}
}

/********************************************************************
 * @name	storeResult
 * @brief	Store data in a database
 * @param	mysql - MySQL object
 * @param	result - Test result
 * @param	table - Tables that need to be stored
 * @return	Whether the store is successful
 * */
bool storeResult(MYSQL* mysql, TestResult result, string table)
{
	// Format MySQL statement
	string head[6];
	head[0] = "val1";
	head[1] = "val2";
	head[2] = "val3";
	head[3] = "val4";
	head[4] = "predict";
	head[5] = "actual";
	char var1[5];
	char var2[5];
	char var3[5];
	char var4[5];
	char predict[2];
	char actual[2];
	sprintf(var1, "%2.2f", result.data[0]);
	sprintf(var2, "%2.2f", result.data[1]);
	sprintf(var3, "%2.2f", result.data[2]);
	sprintf(var4, "%2.2f", result.data[3]);
	sprintf(predict, "%d", result.predictIndex);
	sprintf(actual, "%d", result.actualIndex);
	string value[6];
	value[0] = var1;
	value[1] = var2;
	value[2] = var3;
	value[3] = var4;
	value[4] = predict;
	value[5] = actual;
	const string insert = "INSERT INTO " + table + "(" + head[0] + ", " + head[1] + ", " + head[2] + ", " +
		head[3] + ", " + head[4] + ", " + head[5] +
		") VALUES (" + value[0] + ", " + value[1] + ", " + value[2] + ", " +
		value[3] + ", " + value[4] + ", " + value[5] + ")";
	// Database entry
	if (mysql_query(mysql, insert.c_str()) == 1)
	{
		return false;
	}
	return true;
}