#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void putrep(n,c)

int n;
int c;

/* imprime a representacao de n caracteres c */

{

  int i;

  while((n>=4)||((c=='~')&&(n>0)))
  {
    putchar('~');
    if (n < 26)
       putchar(n-1+'A');
    else
       putchar(26-1+'A');
    putchar(c);
    n = n - 26;
  }
  /* se o numero de repeticoes restantes <4 imprimir o caracter n vezes */
  for (i=n; i>0; i--)
    putchar(c);
}




void compress()

/* Encurta uma string padronizando a repeticao de caracteres,
   substitui uma sequencia de 4 ou + caracteres por ~nx, onde
   n e' a letra A para uma repeticao de x, B para duas, e as-
   sim por diante. Grupos maiores que 26 sao quebrados em 2. */

{
  int n,lastc,c;

  n = 1;
  lastc = getchar();
  while (lastc != '#')
  {
   if ((c=getchar()) == '#')
   {
     if ((n>1)||(lastc=='~'))
       putrep(n,lastc);
     else
       putchar(lastc);
   }
   else
   {
    if (c==lastc)
      n++;
    else if ((n>1)||(lastc=='~'))
         {
           putrep(n,lastc);
           n = 1;
         }
         else
           putchar(lastc);
   }
   lastc = c;
  }
}



main()
{
  compress();
}





