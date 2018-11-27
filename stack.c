#include "stack.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

/**
 * Creates a new stack and allocates it in the memory using the given size.
 * @param elementSize the size of the stack to be allocated.
 * @return a new allocated stack.
 */
Stack* stackAlloc(size_t elementSize)
{
  Stack* stack = (Stack*)malloc(sizeof(Stack));
  stack->_top = NULL;
  stack->_elementSize = elementSize;
  return stack;
}


/**
 * receives a pointer to a stack and frees it from the memory.
 * @param stack The stack to be freed.
 */
void freeStack(Stack** stack)
{
  Node* p1;
  Node* p2;
  if (!(*stack == NULL))
  {
      p1 = (*stack)->_top;
      while(p1)
      {
          p2 = p1;
          p1 = p1->_next;
          free(p2->_data);
          free(p2);
      }
      free(*stack);
      *stack = NULL;
  }
}

/**
 * Pushes a given value to a given stack.
 * @param stack The stack were the value will be pushed.
 * @param data The data to be pushed to the stack.
 */
void push(Stack* stack, void *data)
{
  //you should check allocation success
  Node* node = (Node*)malloc(sizeof(Node));
  node->_data = malloc(stack->_elementSize);
  memcpy(node->_data, data, stack->_elementSize);
  node->_next = stack->_top;
  stack->_top = node;
}


/**
 * Pops a value from a given stack, saves the value to a given destination and frees it from the memory.
 * @param stack The stack that will be popped.
 * @param headData The destination were the value popped value will be saved.
 */
void pop(Stack* stack, void *headData) 
{
  assert(stack != NULL);
  if(stack->_top == NULL)
  {
      fprintf(stderr, "The stack is empty\n");
      return;
  }

  Node *node = stack->_top;
  memcpy(headData, node->_data, stack->_elementSize);
  stack->_top = node->_next;  
  free(node->_data);
  free(node);
}


/**
 * Checks if a given stack is empty.
 * @param stack The stack to be checked.
 * @return true if the stack is empty, false otherwise.
 */
int isEmptyStack(Stack* stack) 
{
  assert(stack != NULL); 
  return stack->_top == NULL; 
}
