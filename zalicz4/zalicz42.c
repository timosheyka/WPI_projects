#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

char* read()    // reads word using getchar inside
{               // returns arr of char
    char* line = malloc(sizeof(char));
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
            line = realloc(line, size);
        }
        line[index++] = (char)ch;
    }

    return line;
}

void clear_input() {    // reading until we meet one of tokens , return c back in stream
    int c;
    do {
        c = getchar();
    } while (c == ' ' || c == '\n' || c == '\t');
    ungetc(c, stdin);
}

char* getsymb()     // reading symbol , returns of tokens line
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
        char* tmp = malloc((sizeof(char) * 2) + 1);
        strcpy(tmp, "->");
        return tmp;
    }
    else
    if (c == '{')
    {
        char* tmp = malloc(sizeof(char) + 1);
        strcpy(tmp, "{");
        return tmp;

    }
    char* tmp = malloc(sizeof(char) + 1);
    strcpy(tmp, "}");
    return tmp;
}

int* addsize(int* x, int vert) // increasing size of arr , take pointer to arr and its size , return new size of arr
{
    int n = (vert + 1);
    x = (int*)(realloc(x, (long unsigned int) n * sizeof(int)));
    return x;
}
/*
  check if we have already met some line
  takes index , array line , array of seen lines, size of vertex
 */
void dfs(int v, int** a, int* used, int* vert)
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
    while (!strcmp(linijka, "{")) { // skips symbols until we meet {
        free(linijka);
        linijka = getsymb();
    }
    free(linijka);


    int* cur_val = malloc(sizeof(int));
    int ii = 0;
    int iii = 0;
    int s = 0;
    char** linijka_pom = malloc(sizeof(char*));
    //linijka_pom[0] = malloc(sizeof(char) + 1);
    //linijka_pom[0][1] = '\0';
    linijka_pom[s] = getsymb();    // gets next symbol
    free(linijka_pom[s]);
    linijka_pom[s] = getsymb();// gets first line to be checked
    while (strcmp(linijka_pom[s], "}") != 0)   // iterating until we met symbol of end of words
    {
        bool valid = false;
        if (strcmp(linijka_pom[s], "->") != 0)     // check if we meet arrow
        {
            for (int j = 0; j < iii; j++)             // finding unique words
                if (strcmp(linijka_pom[s], cur_line[j]) == 0)
                    valid = 1;
            if (!valid) // adding to array , that stores unique words
            {
                cur_line = realloc(cur_line, sizeof(char*) * (long unsigned int) (iii + 1));
                cur_line[iii] = malloc(strlen(linijka_pom[s])+1);
                strcpy(cur_line[iii], linijka_pom[s]);
                //strcpy(cur_line[iii], linijka_pom);
                iii++;
            }
            for (int cur_ind = 0; cur_ind < iii; cur_ind++) // converting to number interpretation
            {
                if (strcmp(cur_line[cur_ind], linijka_pom[s]) == 0) // stores unique words to array , that has number convertation
                {
                    cur_val = realloc(cur_val, sizeof(int) * (long unsigned int) (ii + 1));
                    cur_val[ii] = cur_ind;
                    ii++;
                }
            }
        }
        s++;
        linijka_pom = realloc(linijka_pom, (size_t) (s + 1) * sizeof(char*));
        linijka_pom[s] = getsymb();
        //char *tmp = getsymb();
        //linijka_pom[s] = malloc(sizeof(char) * (strlen(tmp) + 1));
        //linijka_pom[s][strlen(tmp)] = '\0';
        //strcpy(linijka_pom[s], tmp);
        //free(tmp);
    }

    int start = 0;
    for (int i = 0; i < iii; i++)
        if (strcmp(cur_line[i], "start") == 0) // finding "start"
            start = i;

    int** actual_arr = calloc((long unsigned int) iii, sizeof(int*)); //  allocate array of lines
    int* vert = calloc((long unsigned int) iii, sizeof(int));
    for (int i = 0; i < ii; i += 2) // determinator equals 2 , bcs we check odd
    {
        actual_arr[cur_val[i]] = addsize(actual_arr[cur_val[i]], vert[cur_val[i]]); // increasing size of actual_arr arr
        actual_arr[cur_val[i]][vert[cur_val[i]]] = cur_val[i + 1];
        vert[cur_val[i]]++;
    }
    int* used = calloc((long unsigned int) iii, (long unsigned int) iii * sizeof(int));
    dfs(start, actual_arr, used, vert); // calling depth first search
    int ans = 0;
    for (int i = 0; i < iii; i++) // make final calculations
        if (used[i] == 1)
            ans++;
    printf("%d\n", ans);

    // free memory
    for (int i = 0; i < iii; i++)
    {
        free(cur_line[i]);
        free(actual_arr[i]);
    }
    for(int i = 0; i <= s; i++)
        free(linijka_pom[i]);
    free(linijka_pom);
    free(cur_line);
    free(cur_val);
    free(actual_arr);
    free(used);
    free(vert);

    return 0;
}
