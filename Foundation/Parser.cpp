//
//  Parser.cpp
//  Foundation
//
//  Created by Gabe Montague on 12/25/16.
//  Copyright © 2016 Gabe Montague. All rights reserved.
//

#include <iostream>
#include <string>

#include "ast2.h"
#include "Parser.hpp"

using namespace foundation;

// Parses a string. Returns if a string is successfully parsed
bool Parser::parse(std::string & str) {
    
    // Generate the iterator pair used to expose the tokenized input stream.
    std::string::iterator it = str.begin();
    IteratorType iter = _tokenizer.begin(it, str.end());
    IteratorType end = _tokenizer.end();
    
    // Define the lexer state to be used for skipping
    std::string ws("WS");
    
    // Parse the string
    ast::ExpressionType result;
    bool r = qi::phrase_parse(iter, end, _parser, qi::in_state(ws)[_tokenizer.self], result);
    _result = result;
    
    // Return results
    if (r && iter == end) {
        return true;
    }
    return false;
}
