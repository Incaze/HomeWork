#include <stdio.h>
#include <math.h>
int bang(int x)
 {
	return((((~x+1)^x)>>31&1)^1);
 }
 int main()
{
  int a;
  scanf("%d",&a);
  printf("%d\n",bang(a));
}
