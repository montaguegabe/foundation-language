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
//#include "ast.h"

namespace foundation {
    
    using namespace boost::spirit;
    using namespace boost::spirit::ascii;
    
    template <typename Iterator>
    struct LanguageGrammar : qi::grammar<Iterator, unsigned()>
    {
        template <typename TokenDef>
        LanguageGrammar(TokenDef const& tok)
        : LanguageGrammar::base_type(start)
        , c(0), w(0), l(0)
        {
            using qi::eps;
            using qi::lit;
            using qi::_val;
            using qi::_1;
            
            start = eps[_val = 22] >>
                    tok.constant;
        }
        
        std::size_t c, w, l;
        qi::rule<Iterator, unsigned()> start;
    };
}

#endif /* grammar_h */
