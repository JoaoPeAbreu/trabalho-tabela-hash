//Estrutura programa Tabela Hash - Professor Lucas.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO_HASH 101

typedef struct Contato {
    char nome[50];
    char telefone[15];
    struct Contato* proximo;
} Contato;

Contato* tabelaHash[TAMANHO_HASH];

unsigned int funcaoHash(const char* nome) {
    unsigned int hash = 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        hash = (hash + nome[i]) % TAMANHO_HASH;
    }
    return hash;
}

void adicionarContato() {
    char nome[50], telefone[15];
    printf("Nome: ");
    scanf(" %[^\n]", nome);
    printf("Telefone: ");
    scanf(" %[^\n]", telefone);

    unsigned int indice = funcaoHash(nome);
    Contato* novoContato = (Contato*)malloc(sizeof(Contato));
    strcpy(novoContato->nome, nome);
    strcpy(novoContato->telefone, telefone);
    novoContato->proximo = tabelaHash[indice];
    tabelaHash[indice] = novoContato;

    printf("Contato adicionado com sucesso.\n");
}

void buscarContato() {
    char nome[50];
    printf("Nome: ");
    scanf(" %[^\n]", nome);

    unsigned int indice = funcaoHash(nome);
    Contato* atual = tabelaHash[indice];
    clock_t inicio = clock();

    while (atual) {
        if (strcmp(atual->nome, nome) == 0) {
            clock_t fim = clock();
            double tempoBusca = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
            printf("Telefone de %s: %s (tempo de busca: %.2f ms)\n", nome, atual->telefone, tempoBusca);
            return;
        }
        atual = atual->proximo;
    }
    printf("Contato nao encontrado.\n");
}

void removerContato() {
    char nome[50];
    printf("Nome: ");
    scanf(" %[^\n]", nome);

    unsigned int indice = funcaoHash(nome);
    Contato* atual = tabelaHash[indice];
    Contato* anterior = NULL;

    while (atual) {
        if (strcmp(atual->nome, nome) == 0) {
            if (anterior) {
                anterior->proximo = atual->proximo;
            } else {
                tabelaHash[indice] = atual->proximo;
            }
            free(atual);
            printf("Contato removido com sucesso.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Contato nao encontrado.\n");
}

void exibirContatos() {
    printf("Lista de contatos:\n");
    for (int i = 0; i < TAMANHO_HASH; i++) {
        Contato* atual = tabelaHash[i];
        while (atual) {
            printf("Nome: %s, Telefone: %s\n", atual->nome, atual->telefone);
            atual = atual->proximo;
        }
    }
}

int main() {
    int opcao;

    for (int i = 0; i < TAMANHO_HASH; i++) {
        tabelaHash[i] = NULL;
    }

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opcao: ");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarContato();
                break;
            case 2:
                buscarContato();
                break;
            case 3:
                removerContato();
                break;
            case 4:
                exibirContatos();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    for (int i = 0; i < TAMANHO_HASH; i++) {
        Contato* atual = tabelaHash[i];
        while (atual) {
            Contato* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }

    return 0;
}