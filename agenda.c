#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTATOS 100
#define TAM_NOME 50
#define TAM_TELEFONE 15
#define ARQUIVO "contatos.txt"

// Estrutura para armazenar os dados de um contato
typedef struct {
    char nome[TAM_NOME];
    char telefone[TAM_TELEFONE];
} Contato;

// Funções
void adicionarContato(Contato contatos[], int *numContatos);
void listarContatos(Contato contatos[], int numContatos);
void buscarContato(Contato contatos[], int numContatos);
void salvarContatos(Contato contatos[], int numContatos);
void carregarContatos(Contato contatos[], int *numContatos);

int main() {
    Contato contatos[MAX_CONTATOS];
    int numContatos = 0;
    int opcao;

    // Carrega os contatos do arquivo para o vetor
    carregarContatos(contatos, &numContatos);

    do {
        printf("\n--- Sistema de Gerenciamento de Contatos ---\n");
        printf("1. Adicionar contato\n");
        printf("2. Listar contatos\n");
        printf("3. Buscar contato\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                adicionarContato(contatos, &numContatos);
                break;
            case 2:
                listarContatos(contatos, numContatos);
                break;
            case 3:
                buscarContato(contatos, numContatos);
                break;
            case 4:
                salvarContatos(contatos, numContatos);
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 4);

    return 0;
}

// Função para adicionar um contato
void adicionarContato(Contato contatos[], int *numContatos) {
    if (*numContatos >= MAX_CONTATOS) {
        printf("Limite de contatos atingido!\n");
        return;
    }

    printf("Digite o nome do contato: ");
    scanf(" %[^\n]s", contatos[*numContatos].nome);
    printf("Digite o telefone do contato: ");
    scanf(" %[^\n]s", contatos[*numContatos].telefone);

    (*numContatos)++;
    printf("Contato adicionado com sucesso!\n");
}

// Função para listar todos os contatos
void listarContatos(Contato contatos[], int numContatos) {
    if (numContatos == 0) {
        printf("Nenhum contato encontrado!\n");
        return;
    }

    printf("\n--- Lista de Contatos ---\n");
    for (int i = 0; i < numContatos; i++) {
        printf("Contato %d:\n", i + 1);
        printf("Nome: %s\n", contatos[i].nome);
        printf("Telefone: %s\n", contatos[i].telefone);
    }
}

// Função para buscar um contato pelo nome
void buscarContato(Contato contatos[], int numContatos) {
    char nomeBusca[TAM_NOME];
    printf("Digite o nome do contato para buscar: ");
    scanf(" %[^\n]s", nomeBusca);

    for (int i = 0; i < numContatos; i++) {
        if (strcmp(contatos[i].nome, nomeBusca) == 0) {
            printf("Contato encontrado:\n");
            printf("Nome: %s\n", contatos[i].nome);
            printf("Telefone: %s\n", contatos[i].telefone);
            return;
        }
    }

    printf("Contato nao encontrado!\n");
}

// Função para salvar os contatos no arquivo
void salvarContatos(Contato contatos[], int numContatos) {
    FILE *arquivo = fopen(ARQUIVO, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar os contatos!\n");
        return;
    }

    for (int i = 0; i < numContatos; i++) {
        fprintf(arquivo, "%s;%s\n", contatos[i].nome, contatos[i].telefone);
    }

    fclose(arquivo);
    printf("Contatos salvos com sucesso!\n");
}

// Função para carregar os contatos do arquivo para o vetor
void carregarContatos(Contato contatos[], int *numContatos) {
    FILE *arquivo = fopen(ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Nenhum arquivo encontrado, criando um novo.\n");
        return;
    }

    while (fscanf(arquivo, " %[^;];%[^\n]\n", contatos[*numContatos].nome, contatos[*numContatos].telefone) == 2) {
        (*numContatos)++;
    }

    fclose(arquivo);
}
