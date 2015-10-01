#include <stdio.h>
#include <math.h>
int bitAnd(int x,int y)
 {
     return (~(~x | ~y));
 }
int bitXor(int x,int y)
 {
     return (~(~x & ~y) & ~(x & y));
 }
int thirdBits()
 {
     return ( (73 << 23) | (73 << 14) | (73 << 5) | 9 );
 }
int fitsBits(int x, int n)
 {
     return ( x>>n ); //Wrong
 }
int sign(int x)
 {
     return(1 |(x>>31));
 }
int getByte(int x, int n)
 {
     return((x>>(n<<3))&255);
 }
int logicalShift(int x, int n)
 {
     return((x>>n)); // Wrong
 }

int addOK(int x, int y)
 {
     return(!!(x+y));
 }
int bang(int x)
 {
     return((x&1)^1);
 }

int conditional(int x,int y,int z)
 {
     return((((!x^1)<<31>>31)&y)+(((!x^0)<<31>>31)&z));

 }
 /*
int isPower2(int x)
 {
     return(x>>);
 }*/
int main()
{
  int a1,a2,a3,a4,a5;
  scanf("%d%d%d%x%x",&a1,&a2,&a3,&a4,&a5);
  printf("bitAnd = %d\n",bitAnd(a1,a2));
  printf("bitXor = %d\n",bitXor(a1,a2));
  printf("thirdBits (10-th) : %d\n",thirdBits());
  printf("fitsBits = %d\n",fitsBits(a1,a2));
  printf("sign = %d\n",sign(a1));
  printf("getByte = 0x%x\n",getByte(a4,a2));
  printf("logicalShift = 0x%x\n",logicalShift(a4,a2)); // Wrong
  printf("addOK = %d\n",addOK(a4,a5));
  printf("bang = %d\n",bang(a1));
  printf("conditional = %d\n",conditional(a1,a2,a3));
  return 0;
}
