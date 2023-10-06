#include <cstdlib>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>

#include "bstset.h"

using namespace std;

int main() {
  BstSet<int> * m = new BstSet<int>;
  m->add(1);
  cout << m->contains(1) << endl;
  m->remove(1);
  cout << m->contains(1) << endl;

  m->add(1);
  m->add(2);
  m->add(-1);
  cout << m->contains(-1) << endl;
  m->remove(-1);
  cout << m->contains(-1) << endl;
  cout << m->contains(1) << endl;
  m->remove(1);
  cout << m->contains(1) << endl;
  cout << m->contains(2) << endl;
  m->add(2);
  cout << m->contains(2) << endl;
  m->remove(2);
  cout << m->contains(2) << endl;
  m->add(2);
  cout << m->contains(2) << endl;

  BstSet<int> m1(1);
  cout << m1.contains(1) << endl;
  m1.add(3);
  m1.add(5);
  m1.add(4);

  BstSet<int> m2 = (m1);
  cout << m2.contains(1) << endl;
  cout << m2.contains(5) << endl;
  cout << m2.contains(4) << endl;

  m1.add(-4);
  m1.add(100);
  m1.add(50);
  m1.add(45);
  m1.add(40);
  //m1.add(55);
  m1.add(39);
  m1.add(41);

  m1.printTree();

  m1.remove(1);
  cout << m1.contains(1) << endl;
  m1.printTree();

  return EXIT_SUCCESS;
}
