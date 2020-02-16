/*
 * Implementation of functions to push and pop
 *   items from a linked list.
 *
 * Functions require the some or all of the following inputs:
 *   - Reference of pointer to the head of the list
 *   - Value to add (for push operations)
 *   - Size of object adding to linked list (for push operations)
 *
 * Author: Thomas Maher
 * Modified: 2/16/2020
 *
 */

 #include <stdlib.h>

struct LLNode {
  void* data;
  struct LLNode* next;
} LLNode;

void LLpushFront(struct LLNode** head, void* newVal, size_t dataSize) {
  struct LLNode* newNode = (struct LLNode*) malloc(sizeof(struct LLNode));

  newNode->data = malloc(dataSize);
  newNode->data = newVal;
  newNode->next = (*head);

  (*head) = newNode;
}

void LLpush(struct LLNode** head, void* newVal, size_t dataSize) {
  if(*head == NULL) {
    (*head) = (struct LLNode*) malloc(sizeof(struct LLNode));
    (*head)->data = malloc(dataSize);
    (*head)->data = newVal;
    (*head)->next = NULL;
    return;
  }
  struct LLNode* currNode = (*head);

  while(currNode->next != NULL)
    currNode = currNode->next;

  currNode->next = (struct LLNode*) malloc(sizeof(struct LLNode));
  currNode->next->data = malloc(dataSize);
  currNode->next->data = newVal;
  currNode->next->next = NULL;
}

void* LLpop(struct LLNode** head) {
  void* rv = NULL;
  struct LLNode* nextNode = NULL;

  if(*head == NULL)
    return NULL;

  nextNode = (*head)->next;
  rv = (*head)->data;
  //free((*head)->data);
  free(*head);
  (*head) = nextNode;

  return rv;
}

void* LLpopBack(struct LLNode** head) {
  void* rv;
  if((*head) == NULL)
    return NULL;
  else if((*head)->next == NULL) {
    rv = (*head)->data;
    free((*head));
    //free((*head)->data);
    return rv;
  }

  struct LLNode* currNode = (*head);
  while(currNode->next->next != NULL)
    currNode = currNode->next;

  rv = currNode->next->data;
  //free(currNode->next->data);
  free(currNode->next);
  currNode->next = NULL;

  return rv;
}
