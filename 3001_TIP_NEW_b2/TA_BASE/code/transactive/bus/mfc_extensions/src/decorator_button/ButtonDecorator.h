/**
 * The source code in this file is the property of 
 * Ripple Systems and is not for redistribution
 * in any form.
 *
 * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/bus/mfc_extensions/src/decorator_button/ButtonDecorator.h $
 * @author:  
 * @version: $Revision: #2 $
 *
 * Last modification: $DateTime: 2012/02/06 16:15:14 $
 * Last modified by:  $Author: haijun.li $
 * 
 */

#if !defined(ButtonDecorator_6E84EB6A_BDBD_49c4_99E0_622CA06484B4__INCLUDED_)
#define ButtonDecorator_6E84EB6A_BDBD_49c4_99E0_622CA06484B4__INCLUDED_

#include "bus/mfc_extensions/src/decorator_button/AbstractDecoratorButton.h"

namespace TA_Base_Bus
{
    class AFX_EXT_CLASS ButtonDecorator : public AbstractDecoratorButton 
    {

    public:
	    /**
	     * @param pcomponent
         *        the parent component of this decorator
	     * 
	     */
	    ButtonDecorator(AbstractDecoratorButton* pcomponent);

	    virtual ~ButtonDecorator();

	    virtual void Draw(LPDRAWITEMSTRUCT lpDrawItemStruct);

	    virtual void setFinalDecorator(AbstractDecoratorButton* pFinalDec);

    protected:
	    /**
	     * Traverses the chain of decorators and delete each one in the sequence. The
	     * concrete component must not be deleted, thus default for the method will do
	     * nothing, overload in the decorator's parent class.
	     */
	    virtual void deleteTree();

	    AbstractDecoratorButton* m_pcomponent;

    private:
        // disabled methods
	    ButtonDecorator();

    };
};

#endif // !defined(ButtonDecorator_6E84EB6A_BDBD_49c4_99E0_622CA06484B4__INCLUDED_)
