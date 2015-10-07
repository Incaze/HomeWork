#include <stdio.h>
#include <math.h>
int conditional(int x,int y,int z)
 {
     return((((!x^1)<<31>>31)&y)+(((!x^0)<<31>>31)&z));
 }
 int main()
{
  int a1,a2,a3;
  scanf("%d%d%d",&a1,&a2,&a3);
  printf("%d\n",conditional(a1,a2,a3));
}
