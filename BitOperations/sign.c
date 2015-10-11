#include <stdio.h>
#include <math.h>
int sign(int x)
 {
     return(!!x | (x >> 31));
 }
 int main()
{
  int a;
  scanf("%d",&a);
  printf("%d\n",sign(a));
}
