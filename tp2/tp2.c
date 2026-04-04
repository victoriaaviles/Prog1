/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* coloque aqui as funções auxiliares que precisar neste arquivo */
struct racional simplifica_r (struct racional r);

/* programa principal */
int main ()
{
  struct racional v[100];
  int n;

  if (scanf ("%d", &n) != 1)
    return 1;
  
  if (n <= 0 || n > 100)
    return 0;
  
  for (int i = 0; i < n; i++)
  {
    scanf ("%ld %ld", &v[i].num, &v[i].den);
  }

  printf ("VETOR = ");
  for (int i = 0; i < n; i++)
  {
    imprime_r (v[i]);
    if (i < n - 1) 
      printf (" ");
  }
  printf("\n");

  int n_valido = 0;
  for (int i = 0; i < n; i++)
  {
    if (valido_r (v[i]))
    {
      v[n_valido] = simplifica_r (v[i]);
      n_valido++;
    }
  }

  printf ("VETOR = ");
  for (int i = 0; i < n_valido; i++)
  {
    imprime_r (v[i]);
    if (i < n_valido - 1)
      printf (" ");
  }
  printf("\n");

  for (int i = 0; i < n_valido - 1; i++)
  {
    for (int j = 0; j < n_valido - i - 1; j++)
    {
      if (compara_r (v[j], v[j+1]) > 0) 
      {
        struct racional aux = v[j];
        v[j] = v[j+1];
        v[j+1] = aux;
      }
    }
  }
  printf ("VETOR = ");
  for (int i = 0; i < n_valido; i++)
  {
    imprime_r (v[i]);
    if (i < n_valido - 1)
      printf (" ");
  }
  printf("\n");

  struct racional total;
  total.num = 0;
  total.den = 1;

  for (int i = 0; i < n_valido; i++)
  {
    soma_r (total, v[i], &total);
  }

  printf ("SOMA = ");
  imprime_r (total);
  printf ("\n");

  return (0) ;
}
