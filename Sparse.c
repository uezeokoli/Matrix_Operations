// /****************************************************************************************
// *  Sparse.c
// *  Displays result of matrix operations of two matrices
// *****************************************************************************************/

#include "Matrix.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[]){
    if (argc != 3){
        fprintf(stderr, "Invalid number of command line arguments\n");
        exit(EXIT_FAILURE);
    }
    FILE *output = fopen(argv[2],"w");
    FILE *input = fopen(argv[1], "r");
    if (input == NULL){
        fclose(output);
        fprintf(stderr, "Invalid file\n");
        exit(EXIT_FAILURE);
    }

    char str_size[100];
    char str_a_nnz[100];
    char str_b_nnz[100];
    fscanf(input, "%s", str_size);
    fscanf(input, "%s", str_a_nnz);
    fscanf(input, "%s", str_b_nnz);
    int size = atoi(str_size);
    int a_nnz = atoi(str_a_nnz);
    int b_nnz = atoi(str_b_nnz);

    Matrix A = newMatrix(size);
    Matrix B = newMatrix(size);

    char str_row[100];
    char str_col[100];
    char str_val[100];
    int row;
    int col;
    double val;
    //build A matrix
    for(int i = 0; i < a_nnz; i++){
        fscanf(input, "%s", str_row);
        fscanf(input, "%s", str_col);
        fscanf(input, "%s", str_val);
        row = atoi(str_row);
        col = atoi(str_col);
        val = atof(str_val);
        changeEntry(A, row,col,val);
    }
    // build B matrix
    for(int i = 0; i < b_nnz; i++){
        fscanf(input, "%s", str_row);
        fscanf(input, "%s", str_col);
        fscanf(input, "%s", str_val);
        row = atoi(str_row);
        col = atoi(str_col);
        val = atof(str_val);
        changeEntry(B, row,col,val);
    }
    
    fprintf(output,"A has %d non-zero entries:\n", NNZ(A));
    printMatrix(output, A);
    fprintf(output,"\n");

    fprintf(output,"B has %d non-zero entries:\n", NNZ(B));
    printMatrix(output, B);
    fprintf(output,"\n");

    Matrix Scalar = scalarMult(1.5,A);
    fprintf(output,"(1.5)*A =\n");
    printMatrix(output, Scalar);
    fprintf(output,"\n");

    Matrix sum1 = sum(A,B);
    fprintf(output,"A+B =\n");
    printMatrix(output, sum1);
    fprintf(output,"\n");

    Matrix sum2 = sum(A,A);
    fprintf(output,"A+A =\n");
    printMatrix(output, sum2);
    fprintf(output,"\n");

    Matrix diff1 = diff(B,A);
    fprintf(output,"B-A =\n");
    printMatrix(output, diff1);
    fprintf(output,"\n");\

    Matrix diff2 = diff(A,A);
    fprintf(output,"A-A =\n");
    printMatrix(output, diff2);
    fprintf(output,"\n");

    Matrix tran = transpose(A);
    fprintf(output,"Transpose(A) =\n");
    printMatrix(output, tran);
    fprintf(output,"\n");

    Matrix prod1 = product(A,B);
    fprintf(output,"A*B =\n");
    printMatrix(output, prod1);
    fprintf(output,"\n");

    Matrix prod2 = product(B,B);
    fprintf(output,"B*B =\n");
    printMatrix(output, prod2);
    fprintf(output,"\n");

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&Scalar);
    freeMatrix(&sum1);
    freeMatrix(&sum2);
    freeMatrix(&diff1);
    freeMatrix(&diff2);
    freeMatrix(&tran);
    freeMatrix(&prod1);
    freeMatrix(&prod2);


    fclose(output);
    fclose(input);

}
