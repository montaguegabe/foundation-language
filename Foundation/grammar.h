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

namespace foundation {
    
    using namespace boost::spirit;
    using boost::phoenix::val;
    
    template <typename Iterator, typename Lexer>
    struct LanguageGrammar
    : qi::grammar<Iterator, ast::Program(), qi::in_state_skipper<Lexer> >
    {
        template <typename TokenDef>
        LanguageGrammar(TokenDef const& tok)
        : LanguageGrammar::base_type(expression)
        {
            using boost::spirit::qi::_val;
            using boost::phoenix::ref;
            
            expression =
            term
            >> *(
                 (ascii::char_('+') >> term)
                 | (ascii::char_('-') >> term)
                 );
            
            term =
            factor
            >> *(
                 (ascii::char_('*') >> factor)
                 | (ascii::char_('/') >> factor)
            );
            
            factor %=
            tok.constant[_val = _1]
            | '(' >> expression >> ')'
            | (ascii::char_('-') >> factor)
            | (ascii::char_('+') >> factor);
        }
        
        qi::rule<Iterator, ast::Program(), qi::in_state_skipper<Lexer> > expression;
        qi::rule<Iterator, ast::Program(), qi::in_state_skipper<Lexer> > term;
        qi::rule<Iterator, ast::Operand(), qi::in_state_skipper<Lexer> > factor;
    };
}

#endif /* grammar_h */
