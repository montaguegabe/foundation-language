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
    struct LanguageGrammar : qi::grammar<Iterator>
    {
        template <typename TokenDef>
        LanguageGrammar(TokenDef const& tok)
        : LanguageGrammar::base_type(start)
        , c(0), w(0), l(0)
        {
            using boost::phoenix::ref;
            using boost::phoenix::size;
            
            start = *(tok.while_[++ref(w), ++ref(c)]
                     | tok.else_[++ref(c), ++ref(l)]
                     | tok.if_[++ref(c)])
            ;
        }
        
        std::size_t c, w, l;
        qi::rule<Iterator> start;
    };
}

#endif /* grammar_h */
