#pragma once

#include <iostream>

#ifdef DEBUG_BUILD
    #define DEBUG(x) std::cout << x << '\n'
    #define TRACE(x) std::cout << #x << " = " << x << '\n';
#else
    #define DEBUG(x)
    #define TRACE(x)
#endif