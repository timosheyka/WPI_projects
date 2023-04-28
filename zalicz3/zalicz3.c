#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>



void iton(int x, int **a, int *n)
{
    int valid = 1;
    if(x < 0)
    {
        valid = -1;
        x = valid * x;
    }
    int *tab = NULL;
    int size = 0;
    int ei;
    for (int i = 0; x > 0; i++)
    {
        if (x % 2 == 1)
                {
                    size++;
                    ei = 2 - (x % 4);
                    x = x - ei;
                    tab = realloc(tab,(size_t)  size);
                    assert(tab != NULL);
                    if (ei == valid * 1) tab[size - 1] =  i;
                    else tab[size - 1] = - i - 1;
                }
                x = x / 2;
    }
    *a = tab;
    *n = size;
}


int ntoi(int *a, int n)
{
    int x = 0;
    for (int i = 0; i < n; i++)
    {
       if(a[i] > 0)
           x +=(int)  pow(2, a[i]);
       else
           if(a[i] < 0) x -= (int)  pow(2, -a[i] - 1);
           else x += 1;
    }
    return x;
}

//void nadd(int *a, int an, int *b, int bn, int **c, int *cn)



void pisz(int *a, int n)
{
    for (int i = 0; i < n; i++)
        printf("%+d", a[i]);
    putchar(';');
}



int main()
{
    int ile;
    int *si;
    iton(24, &si, &ile);
    pisz(si, ile);
    printf(" (%d)\n", ntoi(si, ile));

    free(si);
    return 0;
}
