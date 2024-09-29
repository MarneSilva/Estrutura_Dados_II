#include <stdio.h>
#include <stdlib.h>

typedef enum { VERMELHO, PRETO } Cor;

typedef struct No {
    int dado;
    Cor cor;
    struct No* esquerda, * direita, * pai;
} No;

No* criarNo(int dado) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = dado;
    novoNo->cor = VERMELHO;
    novoNo->esquerda = novoNo->direita = novoNo->pai = NULL;
    return novoNo;
}

No* raiz = NULL;

// Funções de rotação

void rotacionarEsquerda(No** raiz, No* x) {
    No* y = x->direita;
    x->direita = y->esquerda;

    if (y->esquerda != NULL)
        y->esquerda->pai = x;

    y->pai = x->pai;

    if (x->pai == NULL)
        (*raiz) = y;
    else if (x == x->pai->esquerda)
        x->pai->esquerda = y;
    else
        x->pai->direita = y;

    y->esquerda = x;
    x->pai = y;
}

void rotacionarDireita(No** raiz, No* y) {
    No* x = y->esquerda;
    y->esquerda = x->direita;

    if (x->direita != NULL)
        x->direita->pai = y;

    x->pai = y->pai;

    if (y->pai == NULL)
        (*raiz) = x;
    else if (y == y->pai->direita)
        y->pai->direita = x;
    else
        y->pai->esquerda = x;

    x->direita = y;
    y->pai = x;
}

// Função para balancear a árvore após a inserção
void corrigirInsercao(No** raiz, No* pt) {
    No* pai_pt = NULL;
    No* avo_pt = NULL;

    while ((pt != *raiz) && (pt->cor != PRETO) && (pt->pai->cor == VERMELHO)) {
        pai_pt = pt->pai;
        avo_pt = pt->pai->pai;

        /* Caso A: O pai de pt é filho esquerdo do avô de pt */
        if (pai_pt == avo_pt->esquerda) {
            No* tio_pt = avo_pt->direita;

            /* Caso 1: O tio de pt é vermelho, apenas recolorir */
            if (tio_pt != NULL && tio_pt->cor == VERMELHO) {
                avo_pt->cor = VERMELHO;
                pai_pt->cor = PRETO;
                tio_pt->cor = PRETO;
                pt = avo_pt;
            } else {
                /* Caso 2: pt é filho direito, rotação à esquerda */
                if (pt == pai_pt->direita) {
                    rotacionarEsquerda(raiz, pai_pt);
                    pt = pai_pt;
                    pai_pt = pt->pai;
                }

                /* Caso 3: pt é filho esquerdo, rotação à direita */
                rotacionarDireita(raiz, avo_pt);
                Cor temp = pai_pt->cor;
                pai_pt->cor = avo_pt->cor;
                avo_pt->cor = temp;
                pt = pai_pt;
            }
        }
        /* Caso B: O pai de pt é filho direito do avô de pt */
        else {
            No* tio_pt = avo_pt->esquerda;

            /* Caso 1: O tio de pt é vermelho, apenas recolorir */
            if (tio_pt != NULL && tio_pt->cor == VERMELHO) {
                avo_pt->cor = VERMELHO;
                pai_pt->cor = PRETO;
                tio_pt->cor = PRETO;
                pt = avo_pt;
            } else {
                /* Caso 2: pt é filho esquerdo, rotação à direita */
                if (pt == pai_pt->esquerda) {
                    rotacionarDireita(raiz, pai_pt);
                    pt = pai_pt;
                    pai_pt = pt->pai;
                }

                /* Caso 3: pt é filho direito, rotação à esquerda */
                rotacionarEsquerda(raiz, avo_pt);
                Cor temp = pai_pt->cor;
                pai_pt->cor = avo_pt->cor;
                avo_pt->cor = temp;
                pt = pai_pt;
            }
        }
    }

    (*raiz)->cor = PRETO;
}

// Função para inserir um novo nó na árvore
void inserir(No** raiz, int dado) {
    No* novoNo = criarNo(dado);

    if (*raiz == NULL) {
        *raiz = novoNo;
        novoNo->cor = PRETO;
    } else {
        No* pai = NULL;
        No* temp = *raiz;

        while (temp != NULL) {
            pai = temp;
            if (dado < temp->dado)
                temp = temp->esquerda;
            else if (dado > temp->dado)
                temp = temp->direita;
            else
                return; // Evitar duplicatas
        }

        novoNo->pai = pai;

        if (dado < pai->dado)
            pai->esquerda = novoNo;
        else
            pai->direita = novoNo;

        corrigirInsercao(raiz, novoNo);
    }
}

// Funções de travessia da árvore
void preOrdem(No* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->dado);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->dado);
        emOrdem(raiz->direita);
    }
}

void posOrdem(No* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("%d ", raiz->dado);
    }
}

// Função principal
int main() {
    inserir(&raiz, 10);
    inserir(&raiz, 20);
    inserir(&raiz, 30);
    inserir(&raiz, 15);
    inserir(&raiz, 25);

    printf("Travessia em Pré-Ordem:\n");
    preOrdem(raiz);
    printf("\n");

    printf("Travessia em Ordem:\n");
    emOrdem(raiz);
    printf("\n");

    printf("Travessia em Pós-Ordem:\n");
    posOrdem(raiz);
    printf("\n");

    return 0;
}
