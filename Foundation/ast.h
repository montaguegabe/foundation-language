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

// What we parse to get at command line
#define FOUNDATION_AST_EXPRESSION_TYPE foundation::ast::BinOp
#define FOUNDATION_AST_EXPRESSION_NAME BinOp
//foundation::ast::PostfixExpression

// What we define as an expression
#define FOUNDATION_AST_BASE_TYPE foundation::ast::BinOp


#pragma mark - Type declarations

namespace foundation { namespace ast {
    
    // Atomic expression
    struct FOUNDATION_AST_EXPRESSION_NAME;
    typedef boost::variant<
        unsigned int,
        std::string,
        boost::recursive_wrapper<FOUNDATION_AST_EXPRESSION_NAME>
    >
    AtomicExpression;
    
    // Postfix expression
    typedef std::vector<FOUNDATION_AST_EXPRESSION_NAME> ExpressionList;
    typedef std::string PostfixSimple;
    struct PostfixExpressionList {
        std::string stringPart;
        ExpressionList listPart;
    };
    typedef boost::variant<
        PostfixSimple,
        PostfixExpressionList
    >
    Postfix;
    
    struct PostfixExpression {
        AtomicExpression base;
        std::vector<Postfix> postfixList;
    };
    
    // Unary expression
    struct UnaryExpression {
        std::vector<std::string> prefixes;
        PostfixExpression base;
    };
    
    // Continued term for a generalized binary operation.
    struct BinOpContinuation {
        std::string type;
        UnaryExpression rhs;
    };
    
    // Starting term for a generalized binary operation
    struct BinOp {
        UnaryExpression lhs;
        std::vector<BinOpContinuation> operations;
    };
    
    
}}

BOOST_FUSION_ADAPT_STRUCT(
                          foundation::ast::PostfixExpressionList,
                          (std::string, stringPart)
                          (foundation::ast::ExpressionList, listPart)
                          )

BOOST_FUSION_ADAPT_STRUCT(
                          foundation::ast::PostfixExpression,
                          (foundation::ast::AtomicExpression, base)
                          (std::vector<foundation::ast::Postfix>, postfixList)
                          )

BOOST_FUSION_ADAPT_STRUCT(
                          foundation::ast::UnaryExpression,
                          (std::vector<std::string>, prefixes)
                          (foundation::ast::PostfixExpression, base)
                          )

BOOST_FUSION_ADAPT_STRUCT(
                          foundation::ast::BinOpContinuation,
                          (std::string, type)
                          (foundation::ast::UnaryExpression, rhs)
                          )

BOOST_FUSION_ADAPT_STRUCT(
                          foundation::ast::BinOp,
                          (foundation::ast::UnaryExpression, lhs)
                          (std::vector<foundation::ast::BinOpContinuation>, operations)
                          )

#pragma mark - Evaluation

namespace foundation { namespace ast {
    
    // Print the AST
    /*struct printer
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
        void operator()(AtomicExpression const & expr) const {
            std::cout << "AE{";
            boost::apply_visitor(*this, expr);
            std::cout << "}";
        }
        
        // Postfix expression type
        void operator()(PostfixExpression const & expr) const {
            std::cout << "PFE{";
            boost::apply_visitor(*this, expr.base);
            std::cout << ", pf='";
            boost::apply_visitor(*this, expr.postfix);
            std::cout << "'}";
        }
    };*/
    
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
