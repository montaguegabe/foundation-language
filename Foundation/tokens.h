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
        ID_SHIFT_LEFT,
        ID_SHIFT_RIGHT,
        ID_LEQ,
        ID_GEQ,
        ID_EQUAL,
        ID_NOT_EQUAL,
        ID_AND,
        ID_OR,
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
            | '['
            | ']'
            | '='
            | ','
            | ';'
            | '.'
            
            // Ternary
            | '?'
            | ':'
            
            // Binary
            | '-'
            | '+'
            | '*'
            | '/'
            | '^'
            | '%'
            
            // Relational/logic
            | '>'
            | '<'
            | '&'
            | '^'
            | '|'

            // Unary operators
            | '!'
            | '~'
            | '+'
            | '-';
            
            // Define tokens in order of precedence
            this->self.add
            
            // Keywords
            ("while", ID_WHILE)
            ("if", ID_IF)
            ("else", ID_ELSE)
            
            // Constants, identifiers, strings
            (constant, ID_CONSTANT)
            (identifier, ID_IDENTIFIER)
            (string, ID_STRING)
            
            // Double length symbols
            ("\\+\\+", ID_INCREMENT)
            ("--", ID_DECREMENT)
            ("<<", ID_SHIFT_LEFT)
            (">>", ID_SHIFT_RIGHT)
            ("<=", ID_LEQ)
            (">=", ID_GEQ)
            ("==", ID_EQUAL)
            ("!=", ID_NOT_EQUAL)
            ("&&", ID_AND)
            ("\\|\\|", ID_OR);
            
            // Define whitespace token for skipping
            this->self("WS")
            = lex::token_def<>("[ \\t\\n]+")
            | "#[^\\n]+"; // Only single line comments are supported
        }
        
        lex::token_def<std::string> identifier;
        lex::token_def<unsigned int> constant;
        lex::token_def<std::string> string;
        lex::token_def<lex::omit> marker;
    };
}

#endif /* tokens_h */
