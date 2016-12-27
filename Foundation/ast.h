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

#define FOUNDATION_AST_BASE_TYPE foundation::ast::AtomicExpression

namespace foundation { namespace ast {
    
    struct AtomicExpressionRec;
    
    typedef boost::variant<
        unsigned int,
        std::string,
        boost::recursive_wrapper<AtomicExpressionRec>
    >
    AtomicExpression;
    
    struct AtomicExpressionRec {
        AtomicExpression wrappedValue;
    };
}}

BOOST_FUSION_ADAPT_STRUCT(
    foundation::ast::AtomicExpressionRec,
    (foundation::ast::AtomicExpression, wrappedValue)
)

#pragma mark - Evaluation

namespace foundation { namespace ast {
    
    // Print the AST
    struct printer
    {
        typedef void result_type;
        
        // Unsigned int type
        void operator()(unsigned int n) const {
            std::cout << n;
        }
        
        // String type
        void operator()(std::string str) const {
            std::cout << str;
        }
        
        // Atomic expression type
        void operator()(AtomicExpressionRec const & wrapper) const {
            std::cout << "AERec{";
            boost::apply_visitor(*this, wrapper.wrappedValue);
            std::cout << "}";
        }
        
        void operator()(AtomicExpression const & expr) const {
            std::cout << "AE{";
            boost::apply_visitor(*this, expr);
            std::cout << "}";
        }
    };
    
    // Recursively evaluates an AST node
    /*struct eval {
        
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
        
        // Assignment operators
        int operator()(Assignment const & x) const {
            return boost::apply_visitor(*this, x.operand);
        }
    };*/
}}


#endif /* ast_h */
