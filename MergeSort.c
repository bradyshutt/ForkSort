/* Author: Brady Shutt */

#include <stdio.h>
#include <stdlib.h>

#define NXT_ELM_A setA->elems[idxA]
#define NXT_ELM_B setB->elems[idxB]

typedef struct {
   int size;
   int *elems;
} Set;

Set *NewSet(int size) { 
   Set *rtn = calloc(1, sizeof(Set));

   rtn->size = size;
   rtn->elems = calloc(size, sizeof(int));

   return rtn;
}

void FreeSet(Set *set) {

   free(set->elems);
   free(set);
}

void PrintState(Set *set, int stepNum) {
   int idx;

   printf("Step %d: \t", stepNum);

   for (idx = 0; idx < set->size; ++idx) {
      printf("%d ", set->elems[idx]);
   }
   printf("\n");

}
Set *MergeSort(Set *set) {
   int idx;

   
   

}

Set *Merge(Set *setA, Set *setB) {
   int idxA = 0, idxB = 0, idxNew = 0;
   Set *merged = NewSet(setA->size + setB->size);

   while (idxA < setA->size && idxB < setB->size) {
      merged->elems[idxNew++] = (setA->elems[idxA] < setB->elems[idxB]) 
       ? setA->elems[idxA++] : setB->elems[idxB++];
   }
   while (idxA < setA->size)
      merged->elems[idxNew++] = setA->elems[idxA++];

   while (idxB < setB->size)
      merged->elems[idxNew++] = setB->elems[idxB++];

   FreeSet(setA);
   FreeSet(setB);

   return merged;
}

int main(int argc, char *argv[]) {
   //int *list = { 5, 2, 3, 9, 4, 10, 0, 6, 7, 1, 9 };
   Set *setA = NewSet(10);
   Set *setB = NewSet(10);
   Set *merged;

   setA->elems[0] = 0;
   setA->elems[1] = 2;
   setA->elems[2] = 4;
   setA->elems[3] = 6;
   setA->elems[4] = 8;
   setA->elems[5] = 10;
   setA->elems[6] = 12;
   setA->elems[7] = 14;
   setA->elems[8] = 16;
   setA->elems[9] = 18;

   setB->elems[0] = 1;
   setB->elems[1] = 3;
   setB->elems[2] = 5;
   setB->elems[3] = 7;
   setB->elems[4] = 9;
   setB->elems[5] = 11;
   setB->elems[6] = 13;
   setB->elems[7] = 15;
   setB->elems[8] = 17;
   setB->elems[9] = 19;

   PrintState(setA, 1);
   PrintState(setB, 1);

   merged = Merge(setA, setB);

   PrintState(merged, 1);

   return 0;
}




