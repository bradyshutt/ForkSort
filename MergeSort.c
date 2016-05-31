/* Author: Brady Shutt */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NXT_ELM_A setA->elems[idxA]
#define NXT_ELM_B setB->elems[idxB]
#define SWAP_ELEMS(ELEM_A, ELEM_B) {\
   int __TMP_A = ELEM_A;\
   ELEM_A = ELEM_B;\
   ELEM_B = __TMP_A;\
   }

#ifdef DEBUG
#define debug printf
#else
#define debug if (0) printf
#endif


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

Set *NewRandomSet(int size) { 
   int idx;
   Set *rtn = calloc(1, sizeof(Set));

   rtn->size = size;
   rtn->elems = calloc(size, sizeof(int));
   
   for (idx = 0; idx < size; idx++)
      rtn->elems[idx] = rand() % size ;

   return rtn;
}

void FreeSet(Set *set) {

   free(set->elems);
   free(set);
}

int IsSorted(Set *set) {
   int idx, highest = -1;

   for (idx = 0; idx < set->size; idx++) {
      if (set->elems[idx] < highest) {
         return 0;
      }
      highest = set->elems[idx];
   }

   return 1;
}

Set *Partition(Set *set, int start, int end) {
   int idx, size = end - start;
   Set *rtn = NewSet(size);

   for (idx = 0; start < end; idx++, start++)
      rtn->elems[idx] = set->elems[start];

   return rtn;
}

void PrintState(char *name, Set *set) {
   int idx;

   printf("Set %10s(%d): \t", name, set->size);

   for (idx = 0; idx < set->size; ++idx) {
      printf("%.2d%s", set->elems[idx], ((idx + 1) % 5) ? " " : "   ");
   }
   printf("\n");

}

Set *Merge(Set *leftSet, Set *rightSet) {
   int idxL = 0, idxR = 0, idxNew = 0;
   Set *merged = NewSet(leftSet->size + rightSet->size);

   if (!IsSorted(leftSet)) {
      printf("left set not sorted \n");
      exit(1);
   }

   if (!IsSorted(rightSet)) {
      printf("right set not sorted \n");
      exit(1);
   }

   //printf("################ new set size: %d\n", merged->size);

   while (idxL < leftSet->size && idxR < rightSet->size) {

      //printf("comparing %d ? %d\n", leftSet->elems[idxL], rightSet->elems[idxR]);
      merged->elems[idxNew++] = (leftSet->elems[idxL] < rightSet->elems[idxR]) 
       ? leftSet->elems[idxL++] : rightSet->elems[idxR++];

      //printf("################ next element : %d\n", merged->elems[idxNew - 1]);
   }
   while (idxL < leftSet->size) {
      merged->elems[idxNew++] = leftSet->elems[idxL++];
      //printf("################ next element : %d\n", merged->elems[idxNew - 1]);
   }

   while (idxR < rightSet->size) {
      merged->elems[idxNew++] = rightSet->elems[idxR++];
      //printf("################ next element : %d\n", merged->elems[idxNew - 1]);
   }

   FreeSet(leftSet);
   FreeSet(rightSet);

   return merged;
}

Set *MergeSort(Set *set) {
   int mid;
   Set *leftPartition, *rightPartition, *merged;
   //PrintState(set);


   if (set->size == 1)
      return set;

   mid = set->size / 2;

   leftPartition = Partition(set, 0, mid);
   rightPartition = Partition(set, mid, set->size);

   leftPartition = MergeSort(leftPartition);
   rightPartition = MergeSort(rightPartition);

   merged = Merge(leftPartition, rightPartition);

   //PrintState("Merged", merged);

   return merged;

}

int main(int argc, char *argv[]) {
   int idx;
   Set *random;

   srand(time(NULL));

   int val;
   for (idx = 0; idx < 1000000; idx++) {

      val = (rand() % 50) + 1;
      //fprintf(stderr, "rand val: %d\n", val);
      random = NewRandomSet(val);
      //PrintState("Unsorted", random);
      random = MergeSort(random);
      //PrintState("Sorted", random);
      if (IsSorted(random)) {
         fprintf(stderr, "%s", ".");
      }
      else  {
         fprintf(stderr, "%s", "ERROR");
         break;
      }
   }


   return 0;
}




