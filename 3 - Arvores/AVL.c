#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int chave;
    struct No *esquerda;
    struct No *direita;
    int altura;
} No;

int obterAltura(No *n) {
    if (n == NULL)
        return 0;
    return n->altura;
}

int maximo(int a, int b) {
    return (a > b) ? a : b;
}

No* criarNo(int chave) {
    No* no = (No*) malloc(sizeof(No));
    no->chave = chave;
    no->esquerda = NULL;
    no->direita = NULL;
    no->altura = 1;
    return no;
}

No* rotacaoDireita(No* y) {
    No* x = y->esquerda;
    No* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = maximo(obterAltura(y->esquerda), obterAltura(y->direita)) + 1;
    x->altura = maximo(obterAltura(x->esquerda), obterAltura(x->direita)) + 1;

    return x;
}

No* rotacaoEsquerda(No* x) {
    No* y = x->direita;
    No* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = maximo(obterAltura(x->esquerda), obterAltura(x->direita)) + 1;
    y->altura = maximo(obterAltura(y->esquerda), obterAltura(y->direita)) + 1;

    return y;
}

int obterBalanceamento(No *n) {
    if (n == NULL)
        return 0;
    return obterAltura(n->esquerda) - obterAltura(n->direita);
}

No* inserir(No* no, int chave) {
    if (no == NULL)
        return criarNo(chave);

    if (chave < no->chave)
        no->esquerda = inserir(no->esquerda, chave);
    else if (chave > no->chave)
        no->direita = inserir(no->direita, chave);
    else
        return no;

    no->altura = 1 + maximo(obterAltura(no->esquerda), obterAltura(no->direita));

    int balanceamento = obterBalanceamento(no);

    if (balanceamento > 1 && chave < no->esquerda->chave)
        return rotacaoDireita(no);

    if (balanceamento < -1 && chave > no->direita->chave)
        return rotacaoEsquerda(no);

    if (balanceamento > 1 && chave > no->esquerda->chave) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    if (balanceamento < -1 && chave < no->direita->chave) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

void preOrdem(No *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->chave);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

int main() {
    No *raiz = NULL;

    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 25);

    printf("Árvore AVL em pré-ordem: \n");
    preOrdem(raiz);

    return 0;
}
