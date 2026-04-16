/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

struct racional {
  long num;          
  long den;          
};

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/

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

/* Simplifica o número racional indicado no parâmetro.
 * Por exemplo, se o número for 10/8 muda para 5/4.
 * Retorna 1 em sucesso e 0 se r for inválido ou o ponteiro for nulo.
 * Se ambos numerador e denominador forem negativos, o resultado é positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador. */

int simplifica_r (struct racional *r)
{
  if (r->den == 0)
  return r;
  
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

/* implemente as demais funções de racional.h aqui */

/* estrutura "opaca" que representa um número racional */
/* serve para abstrair totalmente o tipo struct racional para o usuario */
/* a struct de fato eh implementada no arquivo racional.c */
struct racional;

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
struct racional *cria_r (long numerador, long denominador);

/* Libera a memória alocada para o racional apontado por r */
void destroi_r (struct racional **r);

/* Retorna 1 se o racional r for válido ou 0 se for inválido. Um racional
 * é inválido se o denominador for zero ou se ele não tiver sido alocado. */
int valido_r (struct racional *r);

/* Imprime um racional r, respeitando estas regras:
   - o racional deve estar na forma simplificada;
   - não use espacos em branco e não mude de linha;
   - o formato de saída deve ser "num/den", a menos dos casos abaixo;
     - se o ponteiro for nulo, imprime a mensagem "NULL";
     - se o racional for inválido, imprime a mensagem "NaN" (Not a Number);
     - se o numerador for 0, imprime somente "0";
     - se o denominador for 1, imprime somente o numerador;
     - se o numerador e denominador forem iguais, imprime somente "1";
     - se o racional for negativo, o sinal é impresso antes do número;
     - se numerador e denominador forem negativos, o racional é positivo. */
void imprime_r (struct racional *r);

/* Compara dois números racionais r1 e r2.
 * Retorna -2 se r1 ou r2 for inválido ou se o respectivo ponteiro for nulo.
 * Retorna -1 se r1 < r2; 0 se r1 = r2; 1 se r1 > r2.
 * Atenção: faça a comparação normalizando os denominadores pelo MMC.
 * Fazer a comparação baseado na divisão do numerador pelo denominador
 * pode gerar erro de arredondamento e falsear o resultado. */
int compara_r (struct racional *r1, struct racional *r2);

/* Coloca em *r3 a soma simplificada dos racionais *r1 e *r2.
 * Retorna 1 em sucesso e 0 se r1 ou r2 for inválido ou um ponteiro for nulo. */
int soma_r (struct racional *r1, struct racional *r2, struct racional *r3);

/* Coloca em *r3 a diferença simplificada dos racionais *r1 e *r2.
 * Retorna 1 em sucesso e 0 se r1 ou r2 for inválido ou um ponteiro for nulo. */
int subtrai_r (struct racional *r1, struct racional *r2, struct racional *r3);

/* Coloca em *r3 o produto simplificado dos racionais *r1 e *r2.
 * Retorna 1 em sucesso e 0 se r1 ou r2 for inválido ou um ponteiro for nulo. */
int multiplica_r (struct racional *r1, struct racional *r2, struct racional *r3);

/* Coloca em *r3 a divisão simplificada do racional *r1 por *r2.
 * Retorna 1 em sucesso e 0 se r1 ou r2 for inválido ou um ponteiro for nulo. */
int divide_r (struct racional *r1, struct racional *r2, struct racional *r3);

