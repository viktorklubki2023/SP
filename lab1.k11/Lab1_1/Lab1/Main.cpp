#include <stdio.h>

extern "C" int calc(int, short int, int);
extern "C" int K = 0x311;

int main()
{
    int a;
    short int b;
    int e;
    int res;

    printf("Enter numbers:\n");

    printf("A = ");
    scanf_s("%d", &a);

    printf("B = ");
    scanf_s("%hd", &b);

    printf("E = ");
    scanf_s("%d", &e);


    printf("\n(A - B - K) * 2 + E / 4 = %d\n", ((a - b - K) * 2 + e / 4));

    res = calc(a, b , e);
    printf("\nResult of procedure calc is: %d\n", res);

    return 0;
}
 