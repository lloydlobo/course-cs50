#include <stdio.h>

int main(int argc, char *argv[]) {
  int nums[] = {5, 2, 7, 4, 1, 6, 3, 0};
  int len = sizeof(nums) / sizeof(nums[0]); // int is 4 bytes.
  int sorted_nums[0];
  int prev, curr, temp;
  for (int j = 0; j < len; j++) {
    for (int i = 1; i < len; i++) {
      prev = nums[i - 1];
      curr = nums[i];
      if (prev > curr || curr == 0 && prev > curr) {
        temp = curr;
        curr = prev;
        prev = temp;
        sorted_nums[i - 1] = prev;
        sorted_nums[i] = curr;
      } else if (prev <= curr && curr != 0) {
        sorted_nums[i - 1] = prev;
        sorted_nums[i] = curr;
      }
    }
  }
  printf("sorted_nums:\n");
  for (int i = 0; i < len; i++) {
    printf("%d", sorted_nums[i]);
  }
  return 0;
}
