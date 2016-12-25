//
//  Parser.cpp
//  Foundation
//
//  Created by Gabe Montague on 12/25/16.
//  Copyright © 2016 Gabe Montague. All rights reserved.
//

#include "Parser.hpp"

#include <iostream>
#include <string>

using namespace foundation;

// Returns a tribool indicating parsing success. The middle state indicates that
boost::logic::tribool Parser::fromString(std::string & str) {
    
    // Generate the iterator pair used to expose the tokenized input stream.
    std::string::iterator it = str.begin();
    IteratorType iter = _tokenizer.begin(it, str.end());
    IteratorType end = _tokenizer.end();
    
    // Define the lexer state to be used for skipping
    std::string ws("WS");
    
    // Parse the string
    bool r = qi::phrase_parse(iter, end, _parser, qi::in_state(ws)[_tokenizer.self]);
    
    // Check results
    if (r && iter == end) {
        return true;
        
        // Check for unbalanced blocks - in this case we keep the input going
    } else if(_parser.curly != 0) {
        return boost::indeterminate;
        
        // Otherwise failed to parse
    } else {
        return false;
    }
}
