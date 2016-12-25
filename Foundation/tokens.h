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

    enum tokenids {
        IDANY = lex::min_token_id + 10
    };
    
    template <typename Lexer>
    struct LanguageTokens : lex::lexer<Lexer> {
        
        LanguageTokens() {
            
            // Token types
            identifier = "[a-zA-Z_][a-zA-Z0-9_]*";
            constant = "[0-9]+";
            if_ = "if";
            else_ = "else";
            while_ = "while";
            
            // Associate the tokens and the token set with the lexer
            this->self = lex::token_def<>('(') | ')' | '{' | '}' | '=' | ';' | constant;
            this->self += if_ | else_ | while_ | identifier;
            
            // Define the whitespace to ignore (spaces, tabs, newlines and C-style comments)
            this->self("WS")
            =   lex::token_def<>("[ \\t\\n]+")
            |   "\\/\\*[^*]*\\*+([^/*][^*]*\\*+)*\\/"
            ;
        }
        
        // These tokens expose the iterator_range of the matched input sequence
        lex::token_def<> if_, else_, while_;
        
        lex::token_def<std::string> identifier;
        lex::token_def<unsigned> constant;
    };
}

#endif /* tokens_h */
