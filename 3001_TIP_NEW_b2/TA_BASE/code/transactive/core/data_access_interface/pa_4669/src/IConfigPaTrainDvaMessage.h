/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/data_access_interface/pa_4669/src/IConfigPaTrainDvaMessage.h $
  * @author Jade Lee
  * @version $Revision: #2 $
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by: $Author: haijun.li $
  * 
  * IConfigPaTrainDvaMessage - This is the interface supported by objects that allow configuration of
  * PaTrainDvaMessages. It provides methods for retrieving, settings, and writing data for an PaTrainDvaMessage object.
  * The set methods in this interface do not set the values in the database
  * straight away. They only set the values in the object after validating that
  * they are correct.
  */

#if !defined(IConfigPaTrainDvaMessage_9E7AE6B0_D600_4de9_9290_A8480311C649__INCLUDED_)
#define IConfigPaTrainDvaMessage_9E7AE6B0_D600_4de9_9290_A8480311C649__INCLUDED_

#include <string>

#include "core/data_access_interface/src/IConfigItem.h"
#include "core/data_access_interface/pa_4669/src/IPaTrainDvaMessage.h"

namespace TA_Base_Core
{

    class IConfigPaTrainDvaMessage : public virtual TA_Base_Core::IConfigItem, public virtual IPaTrainDvaMessage
    {

    public:

        virtual ~IConfigPaTrainDvaMessage() {};

        virtual void setLabel(const std::string& label) =0;


        /**
         * getDateCreated
         *
         * Returns the date created for this PaTrainDvaMessage
         *
         * @return The date created for this PaTrainDvaMessage as a time_t.
         *
         * @exception DatabaseException A DatabaseException will be thrown if there is a
         *            problem establishing a connection with the database, or if an
         *            error is encountered while retrieving data.
         * @exception DataException A DataException will be thrown if the data cannot be 
         *            converted to the required format (e.g. ACCESSKEY should be an 
         *            unsigned long), or if the wrong ammount of data is retrieved, or if the
         *            the entity key is invalid (and this is not a new entity).
         */
        virtual time_t getDateCreated() =0;


        /**
         * getDateModified
         *
         * Returns the date modified for this PaTrainDvaMessage.
         *
         * @return The date modified for this PaTrainDvaMessage as a time_t.
         *
         * @exception DatabaseException A DatabaseException will be thrown if there is a
         *            problem establishing a connection with the database, or if an
         *            error is encountered while retrieving data.
         * @exception DataException A DataException will be thrown if the data cannot be 
         *            converted to the required format (e.g. ACCESSKEY should be an 
         *            unsigned long), or if the wrong ammount of data is retrieved, or if the
         *            the entity key is invalid (and this is not a new entity).
         */
        virtual time_t getDateModified() =0;

        
        
        /**
         * deleteThisObject
         *
         * Removes this PaTrainDvaMessage from the database. 
         * The calling application MUST then delete this PaTrainDvaMessage object, as it makes no sense
         * to keep it any longer.
         *
         * @exception DatabaseException A DatabaseException will be thrown if there is a 
         *            problem writing the data to the database.
         *
         * pre: Either - this PaTrainDvaMessage was initially loaded from the database
         *      OR     - writePaTrainDvaMessageData() has already been called
         *      This PaTrainDvaMessage has not been deleted
         */
        virtual void deleteThisObject(bool cascade=false) = 0;

        /**
         * setKey
         *
         * Updates the key for this object, responsibility of client to
         *  ensure the key is unique
         *
         */
        virtual void    setKey(unsigned long key) = 0;

        /**
         * getModifiedKey
         *
         * @return the modified (if applicable) primary key, but if the
         *          key hasn't been modified, returns the actual primary key
         *
         * @see setKey
         */
        virtual unsigned long getModifiedKey() = 0;

    };
} //close namespace TA_Base_Core
#endif // !defined(IConfigPaTrainDvaMessage_9E7AE6B0_D600_4de9_9290_A8480311C649__INCLUDED_)
