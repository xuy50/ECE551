#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include <iostream>
#include <sstream>
#include <string>

class Expression {
 public:
  virtual std::string toString() const = 0;  //abstract method
  virtual ~Expression(){};
};

class NumExpression : public Expression {
 private:
  long num;

 public:
  NumExpression(long num) { this->num = num; }
  std::string toString() const {  //actually implement it
    std::stringstream resultstream;
    std::string result;
    resultstream << this->num;
    resultstream >> result;
    return result;
  }

  ~NumExpression() {}
};

class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  std::string toString() const {  //actually implement it
    std::string result;

    result = "(" + result + lhs->toString() + " + " + rhs->toString() + ")";

    return result;
  }

  ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};

#endif
