/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/3001/transactive/app/history/traffic_historian/src/DBConnection.h $
  * @author:  Ripple
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  */
// DBConnection.h: Definition of the DBConnection class
// This is a singleton class that retrieves the database connection string
// from the process manager.
//
// Author: Craig Grant 20/02/2001

#ifndef HISTORIAN_DBCONNECTION_H_INCLUDED
#define HISTORIAN_DBCONNECTION_H_INCLUDED

#include <ManagedProcess.h>

// A singleton class that retrieves the database connection string
// from the process manager.
class DBConnection
{
public:
	static DBConnection* Instance();

	~DBConnection();

	const char* GetDBName() const { return m_DBName.c_str(); }
	const char* GetUsername() const { return m_Username.c_str(); }
	const char* GetPassword() const { return m_Password.c_str(); }

	// Test the database connection, return TRUE if OK.
	bool TestConnection();

protected:
	DBConnection();

private:
	std::string m_DBName;
	std::string m_Username;
	std::string m_Password;
};

#endif  // HISTORIAN_DBCONNECTION_H_INCLUDED
