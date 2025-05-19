#ifndef CADASTRO_H
#define CADASTRO_H

#define MAX 100

typedef struct {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
} Produto;

void adicionarProduto();
void listarProdutos();
void buscarProduto();
void atualizarQuantidade();
void removerProduto();
void ordenarPorNome();
void ordenarPorQuantidade();
void exportarCSV();
void salvarEstoque();
void carregarEstoque();
void salvarEstoqueBinario();
void carregarEstoqueBinario();

#endif
