#ifndef ERRORS_H
#define ERRORS_H

#include <stdexcept>
#include <string>

#define MSG_UNIMPLEMENTED_ERR std::string(__FILE__) + "(" + std::to_string(__LINE__) + "): unimplemented | " + std::string(__FUNCTION__)
#define MSG_INCOMPLETE_IMPLMT std::string(__FILE__) + "(" + std::to_string(__LINE__) + "): incomplete implementation | " + std::string(__FUNCTION__)
#endif