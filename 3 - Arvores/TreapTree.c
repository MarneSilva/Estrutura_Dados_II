#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura de um nó da Treap
typedef struct NoTreap {
    int chave;                    // Chave do nó
    int prioridade;               // Prioridade do nó (para manter a propriedade de heap)
    struct NoTreap* esquerda;     // Filho à esquerda
    struct NoTreap* direita;      // Filho à direita
} NoTreap;

// Função para criar um novo nó da Treap
NoTreap* criarNo(int chave) {
    NoTreap* no = (NoTreap*)malloc(sizeof(NoTreap));
    no->chave = chave;
    no->prioridade = rand() % 100;  // A prioridade é escolhida aleatoriamente
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

// Função para rotacionar à direita
NoTreap* rotacionarDireita(NoTreap* y) {
    NoTreap* x = y->esquerda;
    NoTreap* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    return x;
}

// Função para rotacionar à esquerda
NoTreap* rotacionarEsquerda(NoTreap* x) {
    NoTreap* y = x->direita;
    NoTreap* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    return y;
}

// Função para inserir uma chave na Treap
NoTreap* inserir(NoTreap* raiz, int chave) {
    // Inserção padrão em uma árvore binária de busca
    if (raiz == NULL) {
        return criarNo(chave);
    }

    if (chave < raiz->chave) {
        raiz->esquerda = inserir(raiz->esquerda, chave);

        // Manter a propriedade de heap
        if (raiz->esquerda->prioridade > raiz->prioridade) {
            raiz = rotacionarDireita(raiz);
        }
    } else if (chave > raiz->chave) {
        raiz->direita = inserir(raiz->direita, chave);

        // Manter a propriedade de heap
        if (raiz->direita->prioridade > raiz->prioridade) {
            raiz = rotacionarEsquerda(raiz);
        }
    }

    return raiz;
}

// Função para buscar uma chave na Treap
NoTreap* buscar(NoTreap* raiz, int chave) {
    if (raiz == NULL || raiz->chave == chave) {
        return raiz;
    }

    if (chave < raiz->chave) {
        return buscar(raiz->esquerda, chave);
    } else {
        return buscar(raiz->direita, chave);
    }
}

// Função para remover uma chave na Treap
NoTreap* remover(NoTreap* raiz, int chave) {
    if (raiz == NULL) {
        return raiz;
    }

    if (chave < raiz->chave) {
        raiz->esquerda = remover(raiz->esquerda, chave);
    } else if (chave > raiz->chave) {
        raiz->direita = remover(raiz->direita, chave);
    } else {
        // Nós folha ou nós com apenas um filho
        if (raiz->esquerda == NULL) {
            NoTreap* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            NoTreap* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // Nó com dois filhos: fazer rotações até que o nó a ser removido vire folha
        if (raiz->esquerda->prioridade < raiz->direita->prioridade) {
            raiz = rotacionarEsquerda(raiz);
            raiz->esquerda = remover(raiz->esquerda, chave);
        } else {
            raiz = rotacionarDireita(raiz);
            raiz->direita = remover(raiz->direita, chave);
        }
    }

    return raiz;
}

// Função para imprimir a Treap (em ordem para visualização)
void imprimirTreap(NoTreap* raiz, int espaco) {
    if (raiz == NULL) {
        return;
    }

    espaco += 10;

    imprimirTreap(raiz->direita, espaco);

    printf("\n");
    for (int i = 10; i < espaco; i++) {
        printf(" ");
    }
    printf("%d (p=%d)\n", raiz->chave, raiz->prioridade);

    imprimirTreap(raiz->esquerda, espaco);
}

int main() {
    srand(time(0));  // Inicializar a semente para gerar prioridades aleatórias

    NoTreap* raiz = NULL;

    // Inserindo chaves de exemplo
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 80);

    printf("Treap após inserções:\n");
    imprimirTreap(raiz, 0);

    // Testando busca
    int chave = 40;
    NoTreap* resultado = buscar(raiz, chave);
    if (resultado != NULL) {
        printf("\nChave %d encontrada na Treap com prioridade %d.\n", chave, resultado->prioridade);
    } else {
        printf("\nChave %d não encontrada na Treap.\n", chave);
    }

    // Testando remoção
    raiz = remover(raiz, 50);
    printf("\nTreap após remover chave 50:\n");
    imprimirTreap(raiz, 0);

    return 0;
}
