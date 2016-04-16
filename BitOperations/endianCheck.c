#include <stdio.h>

int endianCheck()
{
	union
	{
	    unsigned int val;
		unsigned char byte[4];
    } check;
	check.val = 0x0102;
	return check.byte[0];
}

int main()
{
    printf("%s-endian", (endianCheck() == 1) ? "big" : "little");
    return 0;
}

