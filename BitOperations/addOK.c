#include <stdio.h>
#include <math.h>
int addOK(int x, int y)
 {
	return !(~((x >> 31) ^ (y >> 31)) & ((x >> 31) ^ ((x + y) >> 31)));
 }
 int main()
{
  int a1,a2;
  scanf("%x%x",&a1,&a2);
  printf("%d\n",addOK(a1,a2));
}
