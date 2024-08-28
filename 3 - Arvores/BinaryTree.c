#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct NoArvore {
  int conteudo;
  struct NoArvore *esq;
  struct NoArvore *dir;
};

struct NoArvore *criarNo(int dado) {
  struct NoArvore *novoNo = (struct NoArvore*)malloc(sizeof(struct NoArvore));
  if (novoNo == NULL)
  {
    printf("Não foi possível criar o novo nó\n. Saindo...");
    exit(-1);
  }
  novoNo -> conteudo = dado;
  novoNo -> esq = NULL;
  novoNo -> dir = NULL;
  return novoNo;
}

struct NoArvore *inserirNaArv(struct NoArvore *raiz, int dado) {
  if (raiz == NULL)
  {
    raiz = criarNo(dado);
  }
  else
  {
    if (dado <= raiz -> conteudo)
    {
      raiz -> esq = inserirNaArv(raiz -> esq, dado);
    }
    else
    {
      raiz -> dir = inserirNaArv(raiz -> dir, dado);
    }
  }
  return raiz;
}

struct NoArvore *encontrarMinimo(struct NoArvore *raiz)
{
    struct NoArvore *atual = raiz;
    while (atual -> esq != NULL)
    {
      atual = atual -> esq;
    }
    return atual;
}

struct NoArvore *excluirNaArv(struct NoArvore *raiz, int valor) {
  if (raiz == NULL) {
    return raiz;
  }
  if (valor < raiz -> conteudo)
    excluirNaArv(raiz -> esq, valor);
  else if (valor > raiz -> conteudo)
    excluirNaArv(raiz -> dir, valor);
  else
  {
    // CASO 1: Nó folha ou o filho esquerda não existe.
    if (raiz -> esq == NULL)
    {
      struct NoArvore *temp = raiz -> dir;
      free(raiz);
      return temp;
    }
    else if (raiz -> dir == NULL)
    {
      struct NoArvore *temp = raiz -> esq;
      free(raiz);
      return temp;
    }
    // CASO 2: Nó com dois filhos, encontrar menor valor na subárvore direita
    struct NoArvore *temp = encontrarMinimo(raiz -> dir);
    raiz -> conteudo = temp -> conteudo;
    raiz -> dir = excluirNaArv(raiz -> dir, temp -> conteudo);
  }
  return raiz;
}

void percorrerEmOrdem(struct NoArvore *raiz)
{
  if (raiz != NULL)
  {
      percorrerEmOrdem(raiz -> esq);
      printf("%i", raiz -> conteudo);
      percorrerEmOrdem(raiz -> esq);
  }
}

void percorrerPreOrdem(struct NoArvore *raiz)
{
  if (raiz != NULL)
  {
      printf("%d ", raiz -> conteudo);
      percorrerEmOrdem(raiz -> esq);
      percorrerEmOrdem(raiz -> dir);
  }
}

void percorrerPosOrdem(struct NoArvore *raiz)
{
  if (raiz != NULL)
  {
      percorrerEmOrdem(raiz -> esq);
      percorrerEmOrdem(raiz -> dir);
      printf("%d ", raiz -> conteudo);
  }
}

// Função auxiliar para imprimir um caractere precedido por uma quantidade específica de espaços
void imprimeNo(int c, int b)
{
  int i;
  for (i = 0; i < b; i++)
      printf("   ");
  printf("%i\n", c);
}

// Função para exibir a árvore no formato esquerda-raiz-direita segundo Sedgewick
void mostraArvore(struct NoArvore *a, int b)
{
  if (a == NULL)
  {
      return;
  }
  mostraArvore(a -> dir, b + 1);
  imprimeNo(a -> conteudo, b); // Convertendo para caractere para imprimir
  mostraArvore(a -> esq, b + 1);
}

int main()
{
  struct NoArvore *raiz = NULL;

  // Inserindo elementos na árvore
  raiz = inserirNaArv(raiz, 1);
  raiz = inserirNaArv(raiz, 2);
  raiz = inserirNaArv(raiz, 3);
  raiz = inserirNaArv(raiz, 4);
  raiz = inserirNaArv(raiz, 5);
  raiz = inserirNaArv(raiz, 6);
  raiz = inserirNaArv(raiz, 7);
  raiz = inserirNaArv(raiz, 8);
  raiz = inserirNaArv(raiz, 9);
  raiz = inserirNaArv(raiz, 10);

  mostraArvore(raiz, 3);
  excluirNaArv(raiz,5);
  mostraArvore(raiz,3);
}
