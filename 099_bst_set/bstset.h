#ifndef __BSTMAP_H__
#define __BSTMAP_H__

#include <cstdlib>
#include <exception>
#include <iostream>

#include "set.h"

template<typename T>
class BstSet : public Set<T> {
 protected:
  class Node {
   public:
    T key;
    Node * left;
    Node * right;
    Node(const T _key) : key(_key), left(NULL), right(NULL) {}
  };

  Node * root;

  Node * copyHelp(Node * curr, Node * rhs) {
    if (rhs != NULL) {
      curr = new Node(rhs->key);
      curr->left = copyHelp(curr->left, rhs->left);
      curr->right = copyHelp(curr->right, rhs->right);
      return curr;
    }
    return NULL;
  }

  void deleteHelp(Node * n) {
    if (n != NULL) {
      deleteHelp(n->left);
      deleteHelp(n->right);
      delete n;
    }
  }

  void removeHelp(Node * pn, int lrCheck) {
    Node * n;
    if (lrCheck == 1) {
      n = pn->right;
    }
    else if (lrCheck == -1) {
      n = pn->left;
    }
    else if (lrCheck == 0) {
      n = pn;
    }

    Node * curr = n;
    if (n->right != NULL) {
      curr = curr->right;
      if (curr->left != NULL) {
        while (curr->left->left != NULL) {
          curr = curr->left;
        }
        n->key = curr->left->key;
        Node * cLeft = curr->left;
        curr->left = cLeft->right;
        delete cLeft;
      }
      else {
        n->key = n->right->key;
        Node * cRight = curr->right;
        delete curr;
        n->right = cRight;
      }
      return;
    }
    else if (n->right == NULL && n->left != NULL) {
      curr = curr->left;
      if (curr->right != NULL) {
        while (curr->right->right != NULL) {
          curr = curr->right;
        }
        n->key = curr->right->key;
        Node * cRight = curr->right;
        curr->right = cRight->left;
        delete cRight;
      }
      else {
        n->key = n->left->key;
        Node * cLeft = curr->left;
        delete curr;
        n->left = cLeft;
      }
      return;
    }
    else {
      delete n;
      if (lrCheck == 0)
        root = NULL;
      if (lrCheck == 1)
        pn->right = NULL;
      else if (lrCheck == -1)
        pn->left = NULL;
    }
  }

 public:
  BstSet() : root(NULL) {}

  BstSet(const T _key) { root = new Node(_key); }

  BstSet(const BstSet & rhs) { root = copyHelp(root, rhs.root); }

  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      deleteHelp(root);
      root = NULL;
      root = copyHelp(root, rhs.root);
    }
    return *this;
  }
  virtual ~BstSet() { deleteHelp(root); }

  virtual void add(const T & key) {
    if (root == NULL) {
      root = new Node(key);
      return;
    }

    Node * curr = root;
    int currCheck = 0;
    while (curr != NULL) {
      T currKey = curr->key;
      if (currKey == key) {
        return;
      }
      else if (currKey < key) {
        currCheck = 1;
        if (curr->right != NULL)
          curr = curr->right;
        else
          break;
      }
      else if (currKey > key) {
        currCheck = -1;
        if (curr->left != NULL)
          curr = curr->left;
        else
          break;
      }
    }
    if (currCheck == 1)
      curr->right = new Node(key);
    else if (currCheck == -1)
      curr->left = new Node(key);
  }

  bool contains(const T & key) const {
    if (root == NULL) {
      return false;
    }

    Node * curr = root;
    while (curr != NULL) {
      T currKey = curr->key;
      if (currKey == key) {
        return true;
      }
      else if (currKey < key) {
        curr = curr->right;
      }
      else if (currKey > key) {
        curr = curr->left;
      }
    }

    return false;
  }

  virtual void remove(const T & key) {
    Node * curr = root;
    if (curr->right == NULL && curr->left == NULL && curr->key == key) {
      delete root;
      root = NULL;
      return;
    }
    else if (curr->key == key) {
      removeHelp(root, 0);
      return;
    }
    while (curr->right != NULL || curr->left != NULL) {
      T currKey = curr->key;
      if (currKey < key) {
        if (curr->right == NULL) {
          return;
        }
        else if (curr->right->key == key) {
          removeHelp(curr, 1);
          break;
        }
        else {
          curr = curr->right;
        }
      }
      else if (currKey > key) {
        if (curr->left == NULL) {
          return;
        }
        else if (curr->left->key == key) {
          removeHelp(curr, -1);
          break;
        }
        else {
          curr = curr->left;
        }
      }
    }
  }

 private:
  void printHelp(Node * n) {
    if (n != NULL) {
      std::cout << n->key << std::endl;
      printHelp(n->left);
      printHelp(n->right);
    }
  }

 public:
  void printTree() { printHelp(root); }
};

#endif
