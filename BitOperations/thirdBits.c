#include <stdio.h>
#include <math.h>
int thirdBits()
 {
     return  (73 << 23) | (73 << 14) | (73 << 5) | 4;
 }
int main()
{
printf("%d\n",thirdBits());
}
