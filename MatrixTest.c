// /****************************************************************************************
// *  MatrixTest.c
// *  Tests functionality of Matrix ADT
// *****************************************************************************************/
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"

void TestFunctions(){
   //Test size()
   Matrix M = newMatrix(20);
   assert(size(M) == 20);
   freeMatrix(&M);
   printf("size() works!\n");
   //Test NNZ()
   M = newMatrix(20);
   assert(NNZ(M) == 0);
   changeEntry(M,2,3,5);
   changeEntry(M,3,2,5);
   assert(NNZ(M) == 2);
   freeMatrix(&M);
   printf("NNZ() works!\n");
   //Test equals()
   Matrix A = newMatrix(20);
   Matrix B = newMatrix(20);
   assert(equals(A,B));
   changeEntry(A,2,3,5);
   changeEntry(A,3,2,5);
   changeEntry(B,2,3,5);
   changeEntry(B,3,2,5);
   assert(equals(A,B));
   freeMatrix(&A);
   freeMatrix(&B);
   printf("equals() works!\n");
   //Test makeZero
   Matrix Z = newMatrix(20);
   M = newMatrix(20);
   assert(equals(Z,M));
   changeEntry(M,2,3,5);
   changeEntry(M,3,2,5);
   assert(!equals(Z,M));
   makeZero(M);
   assert(equals(Z,M));
   freeMatrix(&Z);
   freeMatrix(&M);
   printf("makeZero() works!\n");
   //Test changeEntry()
   M = newMatrix(20);
   assert(NNZ(M)==0);
   changeEntry(M,2,3,5);
   changeEntry(M,3,2,5);
   assert(NNZ(M)!=0);
   freeMatrix(&M);
   printf("changeEntry() works!\n");  
   //Test copy()
   M = newMatrix(20);
   changeEntry(M,2,3,5);
   changeEntry(M,3,2,5);
   A = copy(M);
   assert(equals(M,A));
   freeMatrix(&A);
   freeMatrix(&M);
   printf("copy() works!\n");
   //Test transpose()
   M = newMatrix(20);
   changeEntry(M,2,3,5);
   changeEntry(M,3,2,5);
   A = transpose(M);
   B = newMatrix(20);
   changeEntry(B,3,2,5);
   changeEntry(B,2,3,5);
   assert(equals(A,B));
   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&M);
   printf("transpose() works!\n");
   //Test scalarMult()
   M = newMatrix(20);
   changeEntry(M,2,3,5);
   changeEntry(M,3,2,5);
   A = scalarMult(2,M);
   B = newMatrix(20);
   changeEntry(B,2,3,10);
   changeEntry(B,3,2,10);
   assert(equals(A,B));
   freeMatrix(&M);
   freeMatrix(&A);
   freeMatrix(&B);
   printf("scalarMult() works!\n");
   //Test sum()
   M = newMatrix(20);
   changeEntry(M,2,3,5);
   A = newMatrix(20);
   changeEntry(A,2,3,5);
   B = sum(A,M);
   Z = newMatrix(20);
   changeEntry(Z,2,3,10);
   assert(equals(B,Z));
   freeMatrix(&M);
   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&Z);
   printf("sum() works!\n");
   //Test diff()
   M = newMatrix(20);
   changeEntry(M,2,3,5);
   A = newMatrix(20);
   changeEntry(A,2,3,5);
   B = diff(A,M);
   Z = newMatrix(20);
   assert(equals(B,Z));
   freeMatrix(&M);
   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&Z);
   printf("diff() works!\n");
   //Test product()
   M = newMatrix(1);
   changeEntry(M,1,1,3);
   A = newMatrix(1);
   changeEntry(A,1,1,4);
   B = product(A,M);
   Z = newMatrix(1);
   changeEntry(Z,1,1,12);
   assert(equals(B,Z));
   freeMatrix(&M);
   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&Z);
   printf("product() works!\n");
   // //All Functions work
   printf("All Functions are working!\n");


}


int main(int argc, char* argv[]){

   TestFunctions();

}
