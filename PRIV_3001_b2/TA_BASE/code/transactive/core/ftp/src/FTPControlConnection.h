#ifndef FTPCONTROLCONNECTION_H
#define FTPCONTROLCONNECTION_H
/**
 * The source code in this file is the property of 
 * Ripple Systems and is not for redistribution
 * in any form.
 *
 * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/core/ftp/src/FTPControlConnection.h $
 * @author:  Jade Welton
 * @version: $Revision: #1 $
 *
 * Last modification: $DateTime: 2018/03/14 13:51:20 $
 * Last modified by:  $Author: lim.cy $
 * 
 * Class representing an FTP control connection, by
 * which commands/command responses are passed between
 * the FTP client/server.
 *
 */

#include "core/sockets/src/TcpSocket.h"

namespace TA_Base_Core
{
	class FTPControlConnection : public TA_Base_Core::TcpSocket
	{

	public:

		/**
		 * Constructor
		 *
		 * FTPControlConnection does not currently add any new functionality to
		 * the TcpSocket class, but may do in future, to aid the addition of
		 * new features.
		 *
		 */
		FTPControlConnection( const std::string& hostAddress, const std::string& hostPort )
		: TA_Base_Core::TcpSocket( hostAddress, hostPort ) {}


		/**
		 * Destructor
		 *
		 */
		virtual ~FTPControlConnection() {}

	};
}


#endif // FTPCONTROLCONNECTION_H
