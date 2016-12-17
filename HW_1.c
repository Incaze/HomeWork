#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int m[2] = {0,0};

int app1()
{
    char* s = "save";
    int len = strlen(s);
    m[1]++;
    printf("app1 - %c\n", s[m[1]-1]);
    if (m[1] >= len)
    {
        printf("app1 - FINISHED\n");
    }
    return m[1] >= len;
}

int app2()
{
    char* s = "yourself";
    int len = strlen(s);
    m[2]++;
    printf("app2 - %c\n", s[m[2]-1]);
    if (m[2] >= len)
    {
        printf("app2 - FINISHED\n");
    }
    return m[2] >= len;
}

typedef int (*fn_t)();
fn_t queue[] = { app1, app2 };

int main()
{
    int mas[2] = {0,0};
    int flag = 1;
    int i;
    while (flag == 1)
    {
        flag = 0;
        for (i = 0; i < 2; i++)
        {
            if (!mas[i] == 1)
            {
                mas[i] = queue[i]();
                flag = 1;
            }
        }
    }
    return 0;
}
