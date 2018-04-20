#ifndef M_Eval_Tokeniser_H
#define M_Eval_Tokeniser_H

/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/bus/mathematical_evaluation/src/Tokeniser.h $
  * @author:  Ross Tucker
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  * 
  * 
  */
#include "bus/mathematical_evaluation/src/Token.h"
#include "boost/shared_ptr.hpp"

#include <vector>
#include <map>

namespace TA_Base_Bus
{
    class Tokeniser
    {
    public:

        /**
          * Constructor
          */
        Tokeniser();

        /**
          * Constructor
          */
        Tokeniser(const std::string& p_expression);

        /**
          * Destructor
          *
          * Cleans up the m_tokens member variable. This should be noted by 
          * any classes that call getTokens. That is, it is not safe to delete
          * the tokeniser until the return value from getTokens is no longer in use.
          */
        virtual ~Tokeniser();

        /**
          * setExpression
          *
          * This method sets and parses the new expression.
          *
          * @param The new expression
          *
          * @exception MathematicalEvaluationException thrown if the expression cannot be parsed
          */
        void setExpression(const std::string& p_expression);

        /**
          * getTokens
          *
          * This method returns the vector of tokens that were generated by the supplied expression.
          *
          * @return Tokens extracted from the supplied expression.
          */
        std::vector< boost::shared_ptr< TA_Base_Bus::Token > > getTokens() const;

    private:

        // Disable copy constructor and assignment operator.
        Tokeniser( const Tokeniser& theTokeniser);
        Tokeniser& operator=(const Tokeniser&);

        /**
          * parse
          *
          * This method parses the given expression and populates the m_tokens member variable
          *
          * @param      const std::string& p_expression
          *             A constant expression.
          *
          * @exception  MathematicalEvaluationException 
          *             Thrown if the expression cannot be parsed.
          */
        void parse(const std::string& p_expression);

        /**
          * extractNextOperator
          *
          * If the first element(s) in the supplied string make up an operator, a token
          * will be generated and added to the m_tokens variable.
          *
          * NOTE: This method modifies the m_tokens member variable.
          *
          * @param      const std::string& p_expression
          *             An expression from which the next operator will be extracted.
          *
          * @return     unsigned int
          *             The operator extracted.
          *
          * @exception  MathematicalEvaluationException
          *             Thrown if the expression is invalid.
          *             Caused by illegal positioning of '-' character.
          *
          */
        unsigned int extractNextOperator(const std::string& p_expression);

        /**
          * extractNextConstant
          *
          * If the first element(s) in the supplied string make up an constant, a token
          * will be generated and added to the m_tokens variable.
          *
          * NOTE: This method modifies the m_tokens member variable.
          *
          * @param      const std::string& p_expression
          *             An expression from which the next constant will be extracted.
          *
          * @return     unsigned int
          *             The constant extracted.
          *
          */
        unsigned int extractNextConstant(const std::string& p_expression);

        /**
          * extractNextNumber
          *
          * If the first element(s) in the supplied string make up a numerical value, a token
          * will be generated and added to the m_tokens variable.
          *
          * NOTE: This method modifies the m_tokens member variable.
          *
          * @param      const std::string& p_expression
          *             An expression from which the next number will be extracted.
          *
          * @return     unsigned int
          *             The number extracted.
          *
          */
        unsigned int extractNextNumber(const std::string& p_expression);

        /**
          * extractNextStringLiteral
          *
          * If the first element(s) in the supplied string is enclosed within quotes (""), a token
          * will be generated and added to the m_tokens variable.
          *
          * NOTE: This method modifies the m_tokens member variable.
          *
          * @param      const std::string& p_expression
          *             An expression from which the next string literal will be extracted.
          *
          * @return     unsigned int
          *             The string literal extracted.
          *
          * @exception  MathematicalEvaluationException
          *             Thrown if the expression is invalid.
          *             Caused by absense of \' character.
          *
          */
        unsigned int extractNextStringLiteral(const std::string& p_expression);

        /**
          * extractNextVariable
          *
          * This method will generate a variable token from the start of the expression (until
          * an operator or bracket is reached). The token will then be added to the m_tokens variable.
          *
          * NOTE: This method modifies the m_tokens member variable.
          *
          * @param      const std::string& p_expression
          *             An expression from which the next variable will be extracted.
          *
          * @return     unsigned int
          *             The variable extracted.
          *
          * @exception  MathematicalEvaluationException
          *             Thrown if the expression is invalid.
          *             Caused by absense of \' character.
          *
          */
        unsigned int extractNextVariable(const std::string& p_expression);

        /**
          * extractNextParenthesis
          *
          * If the first element(s) in the supplied string is a bracket, a token
          * will be generated and added to the m_tokens variable.
          *
          * NOTE: This method modifies the m_tokens member variable.
          *
          * @param      const std::string& p_expression
          *             An expression from which the next parenthesis will be extracted.
          *
          * @return     unsigned int
          *             The parenthesis extracted.
          *
          */
        unsigned int extractNextParenthesis(const std::string& p_expression);

        /**
          * clearTokens
          *
          * Cleans up the m_tokens member variable
          */
        void clearTokens();

        // Holds the delimited tokens from input.
        typedef boost::shared_ptr< TA_Base_Bus::Token > TokenPtr;
        std::vector< TokenPtr > m_tokens;
        unsigned int m_operatorCount;
    };
}
#endif // M_Eval_Tokeniser_H