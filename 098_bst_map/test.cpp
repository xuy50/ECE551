#include <cstdlib>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>

#include "bstmap.h"

using namespace std;

int main() {
  BstMap<int, int> * m = new BstMap<int, int>;
  m->add(1, 1);
  cout << m->lookup(1) << endl;
  m->remove(1);
  try {
    cout << m->lookup(1) << endl;
  }
  catch (invalid_argument & e) {
    cout << e.what() << endl;
  }

  m->add(1, 1);
  m->add(2, 2);
  m->add(-1, -1);
  cout << m->lookup(-1) << endl;
  m->remove(-1);
  try {
    cout << m->lookup(-1) << endl;
  }
  catch (invalid_argument & e) {
    cout << e.what() << endl;
  }
  cout << m->lookup(1) << endl;
  m->remove(1);
  try {
    cout << m->lookup(1) << endl;
  }
  catch (invalid_argument & e) {
    cout << e.what() << endl;
  }
  cout << m->lookup(2) << endl;
  m->add(2, 0);
  cout << m->lookup(2) << endl;
  m->add(2, 2);
  cout << m->lookup(2) << endl;

  BstMap<int, int> m1(1, 2);
  cout << m1.lookup(1) << endl;
  m1.add(3, 3);
  m1.add(5, 5);
  m1.add(4, 4);

  BstMap<int, int> m2 = (m1);
  try {
    cout << m2.lookup(1) << endl;
    cout << m2.lookup(5) << endl;
    cout << m2.lookup(4) << endl;
  }
  catch (invalid_argument & e) {
    cout << e.what() << endl;
  }

  m1.add(-4, -4);
  m1.add(100, 100);
  m1.add(50, 50);
  m1.add(45, 45);
  m1.add(40, 40);
  //m1.add(55, 55);
  m1.add(39, 39);
  m1.add(41, 41);

  m1.printTree();

  m1.remove(1);
  try {
    cout << m1.lookup(1) << endl;
  }
  catch (invalid_argument & e) {
    cout << e.what() << endl;
  }
  m1.printTree();

  return EXIT_SUCCESS;
}
