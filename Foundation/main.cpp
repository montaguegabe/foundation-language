//
//  main.cpp
//  Foundation
//
//  Created by Gabe Montague on 12/22/16.
//  Copyright © 2016 Gabe Montague. All rights reserved.
//

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/foreach.hpp>

#include <iostream>
#include <string>

#include "ast.h"
#include "grammar.h"

#include <iostream>

extern int otherMain(int argc, const char * argv[]);
int main(int argc, const char * argv[])
{
    std::cout << "Welcome.\n";
    
    typedef std::string::const_iterator iterator_type;
    typedef foundation::LanguageGrammar<iterator_type> LanguageGrammar;
    typedef foundation::ast::Program ast_Program;
    //typedef foundation::ast::printer ast_print;
    typedef foundation::ast::eval ast_eval;
    
    std::string str;
    while (std::getline(std::cin, str))
    {
        if (str.empty() || str[0] == 'q' || str[0] == 'Q')
            break;
        
        LanguageGrammar calc;        // Our grammar
        ast_Program Program;    // Our Program (AST)
        //ast_print print;        // Prints the Program
        ast_eval eval;          // Evaluates the Program
        
        std::string::const_iterator iter = str.begin();
        std::string::const_iterator end = str.end();
        boost::spirit::ascii::space_type space;
        bool r = phrase_parse(iter, end, calc, space, Program);
        
        if (r && iter == end)
        {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            //print(Program);
            std::cout << "\nResult: " << eval(Program) << std::endl;
            std::cout << "-------------------------\n";
        }
        else
        {
            std::string rest(iter, end);
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "stopped at: \" " << rest << "\"\n";
            std::cout << "-------------------------\n";
        }
    }
    
    std::cout << "Bye... :-) \n\n";
    
    return 0; //otherMain(argc, argv);
}
