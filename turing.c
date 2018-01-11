#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int size = 1;
int n = 0;
int *tape;

int movl(void)
{
    if (n == 0)
    {
        int i;
        int* m;
        size++;
        m = (int*) realloc (tape, sizeof(int) * size);
        if(m != NULL)
        {
            for (i = size-1; i != 0; i--)
                m[i]=m[i-1];
            m[0] = 0;
            tape = m;
        }
        else
            return 1;
    }
    else
        n--;
    return 0;
}
int movr(void)
{
    if (n == (size-1))
    {
        int* m;
        size++;
        n++;
        m = (int*) realloc (tape, sizeof(int) * size);
        if(m != NULL)
        {
            m[size-1] = 0;
            tape = m;
        }
        else
            return 1;
    }
    else
        n++;
    return 0;
}
int inc(void)
{
    if(tape[n]<255)
        tape[n]++;
    else
    {
        printf("current tape element was set to 0 to avoid char overflow");
        tape[n] = 0;
    }
    return 0;
}
int dec(void)
{
    if(tape[n]>0)
        tape[n]--;
    else
        tape[n] = 255;
    return 0;
}
int orders(char** a, int f, int l)
{
    int i, m;
    m = 0;
    for (i = f; i<l; i++)
    {
        if (strcmp(a[i], "movl") == 0)
            movl();
        else
            if (strcmp(a[i], "movr") == 0)
                movr();
            else
                if (strcmp(a[i], "inc") == 0)
                    inc();
                else
                    if (strcmp(a[i], "dec") == 0)
                        dec();
                    else
                        if (strcmp(a[i], "print") == 0)
                            printf("\n%d", tape[n]);
                        else
                            if (strcmp(a[i], "get") == 0)
                            {
                                printf("\nEnter symbol:");
                                tape[n] = getchar();
                            }
                            else
                                if (strcmp(a[i], "printc") == 0)
                                    printf("\n%c", tape[n]);
                                else
                                    if (strcmp(a[i], "begin") == 0)
                                        m = i+1;
                                    else
                                        if (strcmp(a[i], "end") == 0)
                                        {
                                            while (tape[n] != 0)
                                            orders(a, m, i);
                                        }
    }
    return 0;
}
char* space(char* s, char* a)
{
    int i, j;
    j = 0;
    a = (char*) malloc (sizeof(char)*6);
    for (i = 0; s[i]; i++)
    {
        if (s[i] != ' ' && s[i] != '\n')
        {
            a[j] = s[i];
            j++;
            a = (char*) realloc (a,(j+6)*sizeof(char));
        }
    }
    a = (char*) realloc (a, j*sizeof(char));
    return a;
}

int main()
{
    char s[255];
    char **a;
    int num, i;
    num = 0;
    i = 0;
    FILE *file;
    file = fopen("file.txt", "r");
    if (file == NULL)
        printf(" Could not open file\n");
    a = (char **) malloc ((num+1)*sizeof(char *));
    while(fgets(s, 255, file))
    {
        if(s[0] != '*')
        {
            a[num] = space(s, a[num]);
            num++;
            a = (char**) realloc (a,(num+1)*sizeof(char*));
        }
    }
    fclose(file);
    tape = (int*) malloc (sizeof(int));
    tape[n] = 0;
    orders(a, 0, num);
    for(i = 0; i < num; i++)
        free(a[num]);
    free(a);
    printf("\n Tape : ");
    for(i = 0; i < size; i++)
        printf("  %d", tape[i]);
    printf("\n");
    return 0;
}
