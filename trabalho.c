#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PEDIDOS 1000
#define MAX_CLIENTES 1000

typedef struct {
    int idPedido;
    char descricao[100];
    int ValorTotal;
    int Quantidade;
    int idCliente;
} Pedido;

typedef struct {
    int id;
    char nome[100];
    char DataNasc[11];
    char Telefone[15];
    char Endereco[100];
    char CPF[15];
} Cliente;

typedef struct {
    char titular[100];
    char numeroCartao[17];
    char cvv[4];
    char vencimento[6];
} Cartao;

Pedido pedidos[MAX_PEDIDOS];
Cliente clientes[MAX_CLIENTES];
Cartao cartao;
int contadorPedidos = 0;
int contadorClientes = 0;

void salvarClientesEmArquivo() {
    FILE *arquivo = fopen("clientes.dat", "wb");
    if (arquivo != NULL) {
        fwrite(&contadorClientes, sizeof(int), 1, arquivo); 
        for (int i = 0; i < contadorClientes; i++) {
            fwrite(&clientes[i], sizeof(Cliente), 1, arquivo);
        }
        fclose(arquivo);
        printf("Clientes salvos com sucesso!\n");
    } else {
        printf("Erro ao salvar os clientes.\n");
    }
}

void carregarClientesDeArquivo() {
    FILE *arquivo = fopen("clientes.dat", "rb");
    if (arquivo != NULL) {
        fread(&contadorClientes, sizeof(int), 1, arquivo);
        for (int i = 0; i < contadorClientes; i++) {
            fread(&clientes[i], sizeof(Cliente), 1, arquivo);
        }
        fclose(arquivo);
        printf("Clientes carregados com sucesso!\n");
    } else {
        printf("Erro ao carregar os clientes.\n");
    }
}

void salvarPedidosEmArquivo() {
    FILE *arquivo = fopen("pedidos.dat", "wb");
    if (arquivo != NULL) {
        fwrite(&contadorPedidos, sizeof(int), 1, arquivo);
        fwrite(pedidos, sizeof(Pedido), contadorPedidos, arquivo);
        fclose(arquivo);
        printf("Pedidos salvos com sucesso!\n");
    } else {
        printf("Erro ao salvar os pedidos.\n");
    }
}

void carregarPedidosDeArquivo() {
    FILE *arquivo = fopen("pedidos.dat", "rb");
    if (arquivo != NULL) {
        fread(&contadorPedidos, sizeof(int), 1, arquivo);
        fread(pedidos, sizeof(Pedido), contadorPedidos, arquivo);
        fclose(arquivo);
        printf("Pedidos carregados com sucesso!\n");
    } else {
        printf("Erro ao carregar os pedidos.\n");
    }
}

void gerarCartaoAleatorio() {
    sprintf(cartao.titular, "Titular %d", rand() % 10000);
    sprintf(cartao.numeroCartao, "%016lld", (long long)(rand() % 1000000000) * 1000000000LL + rand() % 1000000000);
    sprintf(cartao.cvv, "%03d", rand() % 900 + 100);
    sprintf(cartao.vencimento, "%02d/%04d", rand() % 12 + 1, rand() % 30 + 2024);
}

void pagamento() {
    char senha[5];
    printf("Digite a senha para visualizar os dados do pagamento: ");
    scanf("%s", senha);

    if (strcmp(senha, "1234") == 0) {
        gerarCartaoAleatorio();
        printf("\nDados do Cartão de Crédito:\n");
        printf("Titular: %s\n", cartao.titular);
        printf("Número do Cartão: %s\n", cartao.numeroCartao);
        printf("CVV: %s\n", cartao.cvv);
        printf("Vencimento: %s\n", cartao.vencimento);
    } else {
        printf("Senha incorreta. Acesso negado.\n");
    }
    system("pause");
    system("cls");
}

void acrescentarPedido() {
    if (contadorPedidos < MAX_PEDIDOS) {
        Pedido novo;
        novo.idPedido = contadorPedidos + 1;

        printf("Digite o ID do Cliente para o pedido: ");
        scanf("%d", &novo.idCliente);

        getchar();
        printf("Digite a descrição do pedido: ");
        fgets(novo.descricao, sizeof(novo.descricao), stdin);
        novo.descricao[strcspn(novo.descricao, "\n")] = 0;

        printf("Digite o valor total do pedido: ");
        scanf("%d", &novo.ValorTotal);

        printf("Digite a quantidade do pedido: ");
        scanf("%d", &novo.Quantidade);

        pedidos[contadorPedidos++] = novo;
        salvarPedidosEmArquivo();
        printf("Pedido criado: ID: %d - Descrição: %s - Valor Total: %d - Quantidade: %d - Cliente ID: %d\n",
               novo.idPedido, novo.descricao, novo.ValorTotal, novo.Quantidade, novo.idCliente);
    } else {
        printf("Limite de pedidos atingido.\n");
    }
    system("pause");
    system("cls");
}

