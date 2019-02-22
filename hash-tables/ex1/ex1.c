#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "ex1.h"

Answer *get_indices_of_item_weights(int *weights, int length, int limit)
{
  // YOUR CODE HERE

  // Initiate Variables and Create Data Structures
  HashTable *ht = create_hash_table(length);
  int retrieved = 0;
  int difference = 0;
  int index = 0;

  for (int i = 0; i < length; i++) {
    // Store difference between limit and weight.
    hash_table_insert(ht, weights[i], limit - weights[i]); 
  }

  for (int i = 0; i < length; i++) {
    // Retrieve difference between the limit and the weight. 
    difference = hash_table_retrieve(ht, weights[i]); 

    // Attempt to find that difference as a key in the hash table.
    retrieved = hash_table_retrieve(ht, difference);

    // // If the difference was found as a weight, the answer is found.
    if (retrieved >= 0) {
      Answer *answer = malloc(sizeof(Answer));
      for (int q = length - 1; q >= 0; q--) {
        if (weights[q] == difference){

          index = q;
          break;
        }
      }
      if (index > i) {
        answer -> index_1 = index;
        answer -> index_2 = i;
      } else {
        answer -> index_1 = i;
        answer -> index_2 = index;
      }

      return answer;
    }
  }
  
  destroy_hash_table(ht);
  return NULL;
}

void print_answer(Answer *answer)
{
  if (answer != NULL) {
    printf("%d %d\n", answer->index_1, answer->index_2);
  } else {
    printf("NULL\n");
  }
}

#ifndef TESTING
int main(void)
{

  // TEST 1
  int weights_1 = {9};
  Answer *answer_1 = get_indices_of_item_weights(&weights_1, 1, 9);
  print_answer(answer_1);  // NULL

  // TEST 2
  int weights_2[] = {4, 4};
  Answer* answer_2 = get_indices_of_item_weights(weights_2, 2, 8);
  print_answer(answer_2);  // {1, 0}

  // TEST 3
  int weights_3[] = {4, 6, 10, 15, 16};
  Answer* answer_3 = get_indices_of_item_weights(weights_3, 5, 21);
  print_answer(answer_3);  // {3, 1}

  // TEST 4
  int weights_4[] = {12, 6, 7, 14, 19, 3, 0, 25, 40};
  Answer* answer_4 = get_indices_of_item_weights(weights_4, 9, 7);
  print_answer(answer_4);  // {6, 2}

  return 0;
}
#endif
