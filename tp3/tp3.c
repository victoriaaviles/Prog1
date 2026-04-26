#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* coloque aqui as funções auxiliares que precisar neste arquivo */

/*funcao para imprimir estado do vetor*/
void estado_vetor(struct racional **v, int n) 
{
  printf("VETOR = ");
  for (int i = 0; i < n; i++) 
  {
    imprime_r(v[i]);

    if (i < n - 1)
    printf(" ");
  }
  printf("\n");
}


int main ()
{
  int n, i, j;
  long num, den;
  struct racional **v;
  struct racional *soma_total;

  /* lê um valor n tal que 0 < n < 100 */
  if (scanf("%d", &n) != 1 || n <= 0 || n >= 100)
  return 0;

  /* aloca dinamicamente um vetor com n ponteiros para números racionais */
  v = malloc(n * sizeof (struct racional *));
  if (!v) return 1;

  /* preenche o vetor com n números racionais lidos da entrada */
  for (i = 0; i < n; i++) 
  {
    if (scanf ("%ld %ld", &num, &den) == 2)
      v[i] = cria_r(num, den);
    else 
      v[i] = NULL;
  }

  /* imprime "VETOR = " e os racionais apontados pelo vetor */
  estado_vetor (v, n);

  /* elimina do vetor os racionais inválidos */
  for (i = 0; i < n; i++)
  {
    if (!valido_r(v[i]))
    {
      destroi_r(&v[i]);

      for (j = i; j < n - 1; j++)
      v[j] = v [j + 1];

      n--;
      i--;
    }
  }

  /* imprime "VETOR = " e o vetor resultante */
  estado_vetor (v, n);

  /* ordena o vetor em ordem crescente (Selection Sort) */
  for (i = 0; i < n - 1; i++)
  {
    int min = i;
    for (j = i + 1; j < n; j++)
    {
      if (compara_r(v[j], v[min]) == -1)
      min = j;
    }
    struct racional *temp = v[i];
    v[i] = v[min];
    v[min] = temp;
  }

  /* imprime "VETOR = " e os racionais apontados pelo vetor */
  estado_vetor (v, n);

  /* calcula a soma dos racionais apontados pelo vetor */
  soma_total = cria_r(0,1);
  for (i = 0; i < n; i++)
  {
    soma_r(soma_total, v[i], soma_total);
  }

  /* imprime "SOMA = " e a soma calculada acima */
  printf("SOMA = ");
  imprime_r(soma_total);
  printf("\n");

  /* libera os racionais apontados pelo vetor */
  for (i = 0; i < n; i++)
  {
    destroi_r(&v[i]);
  }

  /* imprime "VETOR = " e os racionais apontados pelo vetor */
  estado_vetor (v, n);

  /* libera o vetor de ponteiros e o espaço da soma */
  free(v);
  destroi_r(&soma_total);

  return 0;
}