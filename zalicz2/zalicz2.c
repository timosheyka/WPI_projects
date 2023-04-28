#include <stdio.h>
#include <limits.h>

#ifndef POLA
#define POLA 4
#endif
#ifndef WIERSZE
#define WIERSZE 10
#endif
#ifndef KOLUMNY
#define KOLUMNY 7
#endif
#ifndef WYBOR
#define WYBOR 234
#endif

void platform_clean(int platform[WIERSZE][KOLUMNY]) // cleans platform
{
    for (int i = 0; i < WIERSZE; i++)
        for (int j = 0; j < KOLUMNY; j++)
            platform[i][j] = 0;
}


void fill(int platform[WIERSZE][KOLUMNY], int move_l_w[], int move_l_k[], int move_r_w[], int move_r_k[], int f)    // fill already done moves
{

    for (int cc = 0; cc < f; cc++)                              // fill horizontal moves
        for (int j = move_r_k[cc];j < KOLUMNY  && j < move_r_k[cc] + POLA; j++)
            platform[move_r_w[cc]][j] = 1;
    for (int c = 0; c <= f; c++)                                // fill vertical moves
        for (int i = move_l_w[c];i < WIERSZE && i < move_l_w[c] + POLA; i++)
            if(move_l_k[c] != -1)                                  // condition if the left player pass
                platform[i][move_l_k[c]] = 1;
}

int value_right(int platform[WIERSZE][KOLUMNY])  // counting ocena planszy for right player
{
    int value = 0;
    for(int i = 0; i < WIERSZE; i++)
    {
        for (int j = 0; j < KOLUMNY;)
        {
            int a = j;
            for (; a < j + POLA && a < KOLUMNY && platform[i][a] == 0; a++)
            {
                platform[i][a] = 1;
                if (a == j + POLA - 1)
                    value++;
            }
            if(a < KOLUMNY && platform[i][a] == 1)
                a++;
            j = a;
        }
    }
    return value;
}

int value_left(int platform[WIERSZE][KOLUMNY])  // counting ocena planszy for left player
{
    int value = 0;
    for(int i = 0; i < KOLUMNY; i++)
    {
        for (int j = 0; j < WIERSZE;)
        {
            int a = j;
            for (; a < j + POLA && a < WIERSZE && platform[a][i] == 0; a++)
            {
                platform[a][i] = 1;
                if (a == j + POLA - 1)
                    value++;
            }
            if(a < WIERSZE && platform[a][i] == 1)
                a++;
            j = a;
        }
    }
    return value;
}

int move(int platform[WIERSZE][KOLUMNY], int wiersze, int kolumny) // checking if the move is possible
{
    int temp = 0;
    for(int i = kolumny;i < KOLUMNY && i < kolumny + POLA; i++)
        if(platform[wiersze][i] == 0)
            temp++;
    if(temp == POLA)
        return 1;
    else
        return 0;
}



int main()
{
    int platform_main[WIERSZE][KOLUMNY];
    int platform_pom[WIERSZE][KOLUMNY];
    platform_clean(platform_main);      // setting 0 values for platform
    platform_clean(platform_pom);       // setting 0 values for platform
    int f = 0;
    int move_l_w[1000];   // moves left player on rows
    int move_l_k[1000];   // moves left player on columns
    int move_r_w[1000];  // moves right player on rows
    int move_r_k[1000];   // moves right player on columns
    for(int i = 0; i < 1000; i++)
    {
        move_l_w[i] = 0;
        move_l_k[i] = 0;
        move_r_w[i] = 0;
        move_r_k[i] = 0;
    }
    int s1mple = 0;

    do
    {
        char input[2];
        scanf("%c", &input[0]);
        if (input[0] == '.')                // set the condition of left player Defeat
            return 0;
        scanf("%c", &input[1]);
        if(input[0] != '-')                 // set the condition for passing first move
        {
            move_l_k[f] = (int) input[0] - 'A';
            move_l_w[f] = (int) input[1] - 'a';
        }
        else
        {
            move_l_k[f] = -1;
            move_l_w[f] = -1;
        }
        move_r_k[0] = s1mple;
        fill(platform_main, move_l_w, move_l_k, move_r_w, move_r_k, f); // filling in already known moves
        fill(platform_pom, move_l_w, move_l_k, move_r_w, move_r_k, f);  // filling in already known moves

        int ind_w[1000] = {0};           // arr with rows indexes
        int ind_k[1000] = {0};           // arr with columns indexes
        int cur_ind = 0;
        int max_value = INT_MIN;        // set start value for max ocena planszy
        int vr = value_right(platform_pom); // counting ocena planszy for right player
        if (vr == 0)
        {
            printf(".\n");
            return 0;
        }
        platform_clean(platform_pom);
        fill(platform_pom, move_l_w, move_l_k, move_r_w, move_r_k, f);
        for (int i = 0; i < WIERSZE; i++)
        {
            for (int j = 0; j < KOLUMNY; j++)
            {
                if (move(platform_pom, i, j) == 1)  // checking if the move is possible
                {

                    for (int jj = j;jj < KOLUMNY && jj <j + POLA; jj++)    // simulating rights move
                        platform_pom[i][jj] = 1;
                    int vl = value_left(platform_pom);      // counting ocena planszy for left player
                    platform_clean(platform_pom);
                    fill(platform_pom, move_l_w, move_l_k, move_r_w, move_r_k, f);

                    int diff = vr - vl;             // difference between right and left values(ocena planszy)

                    if (diff > max_value) {
                        cur_ind = 0;
                        max_value = diff;
                        ind_w[cur_ind] = i;
                        ind_k[cur_ind] = j;
                        cur_ind++;
                    } else if (diff == max_value) {
                        ind_w[cur_ind] = i;
                        ind_k[cur_ind] = j;
                        cur_ind++;
                    }
                }
            }
        }
        move_r_w[f] = ind_w[WYBOR % cur_ind];                       // saving value in moves array
        move_r_k[f] = ind_k[WYBOR % cur_ind];                       // saving value in moves array
        if( f == 0)
            s1mple = move_r_k[f];
        char small_letter = (char) (ind_w[WYBOR % cur_ind] + 'a');
        char big_letter = (char) (ind_k[WYBOR % cur_ind] + 'A');
        printf("%c", small_letter);
        printf("%c", big_letter);
        printf("\n");
        f++;                               // next iteration
    } while (1);                           // exit conditions were set inside
}


