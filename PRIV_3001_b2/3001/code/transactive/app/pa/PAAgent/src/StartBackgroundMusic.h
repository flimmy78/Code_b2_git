/*
 * The source code in this file is the property of
 * Ripple Systems and is not for redistribution
 * in any form.
 *
 * Source : $File: //depot/PRIV_3001/3001/transactive/app/pa/PAAgent/src/StartBackgroundMusic.h $
 * @author  J. Dalin
 * @version $Revision: #1 $
 * Last modification : $DateTime: 2018/03/14 13:51:20 $
 * Last modified by : $Author: lim.cy $
 *
 * 
 */

#ifndef StartBackgroundMusic_H
#define StartBackgroundMusic_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "app/pa/PAAgent/src/PasTransaction.h"

namespace TA_IRS_App
{

class StartBackgroundMusic : public PasTransaction
{
public:
    StartBackgroundMusic( const bool bAtOcc, ITransactionOwner* pOwner );
    virtual ~StartBackgroundMusic();

    void setPasZoneKeys( const std::vector<unsigned long>& vecPasZoneKeys );
    void setSourceNumber( const unsigned short usSourceNumber);

private:
    StartBackgroundMusic();
	StartBackgroundMusic( const StartBackgroundMusic& );
	const StartBackgroundMusic& operator=( const StartBackgroundMusic& );

    virtual int executeOccImp( PasConnectionAgency& refConnection );
    virtual int executeStnImp( PasConnectionAgency& refConnection );

private:
    std::vector<unsigned long> m_vecPasZoneKeys;
    unsigned short m_usSourceNumber;
};

} // namespace TA_IRS_App

#endif // StartBackgroundMusic_H
