//
//  tokens.h
//  Foundation
//
//  Created by Gabe Montague on 12/24/16.
//  Copyright © 2016 Gabe Montague. All rights reserved.
//

#ifndef tokens_h
#define tokens_h

#include "boost.h"


namespace foundation {
    
    namespace lex = boost::spirit::lex;
    namespace qi = boost::spirit::qi;
    using boost::phoenix::val;
    using boost::phoenix::ref;
    
    // Define token identifiers
    enum token_ids {
        ID_CONSTANT = 1000,
        ID_IF,
        ID_ELSE,
        ID_WHILE,
        ID_IDENTIFIER
    };
    
    template <typename Lexer>
    struct LanguageTokens : lex::lexer<Lexer> {
        
        LanguageTokens() {
            
            // Define regular expressions
            identifier = "[a-zA-Z_][a-zA-Z0-9_]*";
            constant = "[0-9]+";
            
            // Associate the tokens and the token set with the lexer
            this->self = lex::token_def<>('(')
            | ')'
            | '{'
            | '}'
            | '-'
            | '+'
            | '*'
            | '/'
            | '='
            | ';';
            
            // Define tokens
            this->self.add
            (constant, ID_CONSTANT)
            ("if", ID_IF)
            ("else", ID_ELSE)
            ("while", ID_WHILE)
            (identifier, ID_IDENTIFIER);
            
            this->self("WS")
            =   lex::token_def<>("[ \\t\\n]+")
            |   "\\/\\*[^*]*\\*+([^/*][^*]*\\*+)*\\/";
        }
        
        lex::token_def<std::string> identifier;
        lex::token_def<unsigned int> constant;
    };
}

#endif /* tokens_h */
