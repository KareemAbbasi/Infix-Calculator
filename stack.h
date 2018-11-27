#ifndef STACK_H
#define STACK_H

#include <stdlib.h>


/**
 * Struct for Node.
 */
typedef struct Node
{
  void * _data; // pointer to anything
  struct Node * _next;
} Node;


/**
 * Struct for stack.
 */
typedef struct Stack
{
  Node * _top;
  size_t _elementSize;    // we need that for memcpy
} Stack;

/**
 * Creates a new stack and allocates it in the memory using the given size.
 * @param elementSize the size of the stack to be allocated.
 * @return a new allocated stack.
 */
Stack* stackAlloc(size_t elementSize);


/**
 * receives a pointer to a stack and frees it from the memory.
 * @param stack The stack to be freed.
 */
void freeStack(Stack** stack);


/**
 * Pushes a given value to a given stack.
 * @param stack The stack were the value will be pushed.
 * @param data The data to be pushed to the stack.
 */
void push(Stack* stack, void *data);


/**
 * Pops a value from a given stack, saves the value to a given destination and frees it from the memory.
 * @param stack The stack that will be popped.
 * @param headData The destination were the value popped value will be saved.
 */
void pop(Stack* stack, void *headData);


/**
 * Checks if a given stack is empty.
 * @param stack The stack to be checked.
 * @return true if the stack is empty, false otherwise.
 */
int isEmptyStack(Stack* stack);

#endif
