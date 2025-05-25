#include <stdio.h>      // Biblioteca padrão para entrada e saída (printf, scanf, etc.)
#include <locale.h>     // Necessária para configurar a acentuação no terminal
#include <string.h>     // Usada para manipulação de strings (ex: fgets, strcspn)
#include "tarefas.h"    // Arquivo de cabeçalho com as funções relacionadas às tarefas

// Nome do arquivo principal usado para salvar tarefas
#define ARQUIVO_TAREFAS "tarefas.txt"  

int main() {

    // Ativa o suporte a acentuação no terminal
    setlocale(LC_ALL, "Portuguese");  

    // Carrega as tarefas salvas anteriormente (caso existam)
    carregarTarefas();                 

    // Armazena a opção do menu escolhida pelo usuário
    int opcao;   

    // Buffer para armazenar descrições de tarefas
    char descricao[256];              

    do {
        // Menu principal do programa
        printf("\n=== GERENCIADOR DE TAREFAS ===\n");
        printf("1. Adicionar tarefa\n");
        printf("2. Listar tarefas\n");
        printf("3. Marcar tarefa como concluída\n");
        printf("4. Remover tarefa\n");
        printf("5. Editar descrição da tarefa\n");
        printf("6. Buscar tarefa por palavra-chave\n");
        printf("7. Salvar tarefas em arquivo\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        // Remove o '\n' deixado pelo scanf para evitar problemas em leituras futuras
        getchar(); 

        switch (opcao) {
            case 1: {
                // Adicionar nova tarefa
                char descricao[256];
                int prioridade;

                printf("Digite a descrição da tarefa: ");

                // Lê a descrição com espaços
                fgets(descricao, sizeof(descricao), stdin);  

                // Remove o '\n' final da string
                descricao[strcspn(descricao, "\n")] = '\0';  

                printf("Defina a prioridade (1 = baixa, 2 = média, 3 = alta): ");
                scanf("%d", &prioridade);

                // Limpa o buffer novamente
                getchar(); 

                if (prioridade < 1 || prioridade > 3) {
                    // Caso o usuário insira um valor inválido
                    printf("Prioridade inválida. Usando prioridade média por padrão.\n");
                    prioridade = 2;
                }

                // Adiciona a tarefa ao sistema
                adicionarTarefa(descricao, prioridade);  
                break;
            }

            case 2:
                // Lista as tarefas na tela em ordem de prioridade

                // Organiza antes de exibir
                ordenarTarefasPorPrioridade();  

                // Mostra todas as tarefas
                listarTarefas();                
                break;

            case 3: {
                // Marca uma tarefa como concluída
                int id;
                printf("Digite o ID da tarefa a ser marcada como concluída: ");
                scanf("%d", &id);

                // Limpa o buffer
                getchar(); 

                // Marca a tarefa correspondente
                marcarComoConcluida(id);  
                break;
            }

            case 4: {
                // Remove uma tarefa do sistema
                int id;
                printf("Digite o ID da tarefa a ser removida: ");
                scanf("%d", &id);

                // Limpa o buffer
                getchar(); 

                // Remove a tarefa
                removerTarefa(id);  
                break;
            }

            case 5: {
                // Edita a descrição de uma tarefa existente
                int id;
                char novaDescricao[256];
                printf("Digite o ID da tarefa a ser editada: ");
                scanf("%d", &id);

                // Limpa o \n do buffer
                getchar(); 

                printf("Digite a nova descrição: ");
                fgets(novaDescricao, sizeof(novaDescricao), stdin);

                // Remove o \n
                novaDescricao[strcspn(novaDescricao, "\n")] = '\0';  

                // Atualiza a descrição
                editarDescricaoTarefa(id, novaDescricao);  
                break;
            }

            case 6: {
                // Busca tarefas contendo uma palavra-chave
                char palavraChave[256];

                // Armazena os índices das tarefas encontradas
                int resultados[100];  

                printf("Digite a palavra-chave para busca: ");
                fgets(palavraChave, sizeof(palavraChave), stdin);

                // Remove \n
                palavraChave[strcspn(palavraChave, "\n")] = '\0';  

                int encontrados = buscarTarefasPorPalavraChave(palavraChave, resultados, 100);

                if (encontrados == 0) {
                    printf("Nenhuma tarefa encontrada com a palavra-chave \"%s\".\n", palavraChave);
                } else {
                    printf("Tarefas encontradas:\n");
                    for (int i = 0; i < encontrados; i++) {
                        int idx = resultados[i];
                        printf("%d. [%s] %s\n", tarefas[idx].id,
                            tarefas[idx].concluida ? "Concluída" : "Pendente",
                            tarefas[idx].descricao);
                    }
                }
                break;
            }

            case 7: {
                // Salva as tarefas em formato CSV (ou binário, dependendo da implementação)
                salvarTarefas();
                break;
            }

            case 0:
                // Sai do programa e salva em formato legível (usado no carregamento também)
                salvarTarefasTxt();
                printf("Saindo do programa...\n");
                break;

            default:
                // Caso o usuário digite uma opção inválida
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);  // Repete até que o usuário escolha sair (opção 0)

    return 0;
}
