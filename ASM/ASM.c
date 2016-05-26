#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define ARRAY_SIZE 262144
#define MAXLENG_STR 255
#define COMMANDS_COUNT 1000

typedef struct instructions
{
    int type;
    union
    {
        int number;
        char lbl[MAXLENG_STR];
    } arg;
} instruction;

typedef struct labels
{
	char name[6];
	size_t line;

} labels;

typedef enum common_type
{
	INSTR_LD = 0,
	INSTR_ST = 1,
	INSTR_LDC,
	INSTR_ADD,
	INSTR_SUB,
	INSTR_CMP,
	INSTR_JMP,
	INSTR_BR,
	INSTR_RET,
	INSTR_BAD = -1
} command;

int data[ARRAY_SIZE];
int stack[ARRAY_SIZE];
char str[MAXLENG_STR];
char stInstr[MAXLENG_STR];
char stArg[MAXLENG_STR];
char *commands[] = {"ld", "st", "ldc", "add", "sub", "cmp", "jmp", "br", "ret"};
const size_t COMMANDS = sizeof(commands) / sizeof(commands[0]);


instruction instr[COMMANDS_COUNT];
labels label[COMMANDS_COUNT];

int arr_label = 0;
int countLines = 0;

inline int deleteSpaces(int j, char s[MAXLENG_STR], int size)
{
    while (s[j] = ' ' && j < size)
    {
        j++;
    }
    return j;
}

int finding(char *stInstr, char *str, int i)
{
    while (str[i] == ' ')
    {
        i++;
    }
    if ((str[i] == ';') || (str[i] == '\0'))
    {
        return i;
    }
    int j = 0;
    while ((isalpha(str[i])) || (isdigit(str[i])) || (str[i] == '-'))
    {
        stInstr[j] = str[i];
        i++;
        j++;
    }
    stInstr[j] = '\0';
    return i;
}

int commandDefine(char *stInstr)
{
    int i = 0;
    for (i; i < COMMANDS; i++)
    {
        if (strcmp(stInstr, commands[i]) == 0)
        {
            return i;
        }
    }
}

int readFile(char *fileName)
{
    FILE *fo = freopen(fileName, "r", stdin);
    if (fo == NULL)
    {
        fprintf(stderr, "Can't read the file\n");
        return 0;
    }
    while (!feof(fo))
    {
        fgets(str, MAXLENG_STR, fo);
        int i = 0;
        while (str[i] == ' ')
        {
            i++;
        }
        if ((str[i] == ';') || (str[i] == '\n') || (str[i] == '\0'))
        {
            continue;
        }
        i = 0;
        i = finding(stInstr, str, i);
        instr[countLines].type = commandDefine(stInstr);

        while (str[i] == ' ')
        {
            i++;
        }
        if (str[i] == ':')
        {
            strcpy(label[arr_label].name, stInstr);
            label[arr_label].line = countLines;
            arr_label++;
            i++;
            if (str[i] == '\0')
            {
                continue;
            } else
            {
                i = finding(stInstr, str, i);
            }
        }
        while (str[i] == ' ')
        {
            i++;
        }
        instr[countLines].type = commandDefine(stInstr);
        int j = 0;
        i = finding(stArg, str, i);
        if (isdigit(stArg[0]) || (stArg[0] == '-'))
        {
            instr[countLines].arg.number = atoi(stArg);
        } else
        {
            strcpy(instr[countLines].arg.lbl, stArg);
        }
        countLines++;
    }
    return 1;
}


int commandRealization(char *fileName)
{
    int SP = -1;
    int i = -1;
    int arg;
    char lbl[MAXLENG_STR];
    int a, b, j;
    while (1)
    {
       i++;
       switch (instr[i].type)
       {
           case INSTR_LD:
               SP++;
               arg = instr[i].arg.number;
               if ((SP < 0) || (SP > ARRAY_SIZE) || (arg > ARRAY_SIZE) || (arg < 0))
               {
                  printf("ERROR_LD");
                  return 0;
               }
               stack[SP] = data[arg];
               break;
           case INSTR_ST:
               arg = instr[i].arg.number;
               if ((SP < 0) || (SP > ARRAY_SIZE) || (arg > ARRAY_SIZE) || (arg < 0))
               {
                  printf("ERROR_ST");
                  return 0;
               }
               data[arg] = stack[SP];
               SP--;
               break;
           case INSTR_LDC:
               SP++;
               arg = instr[i].arg.number;
               if ((SP < 0) || (SP > ARRAY_SIZE))
               {
                   printf("ERROR_LDC");
                   return 0;
               }
               stack[SP] = arg;
               break;
           case INSTR_ADD:
               if (SP < 1)
               {
                   printf("ERROR_ADD");
                   return 0;
               }
               a = stack[SP];
               SP = SP - 1;
               b = stack[SP];
               stack[SP] = a + b;
               break;
           case INSTR_SUB:
                if (SP < 1)
               {
                   printf("ERROR_SUB");
                   return 0;
               }
               a = stack[SP];
               SP = SP - 1;
               b = stack[SP];
               stack[SP] = a - b;
               break;
           case INSTR_CMP:
               if (SP < 1)
               {
                   printf("ERROR_CMP");
                   return 0;
               }
               a = stack[SP];
               SP = SP - 1;
               b = stack[SP];
               stack[SP] = a > b ? 1 : a < b ? -1 : 0;
               break;
          case INSTR_JMP:
               j = 0;
               strcpy(lbl, instr[i].arg.lbl);
               while (strcmp(lbl, label[j].name) != 0)
               {
                   j++;
               }
               i = label[j].line;
               i--;
               break;
           case INSTR_BR:
               if ((stack[SP] == 0))
               {
                   break;
               }
               j = 0;
               strcpy(lbl, instr[i].arg.lbl);
               while (strcmp(lbl, label[j].name) != 0)
               {
                   j++;
               }
               i = label[j].line;
               i--;
               break;
           case INSTR_RET:
               printf("result = %d\n", stack[SP]);
               return 1;
        }
    }
}


int main()
{
    if (!readFile("input.txt"))
    {
        fclose(stdin);
        return 0;
    }
    if (!commandRealization("input.txt"))
    {
        fclose(stdin);
    }
    fclose(stdin);
    return 0;
}
