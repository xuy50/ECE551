#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include <iostream>
#include <sstream>
#include <string>

class Expression {
 public:
  virtual std::string toString() const = 0;  //abstract method
  virtual long evaluate() const = 0;
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

  long evaluate() const { return num; }

  ~NumExpression() {}
};

class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}

  std::string toString() const {
    std::string result;

    result = "(" + result + lhs->toString() + " + " + rhs->toString() + ")";

    return result;
  }

  long evaluate() const { return (lhs->evaluate() + rhs->evaluate()); }

  ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};

class MinusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  MinusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}

  std::string toString() const {
    std::string result;

    result = "(" + result + lhs->toString() + " - " + rhs->toString() + ")";

    return result;
  }

  long evaluate() const { return (lhs->evaluate() - rhs->evaluate()); }

  ~MinusExpression() {
    delete lhs;
    delete rhs;
  }
};

class TimesExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  TimesExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}

  std::string toString() const {
    std::string result;

    result = "(" + result + lhs->toString() + " * " + rhs->toString() + ")";

    return result;
  }

  long evaluate() const { return (lhs->evaluate() * rhs->evaluate()); }

  ~TimesExpression() {
    delete lhs;
    delete rhs;
  }
};

class DivExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  DivExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}

  std::string toString() const {
    std::string result;

    result = "(" + result + lhs->toString() + " / " + rhs->toString() + ")";

    return result;
  }

  long evaluate() const { return (lhs->evaluate() / rhs->evaluate()); }

  ~DivExpression() {
    delete lhs;
    delete rhs;
  }
};

#endif
