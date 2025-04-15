#include <stdexcept>
#include <string>

#ifndef CUSTOM_EXCEPTION_HPP

#define CUSTOM_EXCEPTION_HPP

class SelfAssignmentException : public std::runtime_error
{
public:
  explicit SelfAssignmentException(const std::string &msg = "Self assignment is not a valid operation.") : std::runtime_error(msg) {};
};

class Underflow : public std::runtime_error
{
public:
  explicit Underflow(const std::string &msg = "Stack is empty!") : std::runtime_error(msg) {};
};

class Overflow : public std::runtime_error
{
public:
  explicit Overflow(const std::string &msg = "Stack is full!") : std::runtime_error(msg) {};
};

class InvalidQueueSize : public std::runtime_error
{
public:
  explicit InvalidQueueSize(const std::string &msg = "Size of queue must be greater than zero.") : std::runtime_error(msg) {};
};

#endif