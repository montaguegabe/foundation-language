//
//  main.cpp
//  ReturnTypeCheck
//
//  Created by Gabe Montague on 12/25/16.
//  Copyright © 2016 Gabe Montague. All rights reserved.
//
//  Use this target to quickly check return types of various parsing expressions
//

#include <iostream>
#include "boost.h"

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

// Test grammar return type
using namespace boost;

template <typename Expr, typename Iterator = spirit::unused_type>
struct attribute_of_parser {
    typedef typename spirit::result_of::compile<
    spirit::qi::domain, Expr
    >::type parser_expression_type;
    
    typedef typename spirit::traits::attribute_of<
    parser_expression_type, spirit::unused_type, Iterator
    >::type type;
};

template <typename T>
void display_attribute_of_parser(T const&) {
    typedef typename attribute_of_parser<T>::type attribute_type;
    
    std::cout << typeid(attribute_type).name() << std::endl;
}

int main(int argc, const char * argv[]) {
    
    // Get string's iterator type
    typedef std::string::iterator BaseIteratorType;
    
    // The expression is the only rule having a return value
    typedef boost::variant<unsigned int, std::string> expression_type;
    
    using ascii::char_;
    using boost::spirit::token;
    
    /*qi::rule<BaseIteratorType, expression_type()> expression
    =   qi::double_
    |   qi::int_
    ;
    display_attribute_of_parser(qi::int_ >> '=' >> expression);
    display_attribute_of_parser(qi::int_ >> '=' >> (qi::double_|qi::int_));*/
    display_attribute_of_parser(char_('+') | char_('-'));
}
