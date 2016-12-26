//
//  main.cpp
//  Interpreter
//
//  Created by Gabe Montague on 12/23/16.
//  Copyright © 2016 Gabe Montague. All rights reserved.
//

#define BOOST_VARIANT_USE_RELAXED_GET_BY_DEFAULT
//#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
#define BOOST_SPIRIT_QI_DEBUG

#include <iostream>
#include "version.h"
#include "Parser.hpp"
#include "boost.h"

static void printGreeting();

int main(int argc, const char * argv[]) {
    
    using namespace foundation;
    
    // Create a parser
    Parser parser;
    
    // Greet the user
    printGreeting();
    
    // The aggregated results from previous lines
    std::string aggregate = "";
    int curlyBalance = 0;
    
    while (true) {
        std::cout << ">>> ";
        
        std::string input;
        std::getline(std::cin, input);
        
        if (input.empty() || input == "q" || input == "Q" || input == "quit()") {
            break;
        }
        
        // Add to aggregate
        aggregate += input;
        
        // Determine if our input is balanced
        for (char & c : input) {
            if (c == '{') ++curlyBalance;
            if (c == '}') --curlyBalance;
        }
        if (curlyBalance <= 0) {
            
            // Parse the accumulated string
            bool result = parser.parse(aggregate);
            
            if (!result) {
                std::cout << "Syntax error." << std::endl;
            } else {
                std::cout << "Done, with 0 errors." << std::endl;
            }
            
            // Reset accumulation
            aggregate = "";
            curlyBalance = 0;
        }
    }

    return 0;
}

// Print interactive console greating
static void printGreeting() {

    std::cout << "Foundation Language " << FOUNDATION_VERSION_MAJOR << "."
    << FOUNDATION_VERSION_MINOR << "."
    << FOUNDATION_VERSION_BUGFIX << " ";
    std::cout << "Interactive Console" << std::endl;
    std::cout << "Enter q/Q to exit." << std::endl;
}
