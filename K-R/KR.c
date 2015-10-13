#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <locale.h>

int mSize;
int *mas;

int power(int a, int n)
{
    int res = 1;
    while (n)
    {
        if (n & 1)
        {
        res = res * a;
        }
        a = a * a;
        n = n >> 1;
    }
    return res;
}

int rwPower()
{
    int ch,st;
    printf("Enter the number and power, please.\n");
    scanf("%d%d",&ch,&st);
    int flag = 0;
    if (st < 0)
    {
        st = -st;
        flag = 1;
    }
    flag ? printf("%d^%d = 1/%d\n",ch,st,power(ch,st)) : printf("%d^%d = %d\n",ch,st,power(ch,st));
    return 0;
}

int rMas()
{
    int i;
    printf("Enter the size of the array, please.\n");
    scanf("%d",&mSize);
    mas = (int*) malloc(mSize*sizeof(int));
    for (i = 0; i < mSize; i++)
    {
        printf("Mas[%d]=",i);
        scanf("%d", &mas[i]);
    }
}

int masNull()
{
    rMas();
    int mNull = 0;
    int i;
    for (i = 0; i < mSize; i++)
    {
        if (mas[i] == 0)
        {
            mNull++;
        }
    }
    free(mas);
    printf("In array %d zero\n",mNull);
    return 0;
}

int masSym()
{
    rMas();
    int i;
    int flag = 1;
    for (i = 0; i < mSize/2; i++)
    {
        if (mas[i] != mas[mSize-i-1])
        {
            flag = 0;
            break;
        }
    }
    free(mas);
    flag ? printf("Array is symmetric") : printf("Array is not symmetric");

}
int spaceDel(char str[255], int i)
{
    int j;
    if (str[i] == ' ')
      {
          for (j = i; j < strlen(str); j++)
          {
              str[j] = str[j+1];
          }
      }
}

int regChange(char str[255], int i)
{
    if ((str[i] >= 'A') && (str[i] <= 'Z'))
    {
        str[i] = str[i] + 32;
    }

    if ((str[i] >= 'А') && (str[i] <= 'Я'))
    {
        str[i] = str[i] + 32; // Почему-то русские символы не преобразует, возможно, что связано с кодировкой.
    }
}

int strCheck(char str[255])
{
    int i;
    int len = strlen(str);
    for (i = 0; i < len - 1; i++)
    {
        if (str[i] != str[len - 2 - i])
        {
            return 0;
            break;
        }
        return 1;
    }
}

int pal()
{
    fflush(stdin);
    char str[255];
    int i;
    int flag = 1;
    printf("Enter the text, please.\n");
    fgets(str,255,stdin);
    for (i = 0; i < strlen(str) - 1; i++)
    {
      spaceDel(str,i);
      regChange(str,i);
    }
    flag = strCheck(str);
    flag ? printf("Palindrome") : printf("Not palindrome");
    return 0;
}

int primNum()
{
    int i,n,j;
    printf("Enter the number, please.\n");
    scanf("%d",&n);
	mas = (int*) malloc(n*sizeof(int));
    for (i = 0; i < n; i++)
    {
        mas[i] = i;
    }
    mas[1] = 0;
    for(i = 2; i < n; i++)
    {
        if(mas[i] != 0)
        {
            for(j = i * 2; j < n; j = j + i)
            {
                mas[j]=0;
            }
        }
    }
    printf("Prime numbers: \n");
    for(i = 0; i < n; i++)
    {
        if(mas[i] != 0)
        {
            printf("%d ", mas[i]);
        }
    }
}

int entry()
{
    fflush(stdin);
    char s[255];
    char s1[255];
    int sum = 0;
    int i,j,flag;
    printf("Write S, please.\n");
    fgets(s,255,stdin);
    printf("Write S1, please.\n");
    fgets(s1,255,stdin);
    for (i = 0; i < strlen(s)-strlen(s1)+1; i++)
    {
        if (s[i] == s1[0])
        {
            flag = 1;
            for (j = 1; j<strlen(s1)-1; j++)
            {
                if (s[j] != s[i+j])
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                sum++;
            }
        }
    }
    printf("Occurrences S1 in S: %d\n",sum);
    return 0;
}

int fib()
{
    int i,n,f,f1,f2;
    printf("Enter number N, please.\n");
    scanf("%d",&n);
    f = 1;
    f1 = 1;
    for (i = 1; i < n; i++)
    {
        f2 = f1;
        f1 = f;
        f = f1 + f2;
    }
    printf("F(n) = %d\n",f);
    return 0;
}

int main()
{
    int task;
    printf("Enter the number of tasks, please.\n");
    scanf("%d",&task);
    switch (task)
    {
        case 3 : rwPower(); break;
        case 4 : masNull(); break;
        case 5 : masSym();  break;
        case 6 : pal();     break;
        case 7 : primNum(); break;
        case 10: entry();   break;
        case 11: fib();     break;
        default : printf("Unknown task"); break;
    }
    return 0;
}
