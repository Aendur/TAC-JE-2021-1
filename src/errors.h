#ifndef ERRORS_H
#define ERRORS_H

#include <stdexcept>
#include <string>

#define MSG_UNIMPLEMENTED_ERROR  std::string(__FILE__) + "(" + std::to_string(__LINE__) + "): unimplemented | " + std::string(__FUNCTION__)
#endif