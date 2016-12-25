//
//  main.cpp
//  Interpreter
//
//  Created by Gabe Montague on 12/23/16.
//  Copyright © 2016 Gabe Montague. All rights reserved.
//

#include <iostream>
#include "version.h"
#include "ast.h"
#include "parse.h"

static void printGreeting();

int main(int argc, const char * argv[]) {
    
    printGreeting();
    
    while (true) {
        std::cout << ">>> ";
        std::string input;
        std::getline(std::cin, input);
        
        if (input == "q" || input == "Q" || input == "quit()") {
            break;
        }
        
        foundation::ast::fromString(input);
    }

    return 0;
}

// Print interactive console greating
static void printGreeting() {

    std::cout << "Foundation Language " << FOUNDATION_VERSION_MAJOR << "."
    << FOUNDATION_VERSION_MINOR << "."
    << FOUNDATION_VERSION_BUGFIX << " ";
    std::cout << "Interactive Console\n";
    std::cout << "Enter q/Q to exit.\n";
}
