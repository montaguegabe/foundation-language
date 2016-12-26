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

namespace foundation {
    
    using namespace boost::spirit;
    using boost::phoenix::val;
    
    template <typename Iterator, typename Lexer>
    struct LanguageGrammar
    : qi::grammar<Iterator, unsigned int(), qi::in_state_skipper<Lexer> >
    {
        template <typename TokenDef>
        LanguageGrammar(TokenDef const& tok)
        : LanguageGrammar::base_type(program)
        {
            using boost::spirit::_val;
            using qi::eps;
            using boost::phoenix::ref;
            
            program = tok.constant[_val = _1];
            
            /*program
            = +block;
            
            block
            = qi::lit('{')
            >> *statement
            >> qi::lit('}');
            
            statement
            = assignment
            | if_stmt
            | while_stmt;
            
            assignment
            = (tok.identifier >> '=' >> expression >> ';')
            [
                std::cout << val("assignment statement to: ")
                << _1 << "\n"
            ];
            
            if_stmt
            =   (   token(ID_IF) >> '(' >> expression >> ')' >> block
                 >> -(token(ID_ELSE) >> block)
                 )
            [
             std::cout << val("if expression: ")
             << _2 << "\n"
             ]
            ;
            
            while_stmt
            =   (token(ID_WHILE) >> '(' >> expression >> ')' >> block)
            [
             std::cout << val("while expression: ")
             << _2 << "\n"
             ]
            ;
            
            //  since expression has a variant return type accommodating for
            //  std::string and unsigned integer, both possible values may be
            //  returned to the calling rule
            expression
            =   tok.identifier [ _val = _1 ]
            |   tok.constant   [ _val = _1 ]
            ;*/
        }
        
        typedef boost::variant<unsigned int, std::string> expression_type;
        
        qi::rule<Iterator, unsigned int(), qi::in_state_skipper<Lexer> > program, block, statement;
        qi::rule<Iterator, qi::in_state_skipper<Lexer> > assignment, if_stmt;
        qi::rule<Iterator, qi::in_state_skipper<Lexer> > while_stmt;
        
        // The expression is the only rule having a return value
        qi::rule<Iterator, expression_type(), qi::in_state_skipper<Lexer> >  expression;
    };
}

#endif /* grammar_h */
