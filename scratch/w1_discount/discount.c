#include <stdio.h>

const char PERCENT_CHAR = '%';
float prompt_discount();
int prompt_percent_off();
float calculate_sale(float discount, int percentage);

// Function main
int main(void) {
  float d = prompt_discount();
  printf("Your entered Price is: %.2f\n", d);

  int p = prompt_percent_off();
  printf("Your entered percent off is: %d%c\n", p, PERCENT_CHAR);

  float s = calculate_sale(d, p);
  printf("The Sale Price is: %.2f\n", s); // %.2f 2 decimal.
}

float prompt_discount() {
  float regular;
  printf("Regular Price: ");

  scanf("%f", &regular); // adding `&` formats double to float.

  return regular;
}

int prompt_percent_off() {
  int p;

  printf("Percent off: ");
  scanf("%d", &p);

  return p;
}

// discount.c:38:13: error: lvalue required as unary ‘&’ operand
//    38 |   float p = &(100 - percentage) / 100;
float calculate_sale(float discount, int percentage) {
  return discount * (100 - percentage) / 100;
}
