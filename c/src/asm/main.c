#include <stdio.h>

int main() {
    int src = 10;
    int dst;

    // Extended ASM: copies 'src' to 'dst' and adds 5
    asm ("mov %1, %0"
         "add $5, %0"
         : "=r" (dst)   // Output (%0)
         : "r" (src)    // Input (%1)
    );

    printf("Result: %d\n", dst); // Prints 15
    return 0;
}
