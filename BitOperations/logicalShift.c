#include <stdio.h>
#include <math.h>
int logicalShift(int x, int n)
 {
     return (((x >> n) & ((1 << (~n + 33)) + ~0)) | (!n << 31 >> 31 & x));
 }
 int main()
{
  int a1,a2;
  scanf("%x%d",&a1,&a2);
  printf("0x%x\n",logicalShift(a1,a2));
}
