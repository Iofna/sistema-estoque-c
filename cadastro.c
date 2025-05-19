#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadastro.h"

Produto estoque[MAX];
int totalProdutos = 0;

void adicionarProduto() {
    Produto p;
    printf("Código do produto: ");
    scanf("%d", &p.codigo);
    getchar();
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
