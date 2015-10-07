#include <stdio.h>
#include <math.h>
int sign(int x)
 {
     return(1 |(x>>31));
 }
 int main()
{
  int a;
  scanf("%d",&a);
  printf("%d\n",sign(a));
}
