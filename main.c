#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
} Produto;

Produto estoque[MAX];
int totalProdutos = 0;

// Funções do sistema
void adicionarProduto() {
    Produto p;
    printf("Código do produto: ");
    scanf("%d", &p.codigo);
    getchar(); // limpar buffer

    printf("Nome do produto: ");
    fgets(p.nome, 50, stdin);
    p.nome[strcspn(p.nome, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &p.quantidade);

    printf("Preço: ");
    scanf("%f", &p.preco);

    estoque[totalProdutos++] = p;
    printf("Produto adicionado com sucesso!\n");
}

void listarProdutos() {
    printf("\n=== Lista de Produtos ===\n");
    for (int i = 0; i < totalProdutos; i++) {
        printf("Código: %d | Nome: %s | Qtd: %d | Preço: R$ %.2f\n",
            estoque[i].codigo, estoque[i].nome,
            estoque[i].quantidade, estoque[i].preco);
    }
}

void buscarProduto() {
    int cod;
    printf("Digite o código do produto: ");
    scanf("%d", &cod);

    for (int i = 0; i < totalProdutos; i++) {
        if (estoque[i].codigo == cod) {
            printf("Produto encontrado:\n");
            printf("Código: %d\n", estoque[i].codigo);
            printf("Nome: %s\n", estoque[i].nome);
            printf("Quantidade: %d\n", estoque[i].quantidade);
            printf("Preço: R$ %.2f\n", estoque[i].preco);
            return;
        }
    }
    printf("Produto não encontrado!\n");
}

void atualizarQuantidade() {
    int cod, qtd;
    printf("Digite o código do produto: ");
    scanf("%d", &cod);

    for (int i = 0; i < totalProdutos; i++) {
        if (estoque[i].codigo == cod) {
            printf("Quantidade atual: %d\n", estoque[i].quantidade);
            printf("Digite a quantidade a adicionar (negativo para retirar): ");
            scanf("%d", &qtd);
            estoque[i].quantidade += qtd;
            if (estoque[i].quantidade < 0) estoque[i].quantidade = 0;
            printf("Quantidade atualizada!\n");
            return;
        }
    }
    printf("Produto não encontrado!\n");
}

void removerProduto() {
    int cod;
    printf("Digite o código do produto a remover: ");
    scanf("%d", &cod);
    for (int i = 0; i < totalProdutos; i++) {
        if (estoque[i].codigo == cod) {
            for (int j = i; j < totalProdutos - 1; j++) {
                estoque[j] = estoque[j + 1];
            }
            totalProdutos--;
            printf("Produto removido com sucesso!\n");
            return;
        }
    }
    printf("Produto não encontrado!\n");
}

void ordenarPorNome() {
    for (int i = 0; i < totalProdutos - 1; i++) {
        for (int j = i + 1; j < totalProdutos; j++) {
            if (strcmp(estoque[i].nome, estoque[j].nome) > 0) {
                Produto temp = estoque[i];
                estoque[i] = estoque[j];
                estoque[j] = temp;
            }
        }
    }
    printf("Produtos ordenados por nome!\n");
}

void ordenarPorQuantidade() {
    for (int i = 0; i < totalProdutos - 1; i++) {
        for (int j = i + 1; j < totalProdutos; j++) {
            if (estoque[i].quantidade > estoque[j].quantidade) {
                Produto temp = estoque[i];
                estoque[i] = estoque[j];
                estoque[j] = temp;
            }
        }
    }
    printf("Produtos ordenados por quantidade!\n");
}

void exportarCSV() {
    FILE *file = fopen("estoque.csv", "w");
    if (!file) {
        printf("Erro ao criar CSV!\n");
        return;
    }
    fprintf(file, "Codigo,Nome,Quantidade,Preco\n");
    for (int i = 0; i < totalProdutos; i++) {
        fprintf(file, "%d,%s,%d,%.2f\n",
                estoque[i].codigo, estoque[i].nome,
                estoque[i].quantidade, estoque[i].preco);
    }
    fclose(file);
    printf("Exportado para estoque.csv com sucesso!\n");
}

void salvarEstoque() {
    FILE *file = fopen("estoque.txt", "w");
    if (!file) return;
    for (int i = 0; i < totalProdutos; i++) {
        fprintf(file, "%d,%s,%d,%.2f\n",
                estoque[i].codigo, estoque[i].nome,
                estoque[i].quantidade, estoque[i].preco);
    }
    fclose(file);
}

void carregarEstoque() {
    FILE *file = fopen("estoque.txt", "r");
    if (!file) return;
    Produto p;
    while (fscanf(file, "%d,%49[^,],%d,%f\n",
                  &p.codigo, p.nome, &p.quantidade, &p.preco) != EOF) {
        estoque[totalProdutos++] = p;
    }
    fclose(file);
}

void salvarEstoqueBinario() {
    FILE *file = fopen("estoque.dat", "wb");
    if (!file) return;
    fwrite(&totalProdutos, sizeof(int), 1, file);
    fwrite(estoque, sizeof(Produto), totalProdutos, file);
    fclose(file);
}

void carregarEstoqueBinario() {
    FILE *file = fopen("estoque.dat", "rb");
    if (!file) return;
    fread(&totalProdutos, sizeof(int), 1, file);
    fread(estoque, sizeof(Produto), totalProdutos, file);
    fclose(file);
}

// Função principal
int main() {
    int opcao;
    carregarEstoque();
    carregarEstoqueBinario();

    do {
        printf("\n===== MENU ESTOQUE =====\n");
        printf("1 - Adicionar Produto\n");
        printf("2 - Listar Produtos\n");
        printf("3 - Buscar Produto por Código\n");
        printf("4 - Atualizar Quantidade de Produto\n");
        printf("5 - Remover Produto\n");
        printf("6 - Ordenar por Nome\n");
        printf("7 - Ordenar por Quantidade\n");
        printf("8 - Exportar para CSV\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: adicionarProduto(); break;
            case 2: listarProdutos(); break;
            case 3: buscarProduto(); break;
            case 4: atualizarQuantidade(); break;
            case 5: removerProduto(); break;
            case 6: ordenarPorNome(); break;
            case 7: ordenarPorQuantidade(); break;
            case 8: exportarCSV(); break;
            case 0:
                salvarEstoque();
                salvarEstoqueBinario();
                printf("Saindo... Dados salvos.\n");
                break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
