#ifndef ERRORS_H
#define ERRORS_H

#include <stdexcept>
#include <iostream>
#include <string>

#define STRING2(val) #val
#define STRING(val) STRING2(val)

#define MSG_ERROR_COLOR_RED(msg) "\033[31;1m" msg "\033[m"
#define MSG_ERROR_COLOR_YLW(msg) "\033[33;1m" msg "\033[m"

#define MSG_UNIMPLEMENTED_ERR MSG_ERROR_COLOR_RED(__FILE__ "(" STRING(__LINE__) "): " __FUNCTION__ " not implemented")
#define MSG_INCOMPLETE_ERR    MSG_ERROR_COLOR_YLW(__FILE__ "(" STRING(__LINE__) "): " __FUNCTION__ " incomplete implementation")

#define DEBUG(msg) std::cout << __FILE__ << ' ' << __FUNCTION__ << ' ' << __LINE__ << ' ' << msg

#endif