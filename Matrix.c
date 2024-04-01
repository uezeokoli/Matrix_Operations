// /****************************************************************************************
// *  Ugonna Ezeokoli
// *  uezeokol
// *  2024 Winter CSE101 PA4 
// *  Matrix.c
// *  Defines functions for Matrix ADT
// *****************************************************************************************/


#include "Matrix.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
    Matrix new_matrix = malloc(sizeof(MatrixObj));  
    new_matrix->entries = (List *) calloc(n+1, sizeof(List));
    new_matrix->size = n;
    new_matrix->elements = 0;
    return new_matrix;
}


// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
    if(pM!=NULL && *pM!=NULL) { 
        Matrix M = *pM;
        makeZero(M);
        free(M->entries); 
        free(*pM);
        *pM = NULL;
    }
}


// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M){
    return M->size;
}


// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
    return M->elements;
}


// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){

    if (A->size != B->size){
        return false;
    }
    for (int i = 1; i <= A->size;i++){
        if (A->entries[i] == NULL){
            if (B->entries[i] != NULL){
                return false;
            }
        }
        if (B->entries[i] == NULL){
            if (A->entries[i] != NULL){
                return false;
            }
        }
        if (A->entries[i] != NULL){
            moveFront(A->entries[i]);
            moveFront(B->entries[i]);
            if (length(A->entries[i]) != length(B->entries[i])){
                return false;
            }
            while (index(A->entries[i])>=0){
                if((*(EntryObj*)get(A->entries[i])).val != (*(EntryObj*)get(B->entries[i])).val){
                    return false;
                }
                if((*(EntryObj*)get(A->entries[i])).column != (*(EntryObj*)get(B->entries[i])).column){
                    return false;
                }
                moveNext(A->entries[i]);
                moveNext(B->entries[i]);
            }
        }
    }
    return true;
}


// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
    if (M == NULL){
        fprintf(stderr,"Matrix Error: calling makeZero() when matrix is NULL\n");
        exit(EXIT_FAILURE);
    }
    M->elements = 0;
    for (int i = 1; i <= M->size;i++){
            if (M->entries[i] != NULL){
                if (length(M->entries[i]) != 0){
                    for (moveFront(M->entries[i]); index(M->entries[i]) >=0;moveNext(M->entries[i])){
                        free((EntryObj*)get(M->entries[i]));
                    }
                }
            }
        }
        for (int i = 1; i <= M->size; i++){
            freeList(&M->entries[i]);
        }
    
}


// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
    if (M == NULL){
        fprintf(stderr,"Matrix Error: calling changeEntry() when matrix is NULL\n");
        exit(EXIT_FAILURE);
    }
    if ((i<1 || i>size(M)) || (j<1 || j>size(M))){
        fprintf(stderr,"Matrix Error: calling changeEntry() on out of bound index\n");
        exit(EXIT_FAILURE);
    }
    //Insertion Sort
    if (M->entries[i]== NULL){              // if no entry in row
            if (x == 0){
                    return;
                }
            M->entries[i] = newList();
            Entry new_entry = malloc(sizeof(EntryObj));
            new_entry->column = j;
            new_entry->val = x;
            append(M->entries[i],new_entry);
            M->elements++;
        }
    else{

        for (moveBack(M->entries[i]); index(M->entries[i]) >=0;movePrev(M->entries[i])){
            // this condition finds the entry and changes value
            if((*(EntryObj*)get(M->entries[i])).column == j){
                if (x == 0){
                    free((EntryObj*)get(M->entries[i]));
                    delete(M->entries[i]);
                    M->elements--;
                    if (length(M->entries[i]) == 0){
                        freeList(&M->entries[i]); 
                    }
                    return;
                }
                (*(EntryObj*)get(M->entries[i])).val = x;
                return;
            }

            if((*(EntryObj*)get(M->entries[i])).column < j){
                if (x == 0){
                    return;
                }
                Entry new_entry = malloc(sizeof(EntryObj));
                new_entry->column = j;
                new_entry->val = x;
                insertAfter(M->entries[i],new_entry);
                M->elements++;
                break;
            }

            if(index(M->entries[i]) == 0){
                if (x == 0){
                    return;
                }
                Entry new_entry = malloc(sizeof(EntryObj));
                new_entry->column = j;
                new_entry->val = x;
                insertBefore(M->entries[i], new_entry);
                M->elements++;
                return;
            }
        }
    }
}


