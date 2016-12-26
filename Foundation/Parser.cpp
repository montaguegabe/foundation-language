//
//  Parser.cpp
//  Foundation
//
//  Created by Gabe Montague on 12/25/16.
//  Copyright © 2016 Gabe Montague. All rights reserved.
//

#include <iostream>
#include <string>

#include "ast.h"
#include "Parser.hpp"

using namespace foundation;

// Parses a string. Returns if a string is successfully parsed
bool Parser::parse(std::string & str) {
    
    // TODO: Edge case when parsing empty strings
    
    // Generate the iterator pair used to expose the tokenized input stream.
    std::string::iterator it = str.begin();
    IteratorType iter = _tokenizer.begin(it, str.end());
    IteratorType end = _tokenizer.end();
    
    // Define the lexer state to be used for skipping
    std::string ws("WS");
    
    // Parse the string
    FOUNDATION_AST_BASE_TYPE result;
    bool r = qi::phrase_parse(iter, end, _parser, qi::in_state(ws)[_tokenizer.self], result);
    _result = result;
    
    // Debug printing of value
    typedef ast::printer ast_print;
    //typedef ast::eval ast_eval;
    //ast_eval eval;
    ast_print print;
    print(result);
    //std::cout << std::endl << eval(result);
    std::cout << std::endl;
    
    // Return results
    if (r && iter == end) {
        return true;
    }
    return false;
}
