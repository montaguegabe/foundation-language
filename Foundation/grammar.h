//
//  grammar.h
//  Foundation
//
//  Created by Gabe Montague on 12/22/16.
//  Copyright © 2016 Gabe Montague. All rights reserved.
//

#ifndef grammar_h
#define grammar_h

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/foreach.hpp>

#include <iostream>
#include <string>

namespace foundation {
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;
    
    // Define parsing grammar for expressions
    template <typename Iterator>
    struct LanguageGrammar : qi::grammar<
        Iterator, // Iterator type
        ast::Program(), // Start grammar
        ascii::space_type // Skip grammar
    > {
        
        // Constructor
        LanguageGrammar() : LanguageGrammar::base_type(expression)
        {
            qi::uint_type UInt;
            qi::char_type Char;
            
            // Define rule for expression
            expression =
            term
            >> *(   (Char('+') >> term)
                 |   (Char('-') >> term)
                 )
            ;
            
            // Define rule for terms
            term =
            factor
            >> *(   (Char('*') >> factor)
                 |   (Char('/') >> factor)
                 )
            ;
            
            // Define rule for 'factors'
            factor =
            UInt
            |   '(' >> expression >> ')'
            |   (Char('-') >> factor)
            |   (Char('+') >> factor)
            ;
        }
        
        // Register rules as member variables
        qi::rule<Iterator, ast::Program(), ascii::space_type> expression;
        qi::rule<Iterator, ast::Program(), ascii::space_type> term;
        qi::rule<Iterator, ast::Operand(), ascii::space_type> factor;
    };
}

#endif /* grammar_h */
