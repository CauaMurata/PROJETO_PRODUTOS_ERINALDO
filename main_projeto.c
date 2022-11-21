#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
  char codigo[5];
  char nome[30];
  char descricao[50];
  float preco;
  int quantidade_estoque;
  struct no *proximo;
}No;

typedef struct{
  No *inicio;
  int tam;
}Produto;

criar_produto(Produto *produto){
  produto->inicio=NULL;
  produto->tam=0;
}

void cadastrar(Produto *produto, char codigo[5], char nome[30], char descricao[50], float preco, int quantidade_estoque){
  No *novo = malloc(sizeof(No));

   if(novo){
    strcpy(novo->codigo, codigo);
    strcpy(novo->nome, nome);
    strcpy(novo->descricao, descricao);
    novo->preco = preco;
    novo->quantidade_estoque = quantidade_estoque;
    novo->proximo = produto->inicio;
    produto->inicio = novo;
    produto->tam++;
  }
}

void exibir(Produto produto){
  No *no = produto.inicio;
  printf("\nProdutos: \n");
  printf("----------------------\n");
  while(no){
    printf("Codigo   : %s\n",no->codigo);
    printf("Nome     : %s\n",no->nome);
    printf("Descrição: %s\n",no->descricao);
    printf("Preço    : %0.1f R$\n",no->preco);
    printf("Estoque  : %d\n",no->quantidade_estoque);
    printf("----------------------\n");
    no = no->proximo;
  }
}

void aplicar_desconto(Produto produto,int desconto){
  No *aux = produto.inicio;

  while(aux){
    aux->preco=aux->preco*desconto/100;
    aux=aux->proximo;
  }
  
  aux = produto.inicio;
  printf("\nProdutos com %d%% de desconto: \n",desconto);
  printf("----------------------\n");
  while(aux){
    printf("Codigo   : %s\n",aux->codigo);
    printf("Nome     : %s\n",aux->nome);
    printf("Descrição: %s\n",aux->descricao);
    printf("Preço    : %0.1f R$\n",aux->preco);
    printf("Estoque  : %d\n",aux->quantidade_estoque);
    printf("----------------------\n");
    aux = aux->proximo;
  }
}

void comprar_produto(Produto produto,char codigo[5]){
  No *aux = produto.inicio;
  int opcao;

  while(aux && strcmp(aux->codigo, codigo)!=0)
    aux=aux->proximo;
  if(aux){
    system("clear");
    printf("Produto encontrado: \n");
    printf("----------------------\n");
    printf("Codigo   : %s\n",aux->codigo);
    printf("Nome     : %s\n",aux->nome);
    printf("Descrição: %s\n",aux->descricao);
    printf("Preço    : %0.1f R$\n",aux->preco);
    printf("Estoque  : %d\n",aux->quantidade_estoque);
    printf("----------------------\n");
    if(aux->quantidade_estoque>0){
      printf("\nDeseja comprar o produto? \n[1] SIM\n[2] NÃO\n\nOpção: ");
      scanf("%d",&opcao);
      system("clear");
      if(opcao==1)
        aux->quantidade_estoque=aux->quantidade_estoque-1;
    }else
      printf("\nProduto sem estoque.\n\n");
  }else
    printf("\nProduto não existe.\n\n");
}

void atualizar_produto(Produto produto,char codigo[5]){
  No *aux = produto.inicio;
  int remessa=0, opcao;
  float preco;
  
  while(aux && strcmp(aux->codigo, codigo)!=0)
    aux=aux->proximo;
  if(aux){
    system("clear");
    printf("Produto encontrado: \n");
    printf("----------------------\n");
    printf("Codigo   : %s\n",aux->codigo);
    printf("Nome     : %s\n",aux->nome);
    printf("Descrição: %s\n",aux->descricao);
    printf("Preço    : %0.1f R$\n",aux->preco);
    printf("Estoque  : %d\n",aux->quantidade_estoque);
    printf("----------------------\n\n");
    printf("Informe o novo preço: ");
    scanf("%f",&preco);
    printf("Informe a quantidade da nova remessa: ");
    scanf("%d",&remessa);
    system("clear");
    printf("Deseja salvar a mudança?\n");
    printf("----------------------\n");
    printf("Codigo   : %s\n",aux->codigo);
    printf("Nome     : %s\n",aux->nome);
    printf("Descrição: %s\n",aux->descricao);
    printf("Preço    : %0.1f R$\n",preco);
    printf("Estoque  : %d\n",aux->quantidade_estoque+remessa);
    printf("----------------------\n\n");
    printf("[1] SIM\n[2] NÃO\n\nOpção: ");
    scanf("%d",&opcao);
    system("clear");
    if(opcao==1){
      aux->preco=preco;
      aux->quantidade_estoque=aux->quantidade_estoque+remessa;
    }
  }else
    printf("\nProduto não existe.\n\n");
}
int main(void) {
  int opcao, tam, quant_estoque, desconto;
  float preco;
  char codigo[5], nome[30], descricao[50];
  Produto produto;

  criar_produto(&produto);
  
  do{
    printf("[1] Cadastrar Produto\n[2] Exibir Produtos\n[3] Aplicar Desconto\n[4] Atualizar Produto\n[5] Comprar Produto\n[0] Sair\n\nOpção: ");
    scanf("%d", &opcao);

    switch(opcao){
      case 1:
        if(produto.tam<5){
          system("clear");
          do{
            system("clear");
            printf("Codigo (4 numeros): ");
            scanf("%s",codigo);
            codigo[5]="\0";
          }while(strlen(codigo)>4);
          do{
            system("clear");
            printf("Nome: ");
            scanf("%s",nome);
          }while(strlen(nome)>30);
          do{
            system("clear");
            printf("Descrição: ");
            scanf("%s",descricao);
          }while(strlen(descricao)>50);
            system("clear");
            printf("Informe o preço: ");
            scanf("%f",&preco);
            system("clear");
            printf("Quantidade em estoque: ");
            scanf("%d",&quant_estoque);
            system("clear");
          cadastrar(&produto,codigo,nome,descricao,preco,quant_estoque);
          }else
            printf("\nLimite de produtos atingido\n");
          break;
      case 2:
        system("clear");
        if(produto.inicio){
          exibir(produto);
        }else
          printf("\nNão existe produtos cadastrados.\n\n");
       break;
      case 3:
        system("clear");
        if(produto.inicio){
          printf("Informe a taxa de desconto: ");
          scanf("%d",&desconto);
          aplicar_desconto(produto, desconto);
        }else
          printf("\nNão existe produtos cadastrados.\n\n");
        break;
      case 4:
        system("clear");
        if(produto.inicio){
          printf("Informe o codigo do produto que deseja atualizar: ");
          scanf("%s",codigo);
          atualizar_produto(produto,codigo);
        }else
          printf("\nNão existe produtos cadastrados.\n\n");
        break;
      case 5:
        system("clear");
        if(produto.inicio){
          printf("Informe o codigo do produto que deseje comprar: ");
          scanf("%s",codigo);
          comprar_produto(produto, codigo);
        }else
          printf("\nNão existe produtos cadastrados.\n\n");
        break;
      default:
        if(opcao!=0)
          printf("Opção inválida\n");
    }
  }while(opcao!=0);
}