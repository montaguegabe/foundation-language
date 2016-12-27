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
        ID_IDENTIFIER,
        ID_STRING,
        ID_INCREMENT,
        ID_DECREMENT,
        ID_IF,
        ID_ELSE,
        ID_WHILE
    };
    
    template <typename Lexer>
    struct LanguageTokens : lex::lexer<Lexer> {
        
        LanguageTokens() {
            
            // Assign token definitions
            identifier = "[a-zA-Z_][a-zA-Z0-9_]*";
            constant = "[0-9]+";
            //string = "\\\"[^\\\"]+\\\""; // For without escape
            string = "\\\"([^\\\"]|\\\\\\\")+\\\""; // Allows escaped quotes
            
            // Define single-symbol tokens
            this->self = lex::token_def<>('(')
            | ')'
            | '{'
            | '}'
            | '-'
            | '+'
            | '*'
            | '/'
            | '='
            | ','
            | ';';
            
            // Define tokens
            this->self.add
            (constant, ID_CONSTANT)
            (identifier, ID_IDENTIFIER)
            (string, ID_STRING)
            ("if", ID_IF)
            ("else", ID_ELSE)
            ("while", ID_WHILE)
            ("$$", ID_INCREMENT)
            ("%%", ID_DECREMENT);
            
            // Define whitespace token for skipping
            this->self("WS")
            = lex::token_def<>("[ \\t\\n]+")
            | "#[^\\n]+"; // Only single line comments are supported
        }
        
        lex::token_def<std::string> identifier;
        lex::token_def<unsigned int> constant;
        lex::token_def<std::string> string;
    };
}

#endif /* tokens_h */
