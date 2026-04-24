#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

struct racional {
  long num;          
  long den;          
};

/* Maximo Divisor Comum entre a e b      */
/* calcula o mdc pelo metodo de Euclides */
long mdc (long a, long b)
{
  if (a < 0) 
  a = -a;

  if (b < 0)
  b = -b;

  long resto;
    while (b != 0) 
    {
      resto = a % b;
      a = b;
      b = resto;
    }

  return a;
}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b)
{
  if (a == 0 || b == 0) return 0;
  return (a * b) / mdc (a, b);
}

/* Simplifica o número racional indicado no parâmetro. */

int simplifica_r (struct racional *r)
{
  if (!valido_r(r))
  return 0;
  
  long divisor = mdc (r->num, r->den);
  r->num = r->num / divisor;
  r->den = r->den / divisor;

  if (r->den < 0)
  {
    r->num = -r->num;
    r->den = -r->den;
  }

  return 1;
}

/* Funções do racional.h */

/* Retorna o numerador do racional r */
long numerador_r (struct racional *r)
{
  return r->num;
}

/* Retorna o denominador do racional r */
long denominador_r (struct racional *r)
{
  return r->den;
}

/* Cria um número racional com o numerador e denominador indicados
 * e retorna um ponteiro que aponta para ele.
 * A memória para o número racional deve ser alocada dinamicamente
 * por esta função. Retorna NULL se não conseguiu alocar a memória. */
struct racional *cria_r (long numerador, long denominador)
{
  struct racional *r = malloc (sizeof(struct racional));
  if (r == NULL)
  return NULL;

  r->num = numerador;
  r->den = denominador;

  return r;
}

/* Libera a memória alocada para o racional apontado por r */
void destroi_r (struct racional **r)
{
  if ( r != NULL && *r != NULL)
  {
    free (*r);
    *r = NULL;
  }
}

/* Retorna 1 se o racional r for válido ou 0 se for inválido. */
int valido_r (struct racional *r)
{
  if (r == NULL)
    return 0;

  if (r->den == 0)
    return 0;

  return 1;
}

/* Imprime um racional r */
void imprime_r (struct racional *r)
{
  if (r == NULL) 
  {
    printf ("NULL");
    return;
  }

  if (!valido_r (r))
  {
    printf ("NaN");
    return;
  }

  simplifica_r (r); /* simplifica o racional */
  
  if (r->num == 0)
    printf ("0");
  else if (r->den == 1)
    printf ("%ld", r->num);
  else if (r->num == r->den)
    printf ("1");
  else if (r->num == -r->den)
    printf ("-1");
  else printf("%ld/%ld", r->num, r->den);
}

/* Compara dois números racionais r1 e r2.
 * Comparação normalizando os denominadores pelo MMC.*/
int compara_r (struct racional *r1, struct racional *r2)
{
  if (r1 == NULL || r2 == NULL || !valido_r (r1) || !valido_r (r2))
  return -2;

  simplifica_r (r1);
  simplifica_r (r2);

  /* Divisão do numerador pelo denominador */
  long norm1 = r1->num * r2->den;
  long norm2 = r1->den * r2->num;

  if (norm1 < norm2)
  return -1;

  if (norm1 > norm2)
  return 1;

  return 0;
}

/* Coloca em *r3 a soma simplificada dos racionais *r1 e *r2.
 * Retorna 1 em sucesso e 0 se r1 ou r2 for inválido ou um ponteiro for nulo. */
int soma_r (struct racional *r1, struct racional *r2, struct racional *r3)
{
  if (r1 == NULL || r2 == NULL || r3 == NULL)
  return 0;

  if (!valido_r (r1) || !valido_r (r2))
  return 0;
  
  r3->num = (r2->den * r1->num) + (r1->den * r2->num);
  r3->den = (r1->den * r2->den);

  simplifica_r (r3);

  return 1;
}

/* Coloca em *r3 a diferença simplificada dos racionais *r1 e *r2.
 * Retorna 1 em sucesso e 0 se r1 ou r2 for inválido ou um ponteiro for nulo. */
int subtrai_r (struct racional *r1, struct racional *r2, struct racional *r3)
{
  if (r1 == NULL || r2 == NULL || r3 == NULL)
  return 0;

  if (!valido_r (r1) || !valido_r (r2))
  return 0;
  
  r3->num = (r2->den * r1->num) - (r1->den * r2->num);
  r3->den = (r1->den * r2->den);

  simplifica_r (r3);

  return 1;
}

/* Coloca em *r3 o produto simplificado dos racionais *r1 e *r2.
 * Retorna 1 em sucesso e 0 se r1 ou r2 for inválido ou um ponteiro for nulo. */
int multiplica_r (struct racional *r1, struct racional *r2, struct racional *r3)
{
  if (r1 == NULL || r2 == NULL || r3 == NULL)
  return 0;

  if (!valido_r (r1) || !valido_r (r2))
  return 0;

  r3->num = (r1->num * r2->num);
  r3->den = (r1->den * r2->den);

  simplifica_r (r3);

  return 1;
}

/* Coloca em *r3 a divisão simplificada do racional *r1 por *r2.
 * Retorna 1 em sucesso e 0 se r1 ou r2 for inválido ou um ponteiro for nulo. */
int divide_r (struct racional *r1, struct racional *r2, struct racional *r3)
{
  if (r1 == NULL || r2 == NULL || r3 == NULL)
  return 0;

  if (!valido_r (r1) || !valido_r (r2) || r2->num == 0)
  return 0;
  
  r3->num = (r1->num * r2->den);
  r3->den = (r1->den * r2->num);

  simplifica_r (r3);

  return 1;
}