#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int x[1000][11]; // definujemy tablice typu int , która będzie przechowywała wartości stojący przy x


void wid_standard(char s[], int spacja)  // funkcja usuwa wszystkie spacji
{
    int i, j;

    for (i = j = 0; s[i] != '\0'; i++)
        if (s[i] != spacja)
            s[j++] = s[i];
    s[j] = '\0';
}

void przepisanie(char str[], int wiersz) // przerabia współczynniki do typu int
{
    int stopien;
    int liczba = 1;
    int posred_wyn[11]; //
    for (int q = 0; q < 11; q++)
        posred_wyn[q] = 0;          // wpisujemy zera do pośredniej tablicy
    int j = 0;
    for (long unsigned int i = 0; i < strlen(str) - 1; i++) // za pomocą funkcji strlen działamy do póki są symbołe
    {
        if (str[i] == '-')
            liczba = -1;
        if (str[i] >= '0' && str[i] <= '9')
        {
            char liczba_str[10];        // na mocy zakresu typu int wiemy , że współczynnik ma <= 9 cyfr
            while (str[i] >= '0' && str[i] <= '9')
            {
                liczba_str[j] = str[i];
                j++;
                i++;
            }
            liczba_str[j] = '\0';
            liczba *= atoi(liczba_str);
            j = 0;
        }
        if (str[i] == '\n') // skoro jest koniec linii stopien x = 0
        {
            posred_wyn[0] = liczba;
        }
        if (str[i] == 'x')
        {
            if (str[i + 1] != '^')
            {
                posred_wyn[1] = liczba;
                liczba = 1;
            }
            else
            {
                i += 2;             // przeskakujemy aby trafić na stopien przy x
                char stopien_str[10];
                while (str[i] >= '0' && str[i] <= '9')
                {
                    stopien_str[j] = str[i];
                    j++;
                    i++;
                }
                stopien_str[j] = '\0';
                stopien = atoi(stopien_str);
                posred_wyn[stopien] = liczba;
                liczba = 1;
                j = 0;
                i--;
            }
        }
    }
    for (int wart_wier = 0; wart_wier < 11; wart_wier++)
        x[wiersz][wart_wier] = posred_wyn[wart_wier];   // przenosimy wartości do głównej tablicy
}

int main()
{
    char str[1000][1000];
    /////////////////////////////////////////////////////////////// wprowadzanie wejsćiowych danych
    int i = -1;
    do
    {
        i++;
        fgets(str[i], 1010, stdin);
        wid_standard(str[i], ' ');
    } while (str[i][0] != '.');
    /////////////////////////////////////////////////////////////// koniec wprowadzania wejsćiowych danych
    int n = i; // ograniczamy ilość wierzszów
    /////////////////////////////////////////////////////////////// wyprowadzanie pierwszego wiersza
    long unsigned int wart_wier1 = 1;
    if (str[0][wart_wier1] == '-')
    {
        printf("-");
        wart_wier1++;
    }
    for (; wart_wier1 < strlen(str[0]); wart_wier1++)
    {
        if (str[0][wart_wier1] == '+' || str[0][wart_wier1] == '-')
            printf(" %c ", str[0][wart_wier1]);
        else printf("%c", str[0][wart_wier1]);
    }
    /////////////////////////////////////////////////////////////// koniec wyprowadzania pierwszego wiersza
    for (i = 0; i < n; i++)
    {
        if (i == 1)
            przepisanie(str[i], i);
        else przepisanie(str[i], i);
    }
    /////////////////////////////////////////////////////////////// proces działania
    for (i = 1; i < n; i++)
    {
        int p;
        int tab_dzial[22];  // tablica , nad której wykonujemy działanie
        for (p = 0; p < 22; p++)
            tab_dzial[p] = 0;
        if (str[i][0] == '+')
        {
            for (p = 0; p < 11; p++)
                tab_dzial[p] = x[i][p] + x[i - 1][p];
        }
        else
        {
            for (int xi = 0; xi < 11; xi++)
            {
                for (int xj = 0; xj < 11; xj++)
                {
                    tab_dzial[xi + xj] += (x[i][xi] * x[i - 1][xj]);
                }
            }
        }
        /////////////////////////////////////////////////////////////// koniec procesu działąnia
        /////////////////////////////////////////////////////////////// wyprowadzanie danych
        int bool1 = 0;
        for (int z = 10; z >= 1; z--)
        {
            if (tab_dzial[z] != 0)
            {
                if (bool1 == 1)
                {
                    if (tab_dzial[z] < 0)
                        printf(" - ");
                    else
                        printf(" + ");
                }
                if (bool1 == 0)
                {
                    if (tab_dzial[z] < 0)
                        printf("-");
                    bool1 = 1;
                }
                if (!(abs(tab_dzial[z]) == 1 && z > 0))
                    printf("%d", abs(tab_dzial[z]));
                if (z > 1)
                    printf("x^%d", z);
                if (z == 1)
                    printf("x");
            }
        }
        if (tab_dzial[0] != 0)
        {
            if (tab_dzial[0] > 0)
                printf(" + ");
            else printf(" - ");
            printf("%d", abs(tab_dzial[0]));
        }
        int bool2 = 0;
        for (int e = 0; e < 11; e++)
        {
            if (tab_dzial[e] != 0)
                bool2 = 1;
        }
        if (bool2 == 0)
            printf("0");
        /////////////////////////////////////////////////////////////// koniec wyprowadzania danych
        printf("\n");
        for (int j = 0; j < 11; j++)
        {
            x[i][j] = tab_dzial[j];  // aktualizacja danych
        }
    }
    return 0;
}
