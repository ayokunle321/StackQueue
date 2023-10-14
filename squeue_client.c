#include "squeue.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>


int main()
{
  Squeue *s1 = NULL;
  initSqueue(&s1);
  //Squeue should be empty
  assert(isEmpty(s1));
  addFront(s1, "aaaaaaaaaaaaaaaaaaaaaaa");
  //We just added "aaaaaaaaaaaaaaaaaaaaaaa", so it shouldn't be empty
  assert(!isEmpty(s1));
  addBack(s1, "bbbbbbbbbbbbbbbbbbbb!");
  //We should have "aaaaaaaaaaaaaaaaaaaaaaa", "bbbbbbbbbbbbbbbbbbbb!" in the Squeue in that order.
  assert(strcmp(peekFront(s1), "aaaaaaaaaaaaaaaaaaaaaaa") == 0);
  assert(strcmp(peekBack(s1), "bbbbbbbbbbbbbbbbbbbb!") == 0);
  //We are going to merge "aaaaaaaaaaaaaaaaaaaaaaa" with "bbbbbbbbbbbbbbbbbbbb!"
  mergeFront(s1, 'f');
  assert(strcmp(peekFront(s1), "aaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbb!") == 0);
  //We have only one element so the front and back of the squeue should be equal
  assert(strcmp(peekFront(s1), peekBack(s1)) == 0);
  addFront(s1, "Hola");
  addBack(s1, "Mundo!");
  // this print call should print
    //squeue is:
    //  Hola
    //  aaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbb
    //  Mundo!
  print(s1, 'f');
  reverse(s1);//we now reversed the elements in the stack
  assert(strcmp(peekFront(s1), "Mundo!") == 0);
  assert(strcmp(peekBack(s1), "Hola") == 0);
  // We are printing the stack in reverse order so we should get:
    //squeue is:
    //  Hola
    //  aaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbb
    //  Mundo!


  print(s1, 'r');
  leaveFront(s1);
  assert(strcmp(peekFront(s1), "aaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbb!") == 0);
  nuke(s1);
  //We just nuked our Squeue, so it should be empty
  assert(isEmpty(s1));
  destroySqueue(&s1);
  //After destroying the stack, s1 must be NULL
  assert(s1 == NULL);
  return 0;
  
}



