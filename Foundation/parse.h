//
//  parse.h
//  Foundation
//
//  Created by Gabe Montague on 12/24/16.
//  Copyright © 2016 Gabe Montague. All rights reserved.
//

#ifndef parse_h
#define parse_h
/*
#include "boost.h"
#include "tokens.h"
#include "grammar.h"

#include <iostream>
#include <string>

namespace foundation { namespace ast {
    
    namespace lex = boost::spirit::lex;
    using boost::logic::tribool;

    // Returns a tribool indicating parsing success. The middle state indicates that
    tribool fromString(std::string & str) {
        
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
        
        // From the given types, instantiate a tokenizer and parser
        Tokenizer tokenizer;
        BoostParser parser(tokenizer);
        
        // Generate the iterator pair used to expose the tokenized input stream.
        std::string::iterator it = str.begin();
        IteratorType iter = tokenizer.begin(it, str.end());
        IteratorType end = tokenizer.end();
        
        // Define the lexer state to be used for skipping
        std::string ws("WS");
        
        // Parse the string
        bool r = qi::phrase_parse(iter, end, parser, qi::in_state(ws)[tokenizer.self]);
        
        // Check results
        if (r && iter == end) {
            return true;
        
        // Check for unbalanced blocks - in this case we keep the input going
        } else if(parser.curly != 0) {
            return boost::indeterminate;
        
        // Otherwise failed to parse
        } else {
            return false;
        }
    }
}
}
*/
#endif /* parse_h */
