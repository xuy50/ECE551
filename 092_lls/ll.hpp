#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
//YOUR CODE GOES HERE
class Tester;

class InvalidIndex : std::exception {
 private:
  std::string errMsg;

 public:
  InvalidIndex() { errMsg = "The index over the bound of the lined list."; }
  virtual ~InvalidIndex() throw() {}
  virtual const char * what() const throw() { return errMsg.c_str(); }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(0), next(NULL), prev(NULL){};
    Node(T nData) : data(nData), next(NULL), prev(NULL){};
    Node(T nData, Node * nextNode, Node * prevNode) :
        data(nData), next(nextNode), prev(prevNode){};
  };

  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0){};
  LinkedList(const T & item);
  LinkedList(const LinkedList & rhs);
  ~LinkedList();
  LinkedList & operator=(const LinkedList & rhs);
  void addFront(const T & item);
  void addBack(const T & item);
  bool remove(const T & item);
  T & operator[](int index);
  const T & operator[](int index) const;
  int find(const T & item) const;
  int getSize() const;
  friend class Tester;
};

template<typename T>
LinkedList<T>::LinkedList(const T & item) : size(1) {
  Node nNode = new Node(item);
  head = nNode;
  tail = nNode;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList & rhs) {
  head = NULL;
  tail = NULL;
  size = 0;
  Node * curr = rhs.head;
  while (curr != NULL) {
    addBack(curr->data);
    curr = curr->next;
  }
}

template<typename T>
LinkedList<T>::~LinkedList() {
  while (head != NULL) {
    Node * nNode = head->next;
    delete head;
    head = nNode;
  }
  head = NULL;
  tail = NULL;
  size = 0;
}

template<typename T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList & rhs) {
  if (this != &rhs) {
    if (size != 0) {
      while (head != NULL) {
        Node * nNode = head->next;
        delete head;
        head = nNode;
      }
      head = NULL;
      tail = NULL;
      size = 0;
    }
    Node * curr = rhs.head;
    while (curr != NULL) {
      addBack(curr->data);
      curr = curr->next;
    }
  }
  return *this;
}

template<typename T>
void LinkedList<T>::addFront(const T & item) {
  Node * nNode = new Node(item);
  Node * headNext = head;
  head = nNode;
  nNode->next = headNext;
  if (size == 0)
    tail = nNode;
  else
    headNext->prev = head;
  size++;
}

template<typename T>
void LinkedList<T>::addBack(const T & item) {
  Node * nNode = new Node(item);
  Node * tailPrev = tail;
  tail = nNode;
  nNode->prev = tailPrev;
  if (size == 0)
    head = nNode;
  else
    tailPrev->next = tail;
  size++;
}

template<typename T>
bool LinkedList<T>::remove(const T & item) {
  Node * curr = head;
  for (int i = 0; i < size; i++) {
    if (curr->data == item) {
      if (size == 1) {
        delete head;
        head = NULL;
        tail = NULL;
        size = 0;
        return true;
      }
      size--;
      if (size == 1) {
        if (i == 0) {
          delete head;
          head = tail;
          tail->prev = NULL;
        }
        else if (i == 1) {
          delete tail;
          tail = head;
          head->next = NULL;
        }
        return true;
      }
      else if (i == 0) {
        Node * headTemp = head->next;
        delete head;
        head = headTemp;
        head->prev = NULL;
        return true;
      }
      else if (i == size) {
        Node * tailTemp = tail->prev;
        delete tail;
        tail = tailTemp;
        tail->next = NULL;
        return true;
      }
      else {
        Node * nextTemp = curr->next;
        Node * prevTemp = curr->prev;
        delete curr;
        prevTemp->next = nextTemp;
        nextTemp->prev = prevTemp;
        return true;
      }
    }
    curr = curr->next;
  }
  return false;
}

template<typename T>
T & LinkedList<T>::operator[](int index) {
  if (index < 0 || index >= size)
    throw InvalidIndex();
  Node * curr = head;
  for (int i = 0; i < index; i++) {
    curr = curr->next;
  }
  return curr->data;
}

template<typename T>
const T & LinkedList<T>::operator[](int index) const {
  if (index < 0 || index >= size)
    throw InvalidIndex();
  Node * curr = head;
  for (int i = 0; i < index; i++) {
    curr = curr->next;
  }
  return curr->data;
}

template<typename T>
int LinkedList<T>::find(const T & item) const {
  Node * curr = head;
  for (int i = 0; i < size; i++) {
    if (curr->data == item) {
      return i;
    }
    curr = curr->next;
  }
  return -1;
}

template<typename T>
int LinkedList<T>::getSize() const {
  return size;
}

#endif
