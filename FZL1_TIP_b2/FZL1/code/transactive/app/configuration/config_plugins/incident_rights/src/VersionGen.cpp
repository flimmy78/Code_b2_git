/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/GZL6_TIP/3002/transactive/app/configuration/config_plugins/incident_rights/src/VersionGen.cpp $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2012/06/12 13:35:44 $
  * Last modified by:  $Author: builder $
  *
  */
 
namespace TA_Base_Core
{
    char componentName[] = "#componentName";
	char buildVersion[] = "#buildVersion";
	char componentVersion[] = "#buildVersion";
	char buildDate[] = __DATE__" "__TIME__;
	char identString[] = "";
    int headerArraySize = 1;
    char * headerArray[] =
    {
        "#headerArray"
    };
    
    int libraryArraySize = 1;
    char * libraryArray[] =
    {
        " "
    };
    int otherArraySize = 1;
    char * otherArray[] =
    {
        " "
    };
}
