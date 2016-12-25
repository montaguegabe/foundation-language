//
//  main.cpp
//  Interpreter
//
//  Created by Gabe Montague on 12/23/16.
//  Copyright © 2016 Gabe Montague. All rights reserved.
//

#define BOOST_VARIANT_USE_RELAXED_GET_BY_DEFAULT

#include <iostream>
#include "version.h"
//#include "ast.h"
#include "Parser.hpp"
#include "boost.h"

static void printGreeting();

int main(int argc, const char * argv[]) {
    
    using namespace foundation;
    using boost::logic::tribool;
    
    Parser parser;
    
    printGreeting();
    
    // The aggregated results from previous lines
    std::string aggregate = "";
    
    while (true) {
        std::cout << ">>> ";
        std::string input;
        std::getline(std::cin, input);
        
        if (input.empty() || input == "q" || input == "Q" || input == "quit()") {
            break;
        }
        
        aggregate += input;
        tribool result = parser.fromString(aggregate);
        //boost::logic::tribool result = true;
        
        if (!result) {
            std::cout << "Syntax error." << std::endl;
            aggregate = "";
        } else if (result) {
            std::cout << "Done, with 0 errors." << std::endl;
            aggregate = "";
        } else {
            // Is indeterminate
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
