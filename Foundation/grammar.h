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
            using boost::spirit::qi::_val;
            using boost::spirit::qi::lit;
            using boost::spirit::token;
            using boost::phoenix::ref;
            
            // A block is simply an expression wrapped in curly braces (to signify deferred evaluation)
            block =
            '{'
            >> expression
            >> '}';
            
            // Build the definition of an expression from the most atomic level upwards
            atomicExpression %=
            tok.identifier
            | tok.constant
            | ('(' >> expression >> ',' >> expression >> ')');
            
            // An expression with an atomic "postfix" on the end
            /*postfixExpression =
            atomicExpression
            >> (
                lit('(') >> lit(')')
                | lit('.') >> tok.identifier
                | token(ID_INCREMENT)
                | token(ID_DECREMENT)
            );*/
            
            // Most generalized definition of an expression
            expression = atomicExpression;
        }
        
        qi::rule<Iterator, ast::AtomicExpression(), qi::in_state_skipper<Lexer> > block;
        qi::rule<Iterator, ast::AtomicExpression(), qi::in_state_skipper<Lexer> > atomicExpression;
        qi::rule<Iterator, ast::AtomicExpression(), qi::in_state_skipper<Lexer> > expression;
    };
}

#endif /* grammar_h */
