/********************************************************************
 * @File name:		FileReader.h
 * @Author:			Yichen Luo
 * @Version:		1.0
 * @Date:			2022-4-20
 * @Description:	Declares a method for reading a file
 ********************************************************************/

#pragma once

#ifndef FILEREADER_H
#define FILEREADER_H


//-------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------
#include "Algorithm.h"

#include <string>
#include <vector>


//-------------------------------------------------------------------
// Namespace
//-------------------------------------------------------------------
using namespace std;


//-------------------------------------------------------------------
// Public function declaration
//-------------------------------------------------------------------
vector<DataStruct>* readAsDataList(string filename);

#endif
