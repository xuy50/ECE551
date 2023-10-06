#ifndef __BSTMAP_H__
#define __BSTMAP_H__

#include <cstdlib>
#include <exception>
#include <iostream>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 protected:
  class Node {
   public:
    K key;
    V val;
    Node * left;
    Node * right;
    Node(const K _key, const V _val) : key(_key), val(_val), left(NULL), right(NULL) {}
  };

  Node * root;

  //void copyHelp(Node * rhs) {
  //if (rhs != NULL) {
  //add(rhs->key, rhs->val);
  //copyHelp(rhs->left);
  //copyHelp(rhs->right);
  //}
  //}

  Node * copyHelp(Node * curr, Node * rhs) {
    if (rhs != NULL) {
      curr = new Node(rhs->key, rhs->val);
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
        n->val = curr->left->val;
        Node * cLeft = curr->left;
        curr->left = cLeft->right;
        delete cLeft;
      }
      else {
        n->key = n->right->key;
        n->val = n->right->val;
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
        n->val = curr->right->val;
        Node * cRight = curr->right;
        curr->right = cRight->left;
        delete cRight;
      }
      else {
        n->key = n->left->key;
        n->val = n->left->val;
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
  BstMap() : root(NULL) {}

  BstMap(const K _key, const V _val) { root = new Node(_key, _val); }

  BstMap(const BstMap & rhs) { root = copyHelp(root, rhs.root); }

  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      deleteHelp(root);
      root = NULL;
      root = copyHelp(root, rhs.root);
    }
    return *this;
  }
  virtual ~BstMap() { deleteHelp(root); }

  virtual void add(const K & key, const V & value) {
    if (root == NULL) {
      root = new Node(key, value);
      return;
    }

    Node * curr = root;
    int currCheck = 0;
    while (curr != NULL) {
      K currKey = curr->key;
      if (currKey == key) {
        curr->val = value;
        currCheck = 0;
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
      curr->right = new Node(key, value);
    else if (currCheck == -1)
      curr->left = new Node(key, value);
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    if (root == NULL) {
      throw std::invalid_argument("no element in the map\n");
    }

    Node * curr = root;
    while (curr != NULL) {
      K currKey = curr->key;
      if (currKey == key) {
        return curr->val;
      }
      else if (currKey < key) {
        curr = curr->right;
      }
      else if (currKey > key) {
        curr = curr->left;
      }
    }

    throw std::invalid_argument("cannot find the key in the map\n");
  }

  virtual void remove(const K & key) {
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
      K currKey = curr->key;
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
      std::cout << n->key << " " << n->val << std::endl;
      printHelp(n->left);
      printHelp(n->right);
    }
  }

 public:
  void printTree() { printHelp(root); }
};

#endif