void sumChangeEntry(Matrix M, int i, int j, double x){
    if (M == NULL){
        fprintf(stderr,"Matrix Error: calling sumChangeEntry() when matrix is NULL\n");
        exit(EXIT_FAILURE);
    }
    if ((i<1 || i>size(M)) || (j<1 || j>size(M))){
        fprintf(stderr,"Matrix Error: calling sumChangeEntry() on out of bound index\n");
        exit(EXIT_FAILURE);
    }
    //Insertion Sort
    if (M->entries[i]== NULL){              // if no entry in row
            if (x == 0){
                    return;
                }
            M->entries[i] = newList();
            Entry new_entry = malloc(sizeof(EntryObj));
            new_entry->column = j;
            new_entry->val = x;
            append(M->entries[i],new_entry);
            M->elements++;
        }
    else{

        for (moveBack(M->entries[i]); index(M->entries[i]) >=0;movePrev(M->entries[i])){
            // this condition finds the entry and changes value

            if (length(M->entries[i]) == 0){
                Entry new_entry = malloc(sizeof(EntryObj));
                new_entry->column = j;
                new_entry->val = x;
                append(M->entries[i],new_entry);
                M->elements++;
                return;
            }

            if((*(EntryObj*)get(M->entries[i])).column == j){
                if (x == 0){
                    return;
                }
                if ((((*(EntryObj*)get(M->entries[i])).val + x)  < 0.00001) && (((*(EntryObj*)get(M->entries[i])).val + x)  > -0.00001)){
                    free((EntryObj*)get(M->entries[i]));
                    delete(M->entries[i]);
                    M->elements--;
                    if (length(M->entries[i]) == 0){
                        freeList(&M->entries[i]); 
                    }
                    return;
                }
                (*(EntryObj*)get(M->entries[i])).val += x;
                return;
            }

            if((*(EntryObj*)get(M->entries[i])).column < j){
                if (x == 0){
                    return;
                }
                Entry new_entry = malloc(sizeof(EntryObj));
                new_entry->column = j;
                new_entry->val = x;
                insertAfter(M->entries[i],new_entry);
                M->elements++;
                break;
            }

            if(index(M->entries[i]) == 0){
                if (x == 0){
                    return;
                }
                Entry new_entry = malloc(sizeof(EntryObj));
                new_entry->column = j;
                new_entry->val = x;
                insertBefore(M->entries[i], new_entry);
                M->elements++;
                return;
            }
        }
    }
}

void difChangeEntry(Matrix M, int i, int j, double x){
    if (M == NULL){
        fprintf(stderr,"Matrix Error: calling difChangeEntry() when matrix is NULL\n");
        exit(EXIT_FAILURE);
    }
    if ((i<1 || i>size(M)) || (j<1 || j>size(M))){
        fprintf(stderr,"Matrix Error: calling difChangeEntry() on out of bound index\n");
        exit(EXIT_FAILURE);
    }
    //Insertion Sort
    if (M->entries[i]== NULL){              // if no entry in row
            if (x == 0){
                    return;
                }
            M->entries[i] = newList();
            Entry new_entry = malloc(sizeof(EntryObj));
            new_entry->column = j;
            new_entry->val = -x;
            append(M->entries[i],new_entry);
            M->elements++;
        }
    else{
        for (moveBack(M->entries[i]); index(M->entries[i]) >=0;movePrev(M->entries[i])){
            // this condition finds the entry and changes value
            if (length(M->entries[i]) == 0){
                Entry new_entry = malloc(sizeof(EntryObj));
                new_entry->column = j;
                new_entry->val = -x;
                append(M->entries[i],new_entry);
                M->elements++;
                return;
            }
            if((*(EntryObj*)get(M->entries[i])).column == j){
                if (x == 0){
                    return;
                }
                if ((((*(EntryObj*)get(M->entries[i])).val - x)  < 0.00001) && (((*(EntryObj*)get(M->entries[i])).val - x)  > -0.00001)){
                    free((EntryObj*)get(M->entries[i]));
                    delete(M->entries[i]);
                    M->elements--;
                    if (length(M->entries[i]) == 0){
                        freeList(&M->entries[i]); 
                    }
                    return;
                }
                (*(EntryObj*)get(M->entries[i])).val -= x;
                return;
            }

            if((*(EntryObj*)get(M->entries[i])).column < j){
                if (x == 0){
                    return;
                }
                Entry new_entry = malloc(sizeof(EntryObj));
                new_entry->column = j;
                new_entry->val = -x;
                insertAfter(M->entries[i],new_entry);
                M->elements++;
                break;
            }

            if(index(M->entries[i]) == 0){
                if (x == 0){
                    return;
                }
                Entry new_entry = malloc(sizeof(EntryObj));
                new_entry->column = j;
                new_entry->val = -x;
                insertBefore(M->entries[i], new_entry);
                M->elements++;
                return;
            }
        }
    }
}


// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
    Matrix C = newMatrix(A->size);
    for (int i = 1; i <= A->size;i++){
        if (A->entries[i] != NULL){
            for (moveFront(A->entries[i]); index(A->entries[i]) >=0;moveNext(A->entries[i])){
                changeEntry(C,i,(*(EntryObj*)get(A->entries[i])).column, ((*(EntryObj*)get(A->entries[i])).val));
                
            }
        }
    }
    return C;
}


// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
    Matrix T = newMatrix(A->size);
    for (int i = 1; i <= A->size;i++){
        if (A->entries[i] != NULL){
            for (moveFront(A->entries[i]); index(A->entries[i]) >=0;moveNext(A->entries[i])){
                changeEntry(T,(*(EntryObj*)get(A->entries[i])).column,i, ((*(EntryObj*)get(A->entries[i])).val));
                
            }
        }
    }
    return T;
}


// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){

    Matrix S = newMatrix(A->size);
    for (int i = 1; i <= A->size;i++){
        if (A->entries[i] != NULL){
            for (moveFront(A->entries[i]); index(A->entries[i]) >=0;moveNext(A->entries[i])){
                changeEntry(S,i,(*(EntryObj*)get(A->entries[i])).column, ((*(EntryObj*)get(A->entries[i])).val)*x);
                
            }
        }
    }
    return S;
}


// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
    if (size(A) != size(B)){
        fprintf(stderr,"Matrix Error: calling sum() different sized matrices\n");
        exit(EXIT_FAILURE);
    }
    Matrix S = newMatrix(A->size);
    for (int i = 1; i <= A->size;i++){
        if (A->entries[i] != NULL){
            for (moveFront(A->entries[i]); index(A->entries[i]) >=0;moveNext(A->entries[i])){
                sumChangeEntry(S,i,(*(EntryObj*)get(A->entries[i])).column, ((*(EntryObj*)get(A->entries[i])).val));
                
            }
        }
        if (B->entries[i] != NULL){
            for (moveFront(B->entries[i]); index(B->entries[i]) >=0;moveNext(B->entries[i])){
                sumChangeEntry(S,i,(*(EntryObj*)get(B->entries[i])).column, ((*(EntryObj*)get(B->entries[i])).val));
                
            }
        }
    }
    return S;

}



// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
    if (size(A) != size(B)){
        fprintf(stderr,"Matrix Error: calling diff() different sized matrices\n");
        exit(EXIT_FAILURE);
    }
    Matrix S = newMatrix(A->size);
    for (int i = 1; i <= A->size;i++){
        if ((A->entries[i] != NULL) && (length(A->entries[i]) > 0)){
            for (moveFront(A->entries[i]); index(A->entries[i]) >=0;moveNext(A->entries[i])){
                sumChangeEntry(S,i,(*(EntryObj*)get(A->entries[i])).column, ((*(EntryObj*)get(A->entries[i])).val));
            }
        }
        if (B->entries[i] != NULL && (length(B->entries[i]) > 0)){
            for (moveFront(B->entries[i]); index(B->entries[i]) >=0;moveNext(B->entries[i])){
                difChangeEntry(S,i,(*(EntryObj*)get(B->entries[i])).column, ((*(EntryObj*)get(B->entries[i])).val));
                
            }
        }
    }
    return S;

}


// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
    if (size(A) != size(B)){
        fprintf(stderr,"Matrix Error: calling product() different sized matrices\n");
        exit(EXIT_FAILURE);
    }


    Matrix T = transpose(B);
    Matrix P = newMatrix(size(A));

    for (int i = 1; i<=size(A);i++){
        if (A->entries[i] == NULL){
            continue;
        }
        for (int j = 1; j <=size(A);j++){
            
            if (T->entries[j] == NULL){
                continue;
            }
            moveFront(A->entries[i]);
            moveFront(T->entries[j]);
            while (index(A->entries[i])!=-1 && index(T->entries[j])!=-1){
                if ((*(EntryObj*)get(A->entries[i])).column == (*(EntryObj*)get(T->entries[j])).column){
                    sumChangeEntry(P,i,j,(*(EntryObj*)get(A->entries[i])).val * (*(EntryObj*)get(T->entries[j])).val);
                    moveNext(A->entries[i]);
                    moveNext(T->entries[j]);
                }
                else if((*(EntryObj*)get(A->entries[i])).column < (*(EntryObj*)get(T->entries[j])).column){
                    moveNext(A->entries[i]);
                }
                else{
                    moveNext((T->entries[j]));
                }

            }
        }
    }
    freeMatrix(&T);
    return P;

}


// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
    if (M != NULL){
        for (int i = 1; i <= M->size;i++){
            if (M->entries[i] != NULL){
                if(length(M->entries[i]) != 0){
                    fprintf(out, "%d:", i);
                    for (moveFront(M->entries[i]); index(M->entries[i]) >=0;moveNext(M->entries[i])){
                        fprintf(out," (%d, %.1lf)",(*(EntryObj*)get(M->entries[i])).column, (*(EntryObj*)get(M->entries[i])).val);
                        
                    }
                    fprintf(out,"\n");
                }
            }
        }
    }

}