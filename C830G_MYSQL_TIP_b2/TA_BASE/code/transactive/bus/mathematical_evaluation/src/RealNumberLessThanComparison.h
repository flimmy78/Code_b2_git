#ifndef M_Eval_RealNumLessThanComparison_H
#define M_Eval_RealNumLessThanComparison_H

/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/bus/mathematical_evaluation/src/RealNumberLessThanComparison.h $
  * @author:  Ross Tucker
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  * 
  * RealNumExpression represents a real number less than comparison
  */
#include <memory>

#include "bus/mathematical_evaluation/src/IBooleanExpression.h"
#include "bus/mathematical_evaluation/src/IRealNumberExpression.h"

namespace TA_Base_Bus
{
        class RealNumberLessThanComparison : public IBooleanExpression
        {
        public:
      /**
        * Constructor
        *
        * Constructs a RealNumberExpression. This object takes ownership of the 
        * leftHandSide and rightHandSide pointers. Client of this class must 
        * *not* be delete them.
        * 
        */
        RealNumberLessThanComparison(std::auto_ptr< IRealNumberExpression > leftHandSide,
                                     std::auto_ptr< IRealNumberExpression > rightHandSide);


      /**
        * Destructor
        * 
        */
        virtual ~RealNumberLessThanComparison();


        /**
         * evaluate
         *
         * Evaluates the expression and returns 
         *  "leftHandSide < rightHandSide"
         *
         */
        virtual bool evaluate() const;

        private:

        // Disable copy constructor and assignment operator.
        RealNumberLessThanComparison( const RealNumberLessThanComparison& theRealNumberLessThanComparison);
        RealNumberLessThanComparison& operator=(const RealNumberLessThanComparison&);

        std::auto_ptr< IRealNumberExpression > m_leftHandSide;
        std::auto_ptr< IRealNumberExpression > m_rightHandSide;
        };
}
#endif // M_Eval_RealNumLessThanComparison_H
