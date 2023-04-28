#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* read()
{
    char* line = NULL;
    char* tmp = NULL;
    size_t size = 0;
    size_t index = 0;
    int ch = EOF;
    while (ch)
    {
        ch = getchar();
        if (ch == EOF || !isalnum(ch))
        {
            ungetc(ch, stdin);
            ch = 0;
        }
        if (size <= index) {
            size += 100;
            tmp = realloc(line, size);
            if (!tmp) {
                free(line);
                line = NULL;
                break;
            }
            line = tmp;
        }
        line[index++] = (char)ch;
    }

    return line;
}

void clear_input() {
    int c;
    do {
        c = getchar();
    } while (c == ' ' || c == '\n');
    ungetc(c, stdin);
}

char* getsymb()
{
    clear_input();
    int c = getchar();
    if (isalnum(c))
    {
        ungetc(c, stdin);
        return read();
    }
    else
    if (c == '-')
    {
        c = getchar();
        return "->";
    }
    else
    if (c == '{')
    {
        return "{";
    }
    return "}";
}

int* addsize(int* x, int vert)
{
    int n = (vert + 1);
    x = (int*)(realloc(x, (long unsigned int) n * sizeof(int)));
    return x;
}

void dfs(int v, int** a, int* used, int *vert)
{
    used[v] = 1;
    for (int i = 0; i < vert[v]; i++)
    {
        if (used[a[v][i]] == 0)
            dfs(a[v][i], a, used, vert);
    }
}

int main()
{
    char** cur_line = malloc(sizeof(char*));
    char* linijka = getsymb();
    while (!strcmp(linijka, "{"))
        linijka = getsymb();

    int* cur_val = malloc(sizeof(int));
    int ii = 0;
    int kiki = 0;

    linijka = getsymb();
    linijka = getsymb();
    while (strcmp(linijka, "}") != 0)
    {
        int vlad = 0;
        if (strcmp(linijka, "->") != 0)
        {
            for (int j = 0; j < kiki; j++)
                if (strcmp(linijka, cur_line[j]) == 0)
                    vlad = 1;
            if (!vlad)
            {
                cur_line = realloc(cur_line, sizeof(char*) * (long unsigned int) (kiki + 1));
                cur_line[kiki] = linijka;
                kiki++;
            }
            for (int cur_ind = 0; cur_ind < kiki; cur_ind++)
                if (strcmp(cur_line[cur_ind], linijka) == 0)
                {
                    cur_val = realloc(cur_val, sizeof(int) *(long unsigned int) (ii + 1));
                    cur_val[ii] = cur_ind;
                    ii++;
                }
        }
        linijka = getsymb();
    }

    int start = 0;
    for(int i = 0; i < kiki; i++)
        if(strcmp(cur_line[i], "start") == 0)
            start = i;

    int** a = malloc((long unsigned int) kiki * sizeof(int*));
    for (int i = 0; i < kiki; i++)
        a[i] = (int *) malloc(0);
    int * vert = calloc((long unsigned int) kiki, (long unsigned int) kiki * sizeof(int));
    for (int i = 0; i < ii; i += 2)
    {
        a[cur_val[i]] = addsize(a[cur_val[i]], vert[cur_val[i]]);
        a[cur_val[i]][vert[cur_val[i]]] = cur_val[i + 1];
        vert[cur_val[i]]++;
    }
    int* used = calloc((long unsigned int) kiki, (long unsigned int) kiki * sizeof(int));
    dfs(start, a, used, vert);
    int ans = 0;
    for (int i = 0; i < kiki; i++)
        if (used[i] == 1)
            ans++;
    printf("%d\n", ans);
}
