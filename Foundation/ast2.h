//
//  ast2.h
//  Foundation
//
//  Created by Gabe Montague on 12/25/16.
//  Copyright © 2016 Gabe Montague. All rights reserved.
//

#ifndef ast2_h
#define ast2_h

#include "boost.h"
#include <string>

#pragma mark - Type declarations

namespace foundation { namespace ast {
    
        struct None {};
        struct signed_;
        struct program;
        
        typedef boost::variant<
        None
        , unsigned int
        , boost::recursive_wrapper<signed_>
        , boost::recursive_wrapper<program>
        >
        operand;
        
        struct signed_
        {
            char sign;
            operand operand_;
        };
        
        struct operation
        {
            char operator_;
            operand operand_;
        };
        
        struct program
        {
            operand first;
            std::list<operation> rest;
        };
        
        // print function for debugging
        inline std::ostream& operator<<(std::ostream& out, None) { out << "None"; return out; }
    }}

BOOST_FUSION_ADAPT_STRUCT(
                          foundation::ast::signed_,
                          (char, sign)
                          (foundation::ast::operand, operand_)
                          )

BOOST_FUSION_ADAPT_STRUCT(
                          foundation::ast::operation,
                          (char, operator_)
                          (foundation::ast::operand, operand_)
                          )

BOOST_FUSION_ADAPT_STRUCT(
                          foundation::ast::program,
                          (foundation::ast::operand, first)
                          (std::list<foundation::ast::operation>, rest)
                          )


#pragma mark - Evaluation

namespace foundation { namespace ast {
    
    // Print the AST
    struct printer
    {
        typedef void result_type;
        
        void operator()(None) const {}
        void operator()(unsigned int n) const { std::cout << n; }
        
        void operator()(operation const& x) const
        {
            boost::apply_visitor(*this, x.operand_);
            switch (x.operator_)
            {
                case '+': std::cout << " add"; break;
                case '-': std::cout << " subt"; break;
                case '*': std::cout << " mult"; break;
                case '/': std::cout << " div"; break;
            }
        }
        
        void operator()(signed_ const& x) const
        {
            boost::apply_visitor(*this, x.operand_);
            switch (x.sign)
            {
                case '-': std::cout << " neg"; break;
                case '+': std::cout << " pos"; break;
            }
        }
        
        void operator()(program const& x) const
        {
            boost::apply_visitor(*this, x.first);
            BOOST_FOREACH(operation const& oper, x.rest)
            {
                std::cout << ' ';
                (*this)(oper);
            }
        }
    };
    
    // Recursively evaluates an AST node
    /*struct eval {
        
        // Traits
        typedef int result_type;
        
        // Should never be called on an empty node
        int operator()(None) const { BOOST_ASSERT(0); return 0; }
        
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
        
        // Program evaluation
        int operator()(Program const& x) const {
            
            int state = boost::apply_visitor(*this, x.first);
            BOOST_FOREACH(Operation const& oper, x.rest) {
                state = (*this)(oper, state);
            }
            return state;
        }
    };*/
}}


#endif /* ast2_h */
