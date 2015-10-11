#include <stdio.h>
#include <math.h>
int getByte(int x, int n)
 {
     return (x >> (n << 3)) & 255;
 }
 int main()
{
  int a1,a2;
  scanf("%x%d",&a1,&a2);
  printf("0x%x\n",getByte(a1,a2));
}
