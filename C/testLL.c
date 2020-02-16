/*
 * Script that shows an example of how to create and run
 *   operations on a linked list from LinkedList.h
 *
 * Author: Thomas Maher
 * Modified: 2/16/2020
 */


#include "LinkedList.h"
#include <stdio.h>

int main() {
  struct LLNode* test = NULL;
  unsigned int_size = sizeof(int);
  int arr[] = {10, 20, 30, 40, 50};
  for(int i=0; i<5; ++i) {
    LLpush(&test, &arr[i], int_size);
    // LLpushFront(&test, &arr[i], int_size);
    printf("Pushed %d\n", arr[i]);
  }

  for(int i=0; i<5; ++i) {
    int* popped = LLpop(&test);
    // int* popped = LLpopBack(&test);
    printf("Popped %d\n", *popped);
  }
}
