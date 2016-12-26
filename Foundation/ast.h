//
//  ast.h
//  Foundation
//
//  Created by Gabe Montague on 12/25/16.
//  Copyright © 2016 Gabe Montague. All rights reserved.
//

#ifndef ast_h
#define ast_h

#include "boost.h"
#include <string>

#pragma mark - Type declarations

#define FOUNDATION_AST_BASE_TYPE foundation::ast::OperationList

namespace foundation { namespace ast {
    
    struct None {};
    struct Signed;
    struct OperationList;
    
    typedef boost::variant<
        None,
        unsigned int,
        boost::recursive_wrapper<Signed>,
        boost::recursive_wrapper<OperationList>
    >
    Operand;
    
    struct Signed {
        char sign;
        Operand operand;
    };
    
    struct Operation {
        char type;
        Operand operand;
    };
    
    struct OperationList {
        Operand first;
        std::list<Operation> rest;
    };
    
    struct Assignment {
        std::string identifier;
        OperationList expression;
    };
}}

BOOST_FUSION_ADAPT_STRUCT(
                          foundation::ast::Signed,
                          (char, sign)
                          (foundation::ast::Operand, operand)
                          )

BOOST_FUSION_ADAPT_STRUCT(
                          foundation::ast::Operation,
                          (char, type)
                          (foundation::ast::Operand, operand)
                          )

BOOST_FUSION_ADAPT_STRUCT(
                          foundation::ast::OperationList,
                          (foundation::ast::Operand, first)
                          (std::list<foundation::ast::Operation>, rest)
                          )

BOOST_FUSION_ADAPT_STRUCT(
                          foundation::ast::Assignment,
                          (std::string, identifier)
                          (foundation::ast::OperationList, expression)
                          )


#pragma mark - Evaluation

namespace foundation { namespace ast {
    
    // Print the AST
    struct printer
    {
        typedef void result_type;
        
        // Primitives
        void operator()(None) const {
            std::cout << "None";
        }
        
        void operator()(unsigned int n) const {
            std::cout << n;
        }
        
        void operator()(Operation const& x) const {
            
            std::cout << "Operation{operand = ";
            boost::apply_visitor(*this, x.operand);
            std::cout << "; type = '" << x.type << "';}";
        }
        
        void operator()(Signed const& x) const {
            std::cout << "Signed{operand = ";
            boost::apply_visitor(*this, x.operand);
            std::cout << "; sign = '" << x.sign << "';}";
        }
        
        void operator()(OperationList const& x) const {
            std::cout << "OperationList{[";
            boost::apply_visitor(*this, x.first);
            BOOST_FOREACH(Operation const & oper, x.rest) {
                std::cout << ", "; //<< std::endl;
                (*this)(oper);
            }
            std::cout << "]}";
        }
    };
    
    // Recursively evaluates an AST node
    struct eval {
        
        // Function traits
        typedef int result_type;
        
        // Should never be called on an empty node
        int operator()(None) const {
            // TODO: Throw exception
            return 0;
        }
        
        // Unsigned integer evaluation
        int operator()(unsigned int n) const { return n; }
        
        // Operation evaluation
        int operator()(Operation const& x, int lhs) const {
            
            int rhs = boost::apply_visitor(*this, x.operand);
            switch (x.type) {
                case '+': return lhs + rhs;
                case '-': return lhs - rhs;
                case '*': return lhs * rhs;
                case '/': return lhs / rhs;
            }
            
            BOOST_ASSERT(0);
            return 0;
        }
        
        // Sign evaluation
        int operator()(Signed const& x) const {
            
            int rhs = boost::apply_visitor(*this, x.operand);
            switch (x.sign)
            {
                case '-': return -rhs;
                case '+': return +rhs;
            }
            
            BOOST_ASSERT(0);
            return 0;
        }
        
        // Operand list evaluation
        int operator()(OperationList const& x) const {
            
            int state = boost::apply_visitor(*this, x.first);
            BOOST_FOREACH(Operation const& oper, x.rest) {
                state = (*this)(oper, state);
            }
            return state;
        }
    };
}}


#endif /* ast_h */
