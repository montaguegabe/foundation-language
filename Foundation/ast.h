//
//  ast.h
//  Foundation
//
//  Created by Gabe Montague on 12/22/16.
//  Copyright © 2016 Gabe Montague. All rights reserved.
//

#ifndef ast_h
#define ast_h

#include "boost.h"

#pragma mark - Type declarations

namespace foundation { namespace ast {
    
    struct None {};
    struct Signed;
    struct Program;
    
    typedef boost::variant<
        None,
        unsigned int,
        boost::recursive_wrapper<Signed>,
        boost::recursive_wrapper<Program>
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
    
    struct Program {
        Operand first;
        std::list<Operation> rest;
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
    foundation::ast::Program,
    (foundation::ast::Operand, first)
    (std::list<foundation::ast::Operation>, rest)
)


#pragma mark - Evaluation

namespace foundation { namespace ast {

    // Recursively evaluates an AST node
    struct eval {
        
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
    };
}}

#endif /* ast_h */