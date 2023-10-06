#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {
}
IntArray::IntArray(int n) : data(new int[n]), numElements(n) {
}

IntArray::IntArray(const IntArray & rhs) :
    data(new int[rhs.numElements]), numElements(rhs.numElements) {
  for (int i = 0; i < numElements; i++) {
    this->data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this == &rhs) {
    return *this;
  }
  delete[] data;

  this->data = new int[rhs.numElements];
  this->numElements = rhs.numElements;
  for (int i = 0; i < numElements; i++) {
    this->data[i] = rhs.data[i];
  }
  return *this;
}
const int & IntArray::operator[](int index) const {
  assert(index >= 0 && index < numElements);
  return this->data[index];
}
int & IntArray::operator[](int index) {
  assert(index >= 0 && index < numElements);
  return this->data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (this->numElements != rhs.numElements)
    return false;
  for (int i = 0; i < numElements; i++) {
    if (this->data[i] != rhs.data[i])
      return false;
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  if (this->numElements != rhs.numElements)
    return true;
  for (int i = 0; i < numElements; i++) {
    if (this->data[i] != rhs.data[i])
      return true;
  }
  return false;
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << "{";
  for (int i = 0; i < rhs.size(); i++) {
    s << rhs[i];
    if (i != (rhs.size() - 1)) {
      s << ", ";
    }
  }
  s << "}";
  return s;
}
