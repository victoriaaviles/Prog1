/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* programa principal */
int main ()
{
    srand (0); /* use assim, com zero */

    long n, max;

    scanf ("%ld", &n);
    scanf ("%ld", &max);

    if (n > 0 && n < 100 && max > 0 && max < 30) 
    {
        for (int i = 1; i <= n; i++) 
        {
            printf ("%d: ", i);

            struct racional r1 = sorteia_r (-max, max);
            struct racional r2 = sorteia_r (-max, max);

            imprime_r (r1);
            printf (" ");
            imprime_r (r2);
            printf (" ");
            
            if (valido_r (r1) == 0 || valido_r (r2) == 0)
            {
                printf ("NUMERO INVALIDO");
                return 1;
            }

            struct racional result_soma = soma_r (r1, r2);
            struct racional result_sub = subtrai_r (r1, r2);
            struct racional result_mult = multiplica_r (r1, r2);
            struct racional result_div = divide_r (r1, r2);


            if (valido_r (result_div) == 0)
            {
                printf ("DIVISAO INVALIDA");
                return 1;
            }

            imprime_r (result_soma);
            printf (" ");
            imprime_r (result_sub);
            printf (" ");
            imprime_r (result_mult);
            printf (" ");
            imprime_r (result_div);
            printf ("\n");
        }
    }
    return (0);
}
