// /****************************************************************************************
// *  List.c
// *  Defines functions for List ADT
// *****************************************************************************************/

#include "List.h"

#include <assert.h>
#include <stdlib.h>
//#include <string.h>
#include <stdio.h>
#include <stdbool.h>


// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(void* num){
   Node N = malloc(sizeof(NodeObj));
   assert( N!=NULL );
   N->val = num; 
   N->next = NULL;
   N->prev = NULL;
   return(N);
}
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}
List newList(void){ // Creates and returns a new empty List.
    List new_list = malloc(sizeof(ListObj));
    new_list->size = 0;
    new_list->index = -1;
    new_list->front = NULL;
    new_list->back = NULL;
    new_list->cursor = NULL;
    return new_list;
}
void freeList(List* pL){ // Frees all heap memory associated with *pL, and sets
 // *pL to NULL.
// Access functions -----------------------------------------------------------
if(pL!=NULL && *pL!=NULL) { 
    clear(*pL);
    free(*pL);
    *pL = NULL;
   }
} 
int length(List L){ // Returns the number of elements in L.
    return L->size;
}
int index(List L){ // Returns index of cursor element if defined, -1 otherwise.
    return L->index;
}
void* front(List L){ // Returns front element of L. Pre: length()>0
    if( L==NULL ){
      fprintf(stderr,"List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if( length(L) == 0 ){
      fprintf(stderr,"List Error: calling front() on an empty List\n");
      exit(EXIT_FAILURE);
    }
    return L->front->val;

}
void* back(List L){ // Returns back element of L. Pre: length()>0
    if( L==NULL ){
      fprintf(stderr,"List Error: calling back() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if( length(L) == 0 ){
      fprintf(stderr,"List Error: calling back() on an empty List\n");
      exit(EXIT_FAILURE);
    }
    return L->back->val;
}
void* get(List L){ // Returns cursor element of L. Pre: length()>0, index()>=0
    if( L==NULL ){
      fprintf(stderr,"List Error: calling get() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if( length(L) == 0 ){
      fprintf(stderr,"List Error: calling get() on an empty List\n");
      exit(EXIT_FAILURE);
    }
    if( index(L) < 0 ){
      fprintf(stderr,"List Error: calling get() with undefined cursor\n");
      exit(EXIT_FAILURE);
    }
    return L->cursor->val;
}

void clear(List L){ // Resets L to its original empty state.

    while( L->front != NULL ) { 
         deleteFront(L); 
    }
    
}
void set(List L, void* x){ // Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
    if( L==NULL ){
      fprintf(stderr,"List Error: calling set() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if( length(L) == 0 ){
      fprintf(stderr,"List Error: calling set() on an empty List\n");
      exit(EXIT_FAILURE);
    }
    if( index(L) < 0 ){
      fprintf(stderr,"List Error: calling set() with undefined cursor\n");
      exit(EXIT_FAILURE);
    }
    L->cursor->val = x;
    
}
void moveFront(List L){ // If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
    if (length(L)>0){
        L->cursor = L->front;
        L->index = 0;
    }
}
void moveBack(List L){ // If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
    if (length(L)>0){
        L->cursor = L->back;
        L->index = length(L)-1;
    }
}
void movePrev(List L){ // If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
    if (L->cursor != NULL){
        if (L->cursor->prev != NULL){
            L->cursor = L->cursor->prev;
            L->index--;
        }
        else{
            L->cursor = NULL;
            L->index = -1;
        }
    }
}
void moveNext(List L){ // If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing
    if (L->cursor != NULL){
        if (L->cursor->next != NULL){
            L->cursor = L->cursor->next;
            L->index++;
        }
        else{
            L->cursor = NULL;
            L->index = -1;
        }
    }
}
void prepend(List L, void* x){ // Insert new element into L. If L is non-empty,
 // insertion takes place before front element.
    if (L->size == 0){
        L->size++;
        L->front = L->back = newNode(x);
    }
    else{
        if (index(L)!= -1){
            L->index++;
        }
        L->size++;
        Node new_item = newNode(x);
        new_item->next = L->front;
        L->front->prev = new_item;
        L->front = L->front->prev;
    }

}
void append(List L, void* x){ // Insert new element into L. If L is non-empty,
 // insertion takes place after back element.
 
    if (L->size == 0){
        L->size++;
        L->front = L->back = newNode(x);
    }
    
    else{
        L->size++;
        Node new_item = newNode(x);
        new_item->prev = L->back;
        L->back->next = new_item;
        L->back = L->back->next;
    }
}
void insertBefore(List L, void* x){ // Insert new element before cursor.
// Pre: length()>0, index()>=0
    if( L==NULL ){
      fprintf(stderr,"List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if( length(L) == 0 ){
      fprintf(stderr,"List Error: calling insertBefore() on an empty List\n");
      exit(EXIT_FAILURE);
    }
    if( index(L) < 0 ){
      fprintf(stderr,"List Error: calling insertBefore() with undefined cursor\n");
      exit(EXIT_FAILURE);
    }


    L->size++;
    L->index++;
    Node new_item = newNode(x);
    if (L->cursor->prev != NULL){
        new_item->next = L->cursor;
        new_item->prev = L->cursor->prev;
        L->cursor->prev->next = new_item;
        L->cursor->prev = new_item;
    } 
    else{
        new_item->next = L->cursor;
        L->cursor->prev = new_item;
        L->front = L->cursor->prev;
    }

}
void insertAfter(List L, void* x){ // Insert new element after cursor.
 // Pre: length()>0, index()>=0

    if( L==NULL ){
      fprintf(stderr,"List Error: calling insertAfter() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if( length(L) == 0 ){
      fprintf(stderr,"List Error: calling insertAfter() on an empty List\n");
      exit(EXIT_FAILURE);
    }
    if( index(L) < 0 ){
      fprintf(stderr,"List Error: calling insertAfter() with undefined cursor\n");
      exit(EXIT_FAILURE);
    }


    L->size++;
    Node new_item = newNode(x);
    if (L->cursor->next != NULL){
        new_item->prev = L->cursor;
        new_item->next = L->cursor->next;
        L->cursor->next->prev = new_item;
        L->cursor->next = new_item;
    } 
    else{
        new_item->prev = L->cursor;
        L->cursor->next = new_item;
        L->back = L->cursor->next;
    }
    
}
void deleteFront(List L){ // Delete the front element. Pre: length()>0

    if( L==NULL ){
      fprintf(stderr,"List Error: calling deleteFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if( length(L) == 0 ){
      fprintf(stderr,"List Error: calling deleteFront() on an empty List\n");
      exit(EXIT_FAILURE);
    }
    
    L->size--;
    if (L->size == 0){ 
        L->index = -1;
        freeNode(&L->front);
        L->front = L->back = NULL;
    }
    else{
        L->index--;
        Node new_front = L->front->next;
        new_front->prev = NULL;
        L->front->next = NULL;
        if (L->cursor == L->front){
            L->cursor = NULL;
            L->index = -1;
        }
        freeNode(&L->front);
        L->front = new_front; 
    }   
}
void deleteBack(List L){ // Delete the back element. Pre: length()>0


    if( L==NULL ){
      fprintf(stderr,"List Error: calling deleteBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if( length(L) == 0 ){
      fprintf(stderr,"List Error: calling deleteBack() on an empty List\n");
      exit(EXIT_FAILURE);
    }


    L->size--;
    if (L->size == 0){
        L->index = -1;
        freeNode(&L->back);
        L->front = L->back = NULL;
    }
    else{
        Node new_back = L->back->prev;
        new_back->next = NULL;
        L->back->prev = NULL;
        if (L->cursor == L->back){
            L->cursor =  NULL;
            L->index = -1;
        }
        freeNode(&L->back);
        L->back = new_back; 
    }

}
void delete(List L){ // Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0
// Other operations -----------------------------------------------------------

    if( L==NULL ){
      fprintf(stderr,"List Error: calling delete() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if( length(L) == 0 ){
      fprintf(stderr,"List Error: calling delete() on an empty List\n");
      exit(EXIT_FAILURE);
    }
    if( index(L) < 0 ){
      fprintf(stderr,"List Error: calling delete() with undefined cursor\n");
      exit(EXIT_FAILURE);
    }


    if (L->size == 1){
        L->size--;
        freeNode(&L->front);
        L->front = L->back = L->cursor = NULL;
    }
    else{
        if (L->cursor == L->front){
            deleteFront(L);
        }
        else if (L->cursor == L->back){
            deleteBack(L);
        }
        else{
            L->size--;
            L->cursor->prev->next = L->cursor->next;
            L->cursor->next->prev = L->cursor->prev;
            freeNode(&L->cursor);
            L->cursor = NULL;
            L->index = -1;
        }
    }
}





