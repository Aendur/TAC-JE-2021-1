#ifndef ERRORS_H
#define ERRORS_H

#include <stdexcept>
#include <string>

#define STRING2(val) #val
#define STRING(val) STRING2(val)

#define MSG_ERROR_COLOR(msg) "\033[31;1m" msg "\033[0m"

#define MSG_UNIMPLEMENTED_ERR MSG_ERROR_COLOR(__FILE__ "(" STRING(__LINE__) "): " __FUNCTION__ " not implemented")
#define MSG_INCOMPLETE_ERR    MSG_ERROR_COLOR(__FILE__ "(" STRING(__LINE__) "): " __FUNCTION__ " incomplete implementation")

#endif