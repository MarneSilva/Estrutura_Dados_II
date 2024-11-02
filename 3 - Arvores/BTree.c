#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define T 2  // Ordem mínima da árvore B

// Estrutura do nó da árvore B
typedef struct NoArvoreB {
    int chaves[2 * T - 1];        // Array de chaves
    struct NoArvoreB* filhos[2 * T]; // Ponteiros para os filhos
    int n;                        // Número de chaves atualmente no nó
    bool folha;                   // Verdadeiro se o nó é uma folha
} NoArvoreB;

// Estrutura da árvore B
typedef struct ArvoreB {
    NoArvoreB* raiz;
} ArvoreB;

// Função para criar um nó da árvore B
NoArvoreB* criarNo(bool folha) {
    NoArvoreB* no = (NoArvoreB*)malloc(sizeof(NoArvoreB));
    no->folha = folha;
    no->n = 0;
    for (int i = 0; i < 2 * T; i++) {
        no->filhos[i] = NULL;
    }
    return no;
}

// Função para criar uma árvore B
ArvoreB* criarArvoreB() {
    ArvoreB* arvore = (ArvoreB*)malloc(sizeof(ArvoreB));
    arvore->raiz = criarNo(true);  // A raiz começa como uma folha
    return arvore;
}

// Função para buscar uma chave em um nó da árvore B
NoArvoreB* buscar(NoArvoreB* no, int chave) {
    int i = 0;
    while (i < no->n && chave > no->chaves[i]) {
        i++;
    }

    if (i < no->n && chave == no->chaves[i]) {
        return no;  // A chave foi encontrada
    }

    if (no->folha) {
        return NULL;  // Se for folha, a chave não está na árvore
    }

    return buscar(no->filhos[i], chave);  // Buscar no filho apropriado
}

// Função para dividir o filho y do nó x na posição i
void dividirFilho(NoArvoreB* x, int i, NoArvoreB* y) {
    NoArvoreB* z = criarNo(y->folha);
    z->n = T - 1;

    for (int j = 0; j < T - 1; j++) {
        z->chaves[j] = y->chaves[j + T];
    }

    if (!y->folha) {
        for (int j = 0; j < T; j++) {
            z->filhos[j] = y->filhos[j + T];
        }
    }

    y->n = T - 1;

    for (int j = x->n; j >= i + 1; j--) {
        x->filhos[j + 1] = x->filhos[j];
    }

    x->filhos[i + 1] = z;

    for (int j = x->n - 1; j >= i; j--) {
        x->chaves[j + 1] = x->chaves[j];
    }

    x->chaves[i] = y->chaves[T - 1];
    x->n++;
}

// Função auxiliar para inserir uma nova chave em um nó não cheio
void inserirNaoCheio(NoArvoreB* x, int chave) {
    int i = x->n - 1;

    if (x->folha) {
        while (i >= 0 && chave < x->chaves[i]) {
            x->chaves[i + 1] = x->chaves[i];
            i--;
        }
        x->chaves[i + 1] = chave;
        x->n++;
    } else {
        while (i >= 0 && chave < x->chaves[i]) {
            i--;
        }
        i++;
        if (x->filhos[i]->n == 2 * T - 1) {
            dividirFilho(x, i, x->filhos[i]);
            if (chave > x->chaves[i]) {
                i++;
            }
        }
        inserirNaoCheio(x->filhos[i], chave);
    }
}

// Função para inserir uma chave na árvore B
void inserir(ArvoreB* arvore, int chave) {
    NoArvoreB* raiz = arvore->raiz;
    if (raiz->n == 2 * T - 1) {
        NoArvoreB* s = criarNo(false);
        s->filhos[0] = raiz;
        dividirFilho(s, 0, raiz);
        int i = 0;
        if (chave > s->chaves[0]) {
            i++;
        }
        inserirNaoCheio(s->filhos[i], chave);
        arvore->raiz = s;
    } else {
        inserirNaoCheio(raiz, chave);
    }
}

// Função para imprimir a árvore B (para fins de teste)
void imprimirArvoreB(NoArvoreB* no, int profundidade) {
    int i;
    for (i = 0; i < no->n; i++) {
        if (!no->folha) {
            imprimirArvoreB(no->filhos[i], profundidade + 1);
        }
        printf("%*s%d\n", profundidade * 4, "", no->chaves[i]);
    }
    if (!no->folha) {
        imprimirArvoreB(no->filhos[i], profundidade + 1);
    }
}

int main() {
    ArvoreB* arvore = criarArvoreB();

    // Inserindo chaves de exemplo
    inserir(arvore, 10);
    inserir(arvore, 20);
    inserir(arvore, 5);
    inserir(arvore, 6);
    inserir(arvore, 12);
    inserir(arvore, 30);
    inserir(arvore, 7);
    inserir(arvore, 17);

    printf("Árvore B:\n");
    imprimirArvoreB(arvore->raiz, 0);

    // Testando busca
    int chave = 6;
    NoArvoreB* resultado = buscar(arvore->raiz, chave);
    if (resultado != NULL) {
        printf("Chave %d encontrada na árvore.\n", chave);
    } else {
        printf("Chave %d não encontrada na árvore.\n", chave);
    }

    return 0;
}
