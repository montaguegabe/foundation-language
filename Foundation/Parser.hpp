//
//  Parser.hpp
//  Foundation
//
//  Created by Gabe Montague on 12/25/16.
//  Copyright © 2016 Gabe Montague. All rights reserved.
//

#ifndef Parser_hpp
#define Parser_hpp

#include <string>
#include "boost.h"

namespace foundation {
    
    class Parser {
    public:
        Parser() {}
        
        boost::logic::tribool fromString(std::string & str);
    };
}

#endif /* Parser_hpp */
