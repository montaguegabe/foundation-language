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

namespace foundation { namespace ast {
  
    // Declare type for expressions
    typedef boost::variant<unsigned int, std::string> ExpressionType;
    
    
} }

#endif /* ast2_h */
