#include "stdio.h"
#include "stdlib.h"

// Task 1 variable def.
unsigned char a = 0xAB; // Hex for 171 - 1010 1011
unsigned char b = 0xFE; // Hex for 254

// Task 2 & 3
char string[] = "c"; // toUpper char array def.
int i = 0; // Ticker

// ToUpper Funktion Task 2 & Task 3
void ToUpper(char * str) {

  while (str[i] != '\0') {
    if (str[i] >= 'a' && str[i] <= 'z') {
      str[i] = str[i] - 32;
    }
    ++i;
  }
}

int main() {
// Task 1

    printf("\n a + b = %#04X", (unsigned char)(a+b));

    // a-b
    printf("\n b - a =%#04X", b-a);

    //NOT(a)
    printf("\n NOT(a) = %#04X", (unsigned char)~a);

    //a XOR b
    printf("\n a XOR b: = %#04X", (a^b));

    //Right shift a by 4
    printf("\n a shifted 4 to the right: = %#04X", (a>>4));

    //Left shift b by 2
    printf("\n b shifted to the left by 2: = %#04X", (unsigned char)(b<<2));

    //Toggle 3rd bit of a
    printf("\n 3rd bit of a = %#04X", (a^=1<<3));

    // Toggle 7th bit of b
    printf("\n 7th bit of b = %#04X", (b^=1<<7));

// Calling Function Task 2 & Task 3

    ToUpper(string);
    printf("\n ToUpper: = %s" , string);

    return 0;
}

