/*------------------------------------------------------------------------
File Name: DGDebugLog.cpp
Description: This file contains the implementation of the DGDebugLog 
   class, which makes a debug log out of the strings given to it.
Version:
   1.0.0    6.05.2001  Created the file
------------------------------------------------------------------------*/

#include "DxGuiFramework.h"

DGDebugLog::DGDebugLog()
{
   logFile.open("DGDebugLog.txt", std::ios::out);
}

DGDebugLog::DGDebugLog(char* fileName)
{
   logFile.open(fileName, std::ios::out);
}

DGDebugLog::~DGDebugLog()
{
   logFile.close();
}

void DGDebugLog::LogString(char* string)
{
   logFile << string;
}
