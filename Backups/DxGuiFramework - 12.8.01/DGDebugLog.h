/*------------------------------------------------------------------------
File Name: DGDebugLog.h
Description: This file contains the DGDebugLog class, which makes a 
   debug log out of the strings given to it.
Version:
   1.0.0    6.05.2001  Created the file
------------------------------------------------------------------------*/


#ifndef DGDEBUGLOG_H
#define DGDEBUGLOG_H

class DGDebugLog
{
public:
   DGDebugLog();
   DGDebugLog(char* fileName);

   virtual ~DGDebugLog();

   void LogString(char* string);

private:
   fstream logFile;
};

#endif