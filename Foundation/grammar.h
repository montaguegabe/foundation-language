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
    : qi::grammar<Iterator, ast::OperationList(), qi::in_state_skipper<Lexer> >
    {
        template <typename TokenDef>
        LanguageGrammar(TokenDef const& tok)
        : LanguageGrammar::base_type(program)
        {
            using boost::spirit::qi::_val;
            using boost::spirit::qi::lit;
            using boost::phoenix::ref;
            
            program =
            lit('{')
            >> mathExpression
            >> lit('}');
            
            /*assignmentExpression %= tok.identifier
            >> +(ascii::char_('=') >> mathExpression);*/
            
            mathExpression =
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
            | '(' >> mathExpression >> ')'
            | (ascii::char_('-') >> factor)
            | (ascii::char_('+') >> factor);
            
            /*

            program
            = block;

            block
            = qi::lit('{')
            >> *statement
            >> qi::lit('}');

            statement
            = assignment
            | if_stmt
            | while_stmt;

            assignment
            = (tok.identifier >> '=' >> expression >> ';');

            if_stmt
            = (token(ID_IF) >> '(' >> expression >> ')' >> block
            >> -(token(ID_ELSE) >> block));

            while_stmt = (token(ID_WHILE) >> '(' >> expression >> ')' >> block);
            
            */
        }
        
        qi::rule<Iterator, ast::OperationList(), qi::in_state_skipper<Lexer> > program;
        //qi::rule<Iterator, ast::Assignment(), qi::in_state_skipper<Lexer> > assignmentExpression;
        qi::rule<Iterator, ast::OperationList(), qi::in_state_skipper<Lexer> > mathExpression;
        qi::rule<Iterator, ast::OperationList(), qi::in_state_skipper<Lexer> > term;
        qi::rule<Iterator, ast::Operand(), qi::in_state_skipper<Lexer> > factor;
        
    };
}

#endif /* grammar_h */
