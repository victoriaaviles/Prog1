#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max)
{
  return (rand() % (max - min + 1)) + min;
}

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
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

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b)
{
  if (a == 0 || b == 0) 
    return 0;
  return (a * b) / mdc (a, b);
}

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r (struct racional r)
{
  if (r.den == 0)
    return r;
  
  long divisor = mdc (r.num, r.den);
  r.num = r.num / divisor;
  r.den = r.den / divisor;

  if (r.den < 0) // se r.den negativo, sinal migra para o r.num
  //se r.num e r.den negativo, retorna um positivo
  {
    r.num = -r.num;
    r.den = -r.den;
  }

  return r;
}

/* implemente as demais funções de racional.h aqui */

/* Retorna o numerador do racional r */
long numerador_r (struct racional r)
{
  return r.num;
}

/* Retorna o denominador do racional r */
long denominador_r (struct racional r)
{
  return r.den;
}

/* Cria um número racional com o numerador e denominador indicados. */
struct racional cria_r (long numerador, long denominador)
{
 struct racional r;

 r.num = numerador;
 r.den = denominador;

 return simplifica_r (r);
}

/* Retorna 1 se o racional r for válido ou 0 se for inválido.
 * Um racional é inválido se seu denominador for zero */
int valido_r (struct racional r)
{
  if (r.den == 0)
    return 0;
  return 1;
}

/* Retorna um número racional aleatório na forma simplificada.
 * Deve ser sorteado o numerador e depois o denominador.
 * o racional gerado pode ser válido ou inválido.
 * O numerador e o denominador devem ser inteiros entre min e max. */
struct racional sorteia_r (long min, long max)
{
  struct racional r;

  r.num = aleat (min, max);
  r.den = aleat (min, max);
  
  return simplifica_r (r);
}

/* Imprime um racional r, respeitando estas regras:
   - o racional deve ser impresso na forma simplificada;
   - não imprima espaços em branco e não mude de linha;
   - a saída deve ter o formato "num/den", a menos dos casos abaixo:
     - se o racional for inválido, imprime a mensagem "NaN" (Not a Number);
     - se o numerador for 0, imprime somente "0";
     - se o denominador for 1, imprime somente o numerador;
     - se o numerador e denominador forem iguais, imprime somente "1";
     - se o racional for negativo, o sinal "-" vem antes do numerador;
     - se numerador e denominador forem negativos, o racional é positivo. */
void imprime_r (struct racional r)
{
  if (!valido_r (r))
  {
    printf ("NaN");
    return;
  }

  r = simplifica_r (r);
  
  if (r.num == 0)
    printf ("0");
  else if (r.den == 1)
    printf ("%ld", r.num);
  else if (r.num == r.den)
    printf ("1");
  else if (r.num == -r.den)
    printf ("-1");
  else printf("%ld/%ld", r.num, r.den);
}

/* Compara dois racionais r1 e r2. Retorno: -2 se r1 ou r2 for inválido,
 * -1 se r1 < r2, 0 se r1 = r2 ou 1 se r1 > r2 */
int compara_r (struct racional r1, struct racional r2)
{
  if (!valido_r (r1) || !valido_r (r2))
    return -2;

  long up = r1.num * r2.den;

  long down = r2.num * r1.den;

  if (up < down)
    return -1;

  if (up > down)
    return 1;

  return 0;
}

/* Retorna a soma dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int soma_r (struct racional r1, struct racional r2, struct racional *r3)
{
  if (!valido_r (r1) || !valido_r (r2) || r3 == NULL )
    return 0;
  r3 -> num = (r1.num * r2.den) + (r2.num * r1.den);
  r3 -> den = r1.den * r2.den;

  *r3 = simplifica_r (*r3);

  return 1;
}

/* Retorna a subtracao dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int subtrai_r (struct racional r1, struct racional r2, struct racional *r3)
{
  if (!valido_r (r1) || !valido_r (r2) || r3 == NULL )
    return 0;
  r3 -> num = (r1.num * r2.den) - (r2.num * r1.den);
  r3 -> den = r1.den * r2.den;

  *r3 = simplifica_r (*r3);

  return 1;
}

/* Retorna a multiplicacao dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int multiplica_r (struct racional r1, struct racional r2, struct racional *r3)
{
  if (!valido_r (r1) || !valido_r (r2) || r3 == NULL)
    return 0;
  r3 -> num = r1.num * r2.num;
  r3 -> den = r1.den * r2.den;

  *r3 = simplifica_r (*r3);

  return 1;
}

/* Retorna a divisao dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int divide_r (struct racional r1, struct racional r2, struct racional *r3)
{
  if (!valido_r (r1) || !valido_r (r2) || r3 == NULL || r2.num == 0)
    return 0;
  r3 -> num = r1.num * r2.den;
  r3 -> den = r1.den * r2.num;

  *r3 = simplifica_r (*r3);

  return 1;
}

