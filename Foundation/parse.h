//
//  parse.h
//  Foundation
//
//  Created by Gabe Montague on 12/24/16.
//  Copyright © 2016 Gabe Montague. All rights reserved.
//

#ifndef parse_h
#define parse_h

#include "boost.h"
#include "tokens.h"
#include "grammar.h"

namespace foundation { namespace ast {
    
    namespace lex = boost::spirit::lex;
    
    void fromString(std::string & str) {
        
        typedef lex::lexertl::token<
        char const*, boost::mpl::vector<std::string>
        > TokenType;
        
        typedef lex::lexertl::lexer<TokenType> LexerType;
        
        typedef LanguageTokens<LexerType>::iterator_type IteratorType;
        
        LanguageTokens<LexerType> lexer;
        LanguageGrammar<IteratorType> grammar (lexer);
        
        char const* first = str.c_str();
        char const* last = &first[str.size()];
        
        bool success = lex::tokenize_and_parse(first, last, lexer, grammar);
        
        std::cout << (success ? "Good" : "Bad") << "\n";
    }
}
}

#endif /* parse_h */