void listarPedido() {
    if (contadorPedidos == 0) {
        printf("Nenhum pedido cadastrado.\n");
        system("pause");
        system("cls");
        return;
    }

    printf("Lista de pedidos:\n");
    for (int i = 0; i < contadorPedidos; i++) {
        printf("ID: %d - Descrição: %s - Valor Total: %d - Quantidade: %d - Cliente ID: %d\n",
               pedidos[i].idPedido, pedidos[i].descricao, pedidos[i].ValorTotal, pedidos[i].Quantidade, pedidos[i].idCliente);
    }
    system("pause");
    system("cls");
}

void atualizarPedido() {
    int id;
    printf("Digite o ID do pedido que deseja atualizar: ");
    scanf("%d", &id);

    for (int i = 0; i < contadorPedidos; i++) {
        if (pedidos[i].idPedido == id) {
            getchar();
            printf("Digite a nova descrição do pedido: ");
            fgets(pedidos[i].descricao, sizeof(pedidos[i].descricao), stdin);
            pedidos[i].descricao[strcspn(pedidos[i].descricao, "\n")] = 0;

            printf("Digite o novo valor total do pedido: ");
            scanf("%d", &pedidos[i].ValorTotal);

            printf("Digite a nova quantidade do pedido: ");
            scanf("%d", &pedidos[i].Quantidade);

            salvarPedidosEmArquivo();
            printf("Pedido atualizado: ID: %d - Descrição: %s - Novo Valor Total: %d - Nova Quantidade: %d - Cliente ID: %d\n",
                   pedidos[i].idPedido, pedidos[i].descricao, pedidos[i].ValorTotal, pedidos[i].Quantidade, pedidos[i].idCliente);
            return;
        }
    }
    printf("Pedido com ID %d não encontrado.\n", id);
    system("pause");
    system("cls");
}

void deletarPedido() {
    int id;
    printf("Digite o ID do pedido que deseja deletar: ");
    scanf("%d", &id);

    for (int i = 0; i < contadorPedidos; i++) {
        if (pedidos[i].idPedido == id) {
            for (int j = i; j < contadorPedidos - 1; j++) {
                pedidos[j] = pedidos[j + 1];
            }
            contadorPedidos--;
            salvarPedidosEmArquivo();
            printf("Pedido com ID %d deletado.\n", id);
            return;
        }
    }
    printf("Pedido com ID %d não encontrado.\n", id);
    system("pause");
    system("cls");
}

void criarCliente() {
    if (contadorClientes < MAX_CLIENTES) {
        Cliente novo;
        printf("Digite o ID do Cliente: ");
        scanf("%d", &novo.id);
        getchar();
        printf("Digite o nome do Cliente: ");
        fgets(novo.nome, sizeof(novo.nome), stdin);
        novo.nome[strcspn(novo.nome, "\n")] = 0;
        clientes[contadorClientes++] = novo;
        salvarClientesEmArquivo();
        printf("Cliente criado: ID: %d - Nome: %s\n", novo.id, novo.nome);
    } else {
        printf("Limite de clientes atingido.\n");
    }
    system("pause");
    system("cls");
}

void listarCliente() {
    printf("Lista de Clientes:\n");
    for (int i = 0; i < contadorClientes; i++) {
        printf("ID: %d - Nome: %s\n", clientes[i].id, clientes[i].nome);
    }
    system("pause");
    system("cls");
}

int main() {
    int escolha;

    carregarClientesDeArquivo();
    carregarPedidosDeArquivo();

    do {
        printf("Menu de opções:\n");
        printf("1. Criar cliente\n");
        printf("2. Listar clientes\n");
        printf("3. Criar pedido\n");
        printf("4. Listar pedidos\n");
        printf("5. Atualizar pedido\n");
        printf("6. Deletar pedido\n");
        printf("7. Realizar pagamento\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: criarCliente(); break;
            case 2: listarCliente(); break;
            case 3: acrescentarPedido(); break;
            case 4: listarPedido(); break;
            case 5: atualizarPedido(); break;
            case 6: deletarPedido(); break;
            case 7: pagamento(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n"); break;
        }
    } while (escolha != 0);

    return 0;
}
