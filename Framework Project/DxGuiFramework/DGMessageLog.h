/*------------------------------------------------------------------------
File Name: DGMessageLog.h
Description: This file contains the DGMessageLog class, which makes a log
   of all GUI messages
Version:
   1.0.0    5.05.2001  Created the file
------------------------------------------------------------------------*/


#ifndef DGMESSAGELOG_H
#define DGMESSAGELOG_H

class DGMessageLog
{
public:
   DGMessageLog();
   DGMessageLog(char* fileName);

   virtual ~DGMessageLog();

   void LogMessage(DGMessage* message);

private:
	std::fstream logFile;
};

#endif