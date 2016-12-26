//
//  Parser.hpp
//  Foundation
//
//  Created by Gabe Montague on 12/25/16.
//  Copyright © 2016 Gabe Montague. All rights reserved.
//

#ifndef Parser_hpp
#define Parser_hpp

#include <string>
#include <iostream>
#include "boost.h"
#include "tokens.h"
#include "grammar.h"
#include "ast2.h"

namespace foundation {
    
    namespace lex = boost::spirit::lex;
    
    // Get string's iterator type
    typedef std::string::iterator BaseIteratorType;
    
    // Get the token type outputted by the lexer
    typedef lex::lexertl::token<BaseIteratorType, boost::mpl::vector<unsigned int, std::string> > LexertlTokenType;
    
    // Get the lexer type
    typedef lex::lexertl::lexer<LexertlTokenType> LexerType;
    
    // Get the tokenizer type (derived from the given lexer type).
    typedef LanguageTokens<LexerType> Tokenizer;
    
    // Get the lexer iterator type
    typedef Tokenizer::iterator_type IteratorType;
    
    // Get the parser type
    typedef LanguageGrammar<IteratorType, Tokenizer::lexer_def> BoostParser;
    
    class Parser {
    public:
        Parser() : _tokenizer(), _parser(_tokenizer) {
        }
        
        // Parses a string. Returns if a string is successfully parsed
        bool parse(std::string & str);
        
    private:
        
        // Internal parser and tokenizer
        Tokenizer _tokenizer;
        BoostParser _parser;
        
        // The result of the parsing
        ast::ExpressionType _result;
    };
}

#endif /* Parser_hpp */
