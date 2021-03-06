//
//  grammar.h
//  Foundation
//
//  Created by Gabe Montague on 12/22/16.
//  Copyright © 2016 Gabe Montague. All rights reserved.
//

#ifndef grammar_h
#define grammar_h

#include "boost.h"
#include "ast.h"
#include "tokens.h"

#define FOUNDATION_SEM_COUT(a) (std::cout << val(a) << std::endl)

namespace foundation {
    
    using namespace boost::spirit;
    using boost::phoenix::val;
    
    template <typename Iterator, typename Lexer>
    struct LanguageGrammar
    : qi::grammar<Iterator, FOUNDATION_AST_BASE_TYPE(), qi::in_state_skipper<Lexer> >
    {
        template <typename TokenDef>
        LanguageGrammar(TokenDef const& tok)
        : LanguageGrammar::base_type(block)
        {
            using qi::_val;
            using qi::lit;
            using qi::eps;
            //using boost::phoenix::ref;
            using ascii::char_;
            
            // Shortcut
            const auto asBinOpCont = qi::as<ast::BinOpContinuation>();
            
            // Most generalized definition of an expression
            expression = logicOrExpression.alias();
            
            // A block is simply an expression wrapped in curly braces (to signify deferred evaluation)
            block = '{' >> expression >> '}';
            
            // Build the definition of an expression from the most atomic level upwards
            atomicExpression %=
            tok.identifier
            | tok.constant
            | tok.string
            | '(' >> expression >> ')';
            
            // An expression with a postfix on the end
            postfixSimple %=
            char_('.') >> tok.identifier
            | token(ID_INCREMENT)
            | token(ID_DECREMENT);
            
            expressionList %= (expression % ',');
            postfixExpressionList %=
            char_('(') >> (expressionList | eps) >> ')'
            | char_('[') >> expressionList >> ']';
            
            postfix %= postfixSimple | postfixExpressionList;
            postfixExpression %= atomicExpression >> *postfix;
            
            // An expression with a unary operator
            unaryOperator %=
            char_('!')
            | char_('~')
            | char_('+')
            | char_('-')
            | token(ID_INCREMENT)
            | token(ID_DECREMENT);
            unaryExpression %= *unaryOperator >> postfixExpression;
            // TODO: sizeof? pointers?
            
            // Term, sum, shifting expressions
            multiplicativeExpression %= unaryExpression >> *asBinOpCont[(char_('*') | char_('/') | char_('%')) >> unaryExpression];
            additiveExpression %= multiplicativeExpression >> *asBinOpCont[(char_('+') | char_('-')) >> multiplicativeExpression];
            shiftExpression %= additiveExpression >> *asBinOpCont[(token(ID_SHIFT_LEFT) | token(ID_SHIFT_RIGHT)) >> additiveExpression];
            
            // Logical combination of expressions
            relationalExpression %= shiftExpression >> *asBinOpCont[(token(ID_LEQ) | token(ID_GEQ) | '<' | '>') >> shiftExpression];
            equalityExpression %= relationalExpression >> *asBinOpCont[(token(ID_EQUAL) | token(ID_NOT_EQUAL)) >> relationalExpression];
            andExpression %= equalityExpression >> *asBinOpCont[char_('&') >> equalityExpression];
            xorExpression %= andExpression >> *asBinOpCont[char_('^') >> andExpression];
            orExpression %= xorExpression >> *asBinOpCont[char_('|') >> xorExpression];

            logicAndExpression %= orExpression >> *asBinOpCont[token(ID_AND) >> orExpression];
            logicOrExpression %= logicAndExpression >> *asBinOpCont[token(ID_OR) >> logicAndExpression];
            conditionalExpression %= logicOrExpression >> -('?' >> expression >> ':' >> conditionalExpression);
            
        }
        
        // Rule definitions
        qi::rule<Iterator, FOUNDATION_AST_BASE_TYPE(), qi::in_state_skipper<Lexer> > block;
        qi::rule<Iterator, ast::AtomicExpression(), qi::in_state_skipper<Lexer> > atomicExpression;
        qi::rule<Iterator, ast::ExpressionList(), qi::in_state_skipper<Lexer> > expressionList;
        qi::rule<Iterator, ast::PostfixSimple(), qi::in_state_skipper<Lexer> > postfixSimple;
        qi::rule<Iterator, ast::PostfixExpressionList(), qi::in_state_skipper<Lexer> > postfixExpressionList;
        qi::rule<Iterator, ast::Postfix(), qi::in_state_skipper<Lexer> > postfix;
        qi::rule<Iterator, ast::PostfixExpression(), qi::in_state_skipper<Lexer> > postfixExpression;
        qi::rule<Iterator, std::string(), qi::in_state_skipper<Lexer> > unaryOperator;
        qi::rule<Iterator, ast::UnaryExpression(), qi::in_state_skipper<Lexer> > unaryExpression;
        qi::rule<Iterator, ast::BinOp(), qi::in_state_skipper<Lexer> > multiplicativeExpression, additiveExpression, shiftExpression, relationalExpression, equalityExpression, andExpression, xorExpression, orExpression, logicAndExpression, logicOrExpression;
        qi::rule<Iterator,  qi::in_state_skipper<Lexer> > conditionalExpression;
        qi::rule<Iterator, FOUNDATION_AST_EXPRESSION_TYPE(), qi::in_state_skipper<Lexer> > expression;
    };
}

#endif /* grammar_h */
