#include <stdio.h>
#include <math.h>
int bitXor(int x, int y)
 {
	return ~(~x & ~y) & ~(x & y);
 }
 int main()
{
  int a1,a2;
  scanf("%d%d",&a1,&a2);
  printf("%d\n",bitXor(a1,a2));
}
