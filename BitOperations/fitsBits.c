#include <stdio.h>
#include <math.h>
int fitsBits(int x, int n)
 {
    return (!(((~x & (x >> 31)) + (x & ~(x >> 31))) >> (n + ~0)));
 }
 int main()
{
  int a1,a2;
  scanf("%d%d",&a1,&a2);
  printf("%d\n",fitsBits(a1,a2));
}
