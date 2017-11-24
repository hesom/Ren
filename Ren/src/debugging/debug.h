#pragma once
#ifdef _DEBUG
#include <iostream>
#define ASSERT(expr) if(expr){} else { std::cout << "Assertion failed in " << __FILE__ << " Line " <<  __LINE__; __debugbreak(); }
#define APICALL(expr) if(expr){} else { std::cout << "Assertion failed in " << __FILE__ << " Line " <<  __LINE__; __debugbreak(); }
#else
#define ASSERT(expr)
#define APICALL(expr) expr
#endif