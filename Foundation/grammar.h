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
            using boost::phoenix::ref;
            using ascii::char_;
            
            // A block is simply an expression wrapped in curly braces (to signify deferred evaluation)
            block =
            '{'
            >> expression
            >> '}';
            
            // Build the definition of an expression from the most atomic level upwards
            atomicExpression %=
            tok.identifier
            | tok.constant
            | tok.string
            | ('(' >> expression >> ')');
            
            // An expression with an atomic "postfix" on the end
            postfixExpression %=
            (atomicExpression | postfixExpression)
            >> (token(ID_INCREMENT) | token(ID_DECREMENT));
            
            //| (postfixExpression >> lit('(') >> ')')
            //| (postfixExpression >> lit(.) >> tok.identifier)
            
            //postfixExpressionRec = lit('[') >> postfixExpression >> lit(']')
            
            // Most generalized definition of an expression
            expression = postfixExpression;
        }
        
        qi::rule<Iterator, ast::PostfixExpression(), qi::in_state_skipper<Lexer> > block;
        qi::rule<Iterator, ast::AtomicExpression(), qi::in_state_skipper<Lexer> > atomicExpression;
        qi::rule<Iterator, ast::PostfixExpression(), qi::in_state_skipper<Lexer> > postfixExpression;
        qi::rule<Iterator, ast::PostfixExpression(), qi::in_state_skipper<Lexer> > postfixExpressionRec;
        qi::rule<Iterator, ast::PostfixExpression(), qi::in_state_skipper<Lexer> > expression;
    };
}

#endif /* grammar_h */
