// /****************************************************************************************
// *  ListTest.c
// *  Tests functionality of List ADT
// *****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"



void AccessFunctions() {
   int a = 1;
   int b = 2;
   int c = 3;

   List L = newList();

   //test length
   assert(length(L)==0);
   append(L,&a);
   append(L,&a);
   append(L,&a);
   assert(length(L)==3);
   deleteFront(L);
   assert(length(L)==2);
   freeList(&L);
   printf("length() works!\n");  
   //test index
   L = newList();
   assert(index(L)==-1);
   append(L,&a);
   append(L,&a);
   moveBack(L);
   assert(index(L)==1);
   moveFront(L);
   assert(index(L)==0);
   deleteFront(L);
   assert(index(L)==-1);
   freeList(&L);
   printf("index() works!\n");
   //test front
   L = newList();
   append(L,&a);
   append(L,&b);
   assert(*(int*)front(L)==a);
   prepend(L,&c);
   assert(*(int*)front(L)==c);
   freeList(&L);
   printf("front() works!\n");
   //test back
   L = newList();
   append(L,&a);
   append(L,&b);
   assert(*(int*)back(L)==b);
   append(L,&c);
   assert(*(int*)back(L)==c);
   freeList(&L);
   printf("back() works!\n");
   //test get
   L = newList();
   append(L,&a);
   append(L,&b);
   append(L,&c);
   moveFront(L);
   assert(*(int*)get(L)==a);
   moveNext(L);
   assert(*(int*)get(L)==b);
   freeList(&L);
   printf("get() works!\n");
}
void ManipulationFunctions() {
   //test clear
   int a = 1;
   int b = 2;
   int c = 3;

   List L = newList();
   append(L,&a);
   append(L,&a);
   append(L,&a);
   moveBack(L);
   assert(length(L)==3);
   assert(index(L)==2);
   clear(L);
   assert(length(L)==0);
   assert(index(L)==-1);
   freeList(&L);
   printf("clear() works!\n");
   //test set
   L = newList();
   append(L,&a);
   append(L,&b);
   moveBack(L);
   assert(*(int*)get(L)==b);
   set(L,&c);
   assert(*(int*)get(L)==c);
   freeList(&L);
   printf("set() works!\n");
   //test moveFront
   L = newList();
   append(L,&a);
   append(L,&a);
   assert(index(L)==-1);
   moveFront(L);
   assert(index(L)==0);
   assert(*(int*)get(L)==a);
   moveFront(L);
   assert(index(L)==0);
   assert(*(int*)get(L)==a);
   freeList(&L);
   printf("moveFront() works!\n");
   //test moveBack
   L = newList();
   append(L,&a);
   append(L,&b);
   assert(index(L)==-1);
   moveBack(L);
   assert(index(L)==1);
   assert(*(int*)get(L)==b);
   moveBack(L);
   assert(index(L)==1);
   assert(*(int*)get(L)==b);
   freeList(&L);
   printf("moveBack() works!\n");
   //test movePrev
   L = newList();
   append(L,&a);
   append(L,&a);
   moveBack(L);
   assert(index(L)==1);
   movePrev(L);
   assert(index(L)==0);
   movePrev(L);
   assert(index(L)==-1);
   freeList(&L);
   printf("movePrev() works!\n");
   //test moveNext
   L = newList();
   append(L,&a);
   append(L,&a);
   moveFront(L);
   assert(index(L)==0);
   moveNext(L);
   assert(index(L)==1);
   moveNext(L);
   assert(index(L)==-1);
   freeList(&L);
   printf("moveNext() works!\n");
   //test prepend
   L = newList();
   append(L,&a);
   moveFront(L);
   assert(index(L)==0);
   prepend(L,&b);
   assert(index(L)==1);
   assert(*(int*)front(L)==b);
   freeList(&L);
   printf("prepend() works!\n");
   //test append
   L = newList();
   append(L,&a);
   moveFront(L);
   append(L,&b);
   assert(*(int*)back(L)==b);
   assert(length(L)==2);
   freeList(&L);
   printf("append() works!\n");
   //test insertBefore
   L = newList();
   append(L,&a);
   moveFront(L);
   insertBefore(L,&b);
   movePrev(L);
   assert(*(int*)get(L)==b);
   assert(length(L)==2);
   freeList(&L);
   printf("insertBefore() works!\n");
   //test insertAfter
   L = newList();
   append(L,&a);
   moveFront(L);
   insertAfter(L,&b);
   moveNext(L);
   assert(*(int*)get(L)==b);
   assert(length(L)==2);
   freeList(&L);
   printf("insertAfter() works!\n");
   //test deleteFront
   L = newList();
   append(L,&a);
   append(L,&b);
   append(L,&a);
   moveFront(L);
   assert(length(L)==3);
   assert(*(int*)front(L)==a);
   assert(index(L)==0);
   deleteFront(L);
   assert(length(L)==2);
   assert(*(int*)front(L)==b);
   assert(index(L)==-1);
   freeList(&L);
   printf("deleteFront() works!\n");
   //test deleteBack
   L = newList();
   append(L,&a);
   append(L,&b);
   append(L,&c);
   moveBack(L);
   assert(length(L)==3);
   assert(*(int*)back(L)==c);
   assert(index(L)==2);
   deleteBack(L);
   assert(length(L)==2);
   assert(*(int*)back(L)==b);
   assert(index(L)==-1);
   freeList(&L);
   printf("deleteBack() works!\n");
   //test delete
   L = newList();
   append(L,&a);
   append(L,&b);
   append(L,&c);
   moveFront(L);
   moveNext(L);
   assert(*(int*)front(L)==a);
   assert(*(int*)back(L)==c);
   assert(index(L)==1);
   assert(length(L)==3);
   delete(L);
   assert(*(int*)front(L)==a);
   assert(*(int*)back(L)==c);
   assert(index(L)==-1);
   assert(length(L)==2);
   freeList(&L);
   printf("delete() works!\n");

}



int main() {

   AccessFunctions();

   ManipulationFunctions();

   printf("All tests pass!\n");

   return 0;
}

