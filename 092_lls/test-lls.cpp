#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "ll.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    LinkedList<int> il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    LinkedList<int> il;
    il.addFront(0);
    //assert(il.head != NULL);
    assert(il[0] == 0);
    assert(il.head->data == 0);
    assert(il.tail->data == 0);
    assert(il.head->prev == NULL);
    assert(il.head->next == NULL);
    assert(il.tail->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.getSize() == 1);

    il.addFront(1);
    assert(il[0] == 1);
    assert(il.head->data == 1);
    assert(il.head->next != NULL);
    assert(il.head->next->data == 0);
    assert(il.head->prev == NULL);
    assert(il.tail->data == 0);
    assert(il.tail->next == NULL);
    assert(il.tail->prev != NULL);
    assert(il.tail->prev->data == 1);
    assert(il.getSize() == 2);

    for (int i = 2; i < 100; i++) {
      il.addFront(i);
      assert(il[0] == i);
      assert(il.head->data == i);
      assert(il.tail->data == 0);
      assert(il.getSize() == i + 1);
    }
    LinkedList<int> nil1(il);
    nil1.addFront(1);
    nil1.tail->data = 1;
    assert(nil1[0] == 1);
    assert(nil1[100] == 1);
    assert(nil1.head->data == 1);
    assert(nil1.tail->data == 1);
    assert(nil1.getSize() == 101);
    assert(il[0] == 99);
    assert(il[99] == 0);
    assert(il.getSize() == 100);
    assert(il.head->data == 99);
    assert(il.tail->data == 0);

    LinkedList<int> nil2 = il;
    nil2.addFront(1);
    nil2.tail->data = 1;
    assert(nil2[0] == 1);
    assert(nil2[100] == 1);
    assert(nil2.head->data == 1);
    assert(nil2.tail->data == 1);
    assert(nil2.getSize() == 101);
    assert(il[0] == 99);
    assert(il[99] == 0);
    assert(il.getSize() == 100);
    assert(il.head->data == 99);
    assert(il.tail->data == 0);
  }
  // many more tester methods
  void testAddBack() {
    LinkedList<int> il;
    il.addBack(0);
    assert(il.head != NULL);
    assert(il[0] == 0);
    assert(il.head->data == 0);
    assert(il.tail->data == 0);
    assert(il.head->prev == NULL);
    assert(il.head->next == NULL);
    assert(il.tail->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.getSize() == 1);

    il.addBack(1);
    assert(il[0] == 0);
    assert(il[1] == 1);
    assert(il.head->data == 0);
    assert(il.head->next != NULL);
    assert(il.head->next->data == 1);
    assert(il.head->prev == NULL);
    assert(il.tail->data == 1);
    assert(il.tail->next == NULL);
    assert(il.tail->prev != NULL);
    assert(il.tail->prev->data == 0);
    assert(il.getSize() == 2);

    for (int i = 2; i < 100; i++) {
      il.addBack(i);
      assert(il[i] == i);
      assert(il.head->data == 0);
      assert(il.tail->data == i);
      assert(il.getSize() == i + 1);
    }
    LinkedList<int> nil1(il);
    nil1.addBack(1);
    nil1.head->data = 1;
    assert(nil1[0] == 1);
    assert(nil1[100] == 1);
    assert(nil1.head->data == 1);
    assert(nil1.tail->data == 1);
    assert(nil1.getSize() == 101);
    assert(il[0] == 0);
    assert(il[99] == 99);
    assert(il.head->data == 0);
    assert(il.tail->data == 99);
    assert(il.getSize() == 100);

    LinkedList<int> nil2 = il;
    nil2.addBack(1);
    nil2.head->data = 1;
    assert(nil2[0] == 1);
    assert(nil2[100] == 1);
    assert(nil2.head->data == 1);
    assert(nil2.tail->data == 1);
    assert(nil2.getSize() == 101);
    assert(il[0] == 0);
    assert(il[99] == 99);
    assert(il.head->data == 0);
    assert(il.tail->data == 99);
    assert(il.getSize() == 100);

    nil1 = il;
    assert(nil1[0] == 0);
    assert(nil1[99] == 99);
    assert(nil1.head->data == 0);
    assert(nil1.tail->data == 99);
    assert(nil1.getSize() == 100);
  }

  void testRemove() {
    LinkedList<int> il;
    il.addBack(0);
    assert(il.head != NULL);
    assert(il[0] == 0);
    assert(il.head->data == 0);
    assert(il.tail->data == 0);
    assert(il.head->prev == NULL);
    assert(il.head->next == NULL);
    assert(il.tail->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.getSize() == 1);

    assert(il.remove(0) == true);
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);

    il.addFront(0);
    il.addBack(1);
    assert(il[0] == 0);
    assert(il[1] == 1);
    assert(il.head->data == 0);
    assert(il.head->next != NULL);
    assert(il.head->next->data == 1);
    assert(il.head->prev == NULL);
    assert(il.tail->data == 1);
    assert(il.tail->next == NULL);
    assert(il.tail->prev != NULL);
    assert(il.tail->prev->data == 0);
    assert(il.getSize() == 2);

    assert(il.remove(2) == false);
    assert(il[0] == 0);
    assert(il[1] == 1);
    assert(il.head->data == 0);
    assert(il.head->next != NULL);
    assert(il.head->next->data == 1);
    assert(il.head->prev == NULL);
    assert(il.tail->data == 1);
    assert(il.tail->next == NULL);
    assert(il.tail->prev != NULL);
    assert(il.tail->prev->data == 0);
    assert(il.getSize() == 2);

    il.remove(1);
    assert(il.head != NULL);
    assert(il[0] == 0);
    assert(il.head->data == 0);
    assert(il.tail->data == 0);
    assert(il.head->prev == NULL);
    assert(il.head->next == NULL);
    assert(il.tail->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.getSize() == 1);

    il.addFront(1);
    il.remove(1);
    assert(il.head != NULL);
    assert(il[0] == 0);
    assert(il.head->data == 0);
    assert(il.tail->data == 0);
    assert(il.head->prev == NULL);
    assert(il.head->next == NULL);
    assert(il.tail->prev == NULL);
    assert(il.tail->next == NULL);
    assert(il.getSize() == 1);

    il.addBack(1);
    il.addBack(2);
    il.remove(1);
    assert(il[0] == 0);
    std::cout << il.size << " " << il[1] << std::endl;
    assert(il[1] == 2);
    assert(il.head->data == 0);
    assert(il.head->next != NULL);
    assert(il.head->next->data == 2);
    assert(il.head->prev == NULL);
    assert(il.tail->data == 2);
    assert(il.tail->next == NULL);
    assert(il.tail->prev != NULL);
    assert(il.tail->prev->data == 0);
    assert(il.getSize() == 2);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  // write calls to your other test methods here
  t.testAddBack();
  t.testRemove();
  return EXIT_SUCCESS;
}
