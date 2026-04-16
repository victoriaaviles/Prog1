/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

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
  if (a == 0 || b == 0) return 0;
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

/* implemente as demais funções aqui */

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
     - se o racional for inválido, deve imprimir a mensagem "INVALIDO";
     - se o numerador for 0, deve imprimir somente "0";
     - se o denominador for 1, deve imprimir somente o numerador;
     - se o numerador e denominador forem iguais, deve imprimir somente "1";
     - se o racional for negativo, o sinal "-" deve vir antes do numerador;
     - se numerador e denominador forem negativos, o racional é positivo. */
void imprime_r (struct racional r)
{
  if (!valido_r (r))
  {
    printf ("INVALIDO");
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

/* Retorna a soma dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */
struct racional soma_r (struct racional r1, struct racional r2)
{
  struct racional result;
    if (r1.den == 0 || r2.den == 0) 
    {
      result.den = 0;
      return result;
    }
  
  result.num = (r2.den * r1.num) + (r1.den * r2.num);
  result.den = (r1.den * r2.den);

  return simplifica_r (result);
}

/* Retorna a subtração dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */
struct racional subtrai_r (struct racional r1, struct racional r2)
{
  struct racional result;
    if (r1.den == 0 || r2.den == 0)
    {
      result.den = 0;
      return result;
    }

  result.num = (r2.den * r1.num) - (r1.den * r2.num);
  result.den = (r1.den * r2.den);

  return simplifica_r (result);
}

/* Retorna a multiplicação dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */
struct racional multiplica_r (struct racional r1, struct racional r2)
{
  struct racional result;
    if (r1.den == 0 || r2.den == 0)
    {
      result.den = 0;
      return result;
    }

  result.num = (r1.num * r2.num);
  result.den = (r1.den * r2.den);

  return simplifica_r (result);
}

/* Retorna a divisão dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido.
 * observe que a divisão com r1 e r2 válidos pode gerar um racional inválido */
struct racional divide_r (struct racional r1, struct racional r2)
{
  struct racional result;
    if (r1.den == 0 || r2.den == 0 || r2.num == 0)
    {
      result.den = 0;
      return result;
    }
  
  result.num = (r1.num * r2.den);
  result.den = (r1.den * r2.num);

  return simplifica_r (result);
}

