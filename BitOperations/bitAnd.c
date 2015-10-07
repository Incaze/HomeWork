#include <stdio.h>
#include <math.h>
int bitAnd(int x, int y)
 {
	return (~(~x | ~y));
 }
 int main()
{
  int a1,a2;
  scanf("%d%d",&a1,&a2);
  printf("%d\n",bitAnd(a1,a2));
}
