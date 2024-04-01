// /****************************************************************************************
// *  Matrix.h
// *  declare functions and construct the ADTs Entry and Matrix
// *****************************************************************************************/

#ifndef MATRIX_H
#define MATRIX_H

#include "List.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct EntryObj* Entry;
typedef struct MatrixObj* Matrix;

typedef struct EntryObj{
    double val;
    int column;
}EntryObj;

typedef struct MatrixObj{
    int size;
    int elements;
    List* entries;
    
} MatrixObj;


Matrix newMatrix(int n);

void freeMatrix(Matrix* pM);

int size(Matrix M);

int NNZ(Matrix M);

int equals(Matrix A, Matrix B);

void makeZero(Matrix M);

void changeEntry(Matrix M, int i, int j, double x);

void sumChangeEntry(Matrix M, int i, int j, double x);

void difChangeEntry(Matrix M, int i, int j, double x);

Matrix copy(Matrix A);

Matrix transpose(Matrix A);

Matrix scalarMult(double x, Matrix A);

Matrix sum(Matrix A, Matrix B);

Matrix diff(Matrix A, Matrix B);

Matrix product(Matrix A, Matrix B);

void printMatrix(FILE* out, Matrix M);
#endif
