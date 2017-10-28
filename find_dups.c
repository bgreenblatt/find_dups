#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct find_dups {
  int elem;
  int count;
};

void insert_subarray(int element, struct find_dups *arr, int *size) {
  int front, middle, end, num_elem_to_move;
  
  front = 0;
  if (0 == *size) {
    goto insert;
  }
  end = *size - 1;

  while (front <= end) {
    middle = (front + end) / 2;
    if (abs(arr[middle].elem) < abs(element)) {
      front = middle + 1;
    } else if (abs(arr[middle].elem) > abs(element)) {
      end = middle - 1;
    } else {
      // found it exactly
      arr[middle].count += 1;
      return;
    }
  }
  // insert at position front.
  num_elem_to_move = *size - front;
  if (num_elem_to_move > 0) {
    memmove(&arr[front + 1], &arr[front], 
          num_elem_to_move * sizeof(struct find_dups));
  }
insert:
  arr[front].elem = element;
  arr[front].count = 1;
  *size += 1;
}

void print_array(struct find_dups *arr, int size, char *type) {
  int i = 0;

  printf("printing %s array of size %d\n", type, size);
  for (i = 0; i < size; i++) {
    printf("arr[%d]: val: %d, count: %d\n", i, arr[i].elem, arr[i].count);
  }
}

void find_pairs(int *arr, int size) {
  struct find_dups *pos_subarray = NULL;
  struct find_dups *neg_subarray = NULL;
  int num_pos_elem = 0, num_neg_elem = 0;
  int zero_flag = 0;
  int i, j;
  
  pos_subarray = malloc(size * sizeof(struct find_dups));
  neg_subarray = malloc(size * sizeof(struct find_dups));
  
  for (i = 0; i < size; i++) {
    if (arr[i] < 0) {
      insert_subarray(arr[i], neg_subarray, &num_neg_elem);
    } else if (arr[i] > 0) {
      insert_subarray(arr[i], pos_subarray, &num_pos_elem);
    } else {
      if (zero_flag == 0) {
        zero_flag = 1;
      } else {
        printf("found a pair of 0s\n");
        zero_flag = 0;
      }
    }
  }
  print_array(pos_subarray, num_pos_elem, "pos");
  print_array(neg_subarray, num_neg_elem, "neg");
  i = 0;
  j = 0;
  while ((i < num_pos_elem) && (j < num_neg_elem)) {
      if (0 == (neg_subarray[j].elem + pos_subarray[i].elem)) {
        printf("found a pair (%d, %d)\n", neg_subarray[j].elem, pos_subarray[i].elem);
        pos_subarray[i].count -= 1;
        neg_subarray[j].count -= 1;
        if ((0 == pos_subarray[i].count) || (0 == neg_subarray[j].count)) {
          i++;
          j++;
        }
      } else if ((neg_subarray[j].elem + pos_subarray[i].elem) < 0) {
        i++;
      } else {
        j++;
      }
  }
}

int main() {
	int arr[] = {2, 5, -7, 4, 0, 5, -4, -34, -5, -3, -5, 7, 0, -7, 9, 0, 3};

	int len = sizeof(arr) / sizeof(int);
	find_pairs(arr, len);
	return 0;
}
