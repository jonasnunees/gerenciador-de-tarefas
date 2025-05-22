// Inclusão das bibliotecas necessárias
#include <stdio.h>   // Para entrada e saída de dados
#include <string.h>  // Para manipulação de strings
#include <stdlib.h>  // Para funções como malloc, free e qsort
#include <time.h>    // Para obter data e hora
#include "tarefas.h" // Inclusão do cabeçalho com as declarações e estrutura de Tarefa

// Declaração e inicialização dos dados globais
Tarefa tarefas[MAX_TAREFAS];  // Vetor que armazena todas as tarefas
int totalTarefas = 0;         // Contador de quantas tarefas existem
int proximoId = 1;            // ID a ser usado para a próxima tarefa criada

// Zera a lista de tarefas
void inicializarTarefas() {
    totalTarefas = 0;
}

// Retorna uma string representando a prioridade (1, 2 ou 3)
const char *prioridadeStr(int prioridade) {
    switch (prioridade) {
        case 1: return "Baixa";
        case 2: return "Média";
        case 3: return "Alta";
        default: return "Desconhecida";
    }
}

// Lista todas as tarefas cadastradas no programa
void listarTarefas() {
    if (totalTarefas == 0) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    printf("\nTarefas:\n");
    for (int i = 0; i < totalTarefas; i++) {
        printf("ID: %d | [%s] | Prioridade: %s | %s\n",
               tarefas[i].id,
               tarefas[i].concluida ? "Concluída" : "Pendente",
               prioridadeStr(tarefas[i].prioridade),
               tarefas[i].descricao);
    }
}

// Adiciona uma nova tarefa à lista
void adicionarTarefa(const char *descricao, int prioridade) {
    if (totalTarefas >= MAX_TAREFAS) {
        printf("Limite de tarefas atingido.\n");
        return;
    }

    // Captura a data e hora atual
    time_t agora = time(NULL);
    struct tm *tm_info = localtime(&agora);
    strftime(tarefas[totalTarefas].dataCriacao, sizeof(tarefas[totalTarefas].dataCriacao), "%Y-%m-%d %H:%M:%S", tm_info);

    // Preenche os dados da nova tarefa
    tarefas[totalTarefas].id = proximoId++;
    strncpy(tarefas[totalTarefas].descricao, descricao, sizeof(tarefas[totalTarefas].descricao) - 1);
    tarefas[totalTarefas].descricao[sizeof(tarefas[totalTarefas].descricao) - 1] = '\0'; // Garante o fim da string
    tarefas[totalTarefas].concluida = 0; // Ainda não foi concluída
    tarefas[totalTarefas].prioridade = prioridade;

    totalTarefas++; // Aumenta o contador de tarefas
    printf("Tarefa adicionada com sucesso.\n");
}

// Marca uma tarefa como concluída com base no ID
void marcarComoConcluida(int id) {
    for (int i = 0; i < totalTarefas; i++) {
        if (tarefas[i].id == id) {
            if (tarefas[i].concluida) {
                printf("A tarefa já está marcada como concluída.\n");
            } else {
                tarefas[i].concluida = 1;
                printf("Tarefa marcada como concluída.\n");
            }
            return;
        }
    }
    printf("Tarefa com ID %d não encontrada.\n", id);
}

// Remove uma tarefa com base no ID
void removerTarefa(int id) {
    int encontrada = 0;

    for (int i = 0; i < totalTarefas; i++) {
        if (tarefas[i].id == id) {
            encontrada = 1;

            // Move as tarefas seguintes uma posição para trás
            for (int j = i; j < totalTarefas - 1; j++) {
                tarefas[j] = tarefas[j + 1];
            }

            totalTarefas--; // Diminui o total
            printf("Tarefa removida com sucesso.\n");
            break;
        }
    }

    if (!encontrada) {
        printf("Tarefa com ID %d não encontrada.\n", id);
    }
}

// Carrega tarefas de um arquivo binário simples
void carregarTarefasDoArquivo(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) return;

    totalTarefas = 0;
    while (fscanf(arquivo, "%d|%255[^|]|%d\n", &tarefas[totalTarefas].id, tarefas[totalTarefas].descricao, &tarefas[totalTarefas].concluida, &tarefas[totalTarefas].prioridade) == 3) {
        totalTarefas++;
        if (tarefas[totalTarefas - 1].id >= proximoId) {
            proximoId = tarefas[totalTarefas - 1].id + 1;
        }
    }

    fclose(arquivo);
}

// Salva as tarefas num arquivo binário simples
void salvarTarefasEmArquivo(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar tarefas no arquivo.\n");
        return;
    }

    for (int i = 0; i < totalTarefas; i++) {
        fprintf(arquivo, "%d|%s|%d|%d\n",
            tarefas[i].id,
            tarefas[i].descricao,
            tarefas[i].concluida,
            tarefas[i].prioridade);
    }

    fclose(arquivo);
}

// Edita a descrição de uma tarefa com base no ID
void editarDescricaoTarefa(int id, const char *novaDescricao) {
    for (int i = 0; i < totalTarefas; i++) {
        if (tarefas[i].id == id) {
            strncpy(tarefas[i].descricao, novaDescricao, sizeof(tarefas[i].descricao) - 1);
            tarefas[i].descricao[sizeof(tarefas[i].descricao) - 1] = '\0';
            printf("Descrição da tarefa atualizada com sucesso.\n");
            return;
        }
    }
    printf("Tarefa com ID %d não encontrada.\n", id);
}

// Função usada por qsort para comparar prioridades
int compararPrioridade(const void *a, const void *b) {
    const Tarefa *tarefaA = (const Tarefa *)a;
    const Tarefa *tarefaB = (const Tarefa *)b;

    return tarefaB->prioridade - tarefaA->prioridade;  // Ordena de forma decrescente
}

// Ordena a lista de tarefas por prioridade
void ordenarTarefasPorPrioridade() {
    qsort(tarefas, totalTarefas, sizeof(Tarefa), compararPrioridade);
}

// Busca tarefas que contenham uma palavra-chave na descrição
int buscarTarefasPorPalavraChave(const char *palavraChave, int resultados[], int maxResultados) {
    int count = 0;
    for (int i = 0; i < totalTarefas; i++) {
        if (strstr(tarefas[i].descricao, palavraChave) != NULL) {
            if (count < maxResultados) {
                resultados[count] = i;
                count++;
            } else {
                break;
            }
        }
    }
    return count;
}

// Salva tarefas em um arquivo de texto legível
void salvarTarefasTxt() {
    FILE *f = fopen("tarefas.txt", "w");
    if (!f) {
        printf("Erro ao abrir o arquivo tarefas.txt para escrita.\n");
        return;
    }

    for (int i = 0; i < totalTarefas; i++) {
        fprintf(f, "ID: %d\n", tarefas[i].id);
        fprintf(f, "Descrição: %s\n", tarefas[i].descricao);
        fprintf(f, "Prioridade: %d\n", tarefas[i].prioridade);
        fprintf(f, "Status: %s\n", tarefas[i].concluida ? "Concluída" : "Pendente");
        fprintf(f, "Data: %s\n", tarefas[i].dataCriacao);
        fprintf(f, "----\n");
    }

    fclose(f);
    printf("Tarefas salvas no formato texto com sucesso!\n");
}

// Salva tarefas em formato CSV (planilha)
void salvarTarefasCsv() {
    FILE *f = fopen("tarefas.csv", "w");
    if (!f) {
        printf("Erro ao abrir arquivo tarefas.csv para escrita.\n");
        return;
    }

    fprintf(f, "ID,Descrição,Prioridade,Status\n");

    for (int i = 0; i < totalTarefas; i++) {
        fprintf(f, "%d,\"%s\",%d,%s\n",
                tarefas[i].id,
                tarefas[i].descricao,
                tarefas[i].prioridade,
                tarefas[i].concluida ? "Concluída" : "Pendente");
    }

    fclose(f);
    printf("Tarefas salvas em tarefas.csv com sucesso!\n");
}

// Permite o usuário escolher o formato de salvamento
void salvarTarefas() {
    int opcao;
    printf("Escolha o formato para salvar as tarefas:\n");
    printf("1. Texto (.txt)\n");
    printf("2. CSV (.csv)\n");
    printf("Opção: ");
    scanf("%d", &opcao);
    getchar(); // Limpa o buffer do teclado

    if (opcao == 1) {
        salvarTarefasTxt();
    } else if (opcao == 2) {
        salvarTarefasCsv();
    } else {
        printf("Opção inválida. Nenhum arquivo salvo.\n");
    }
}

// Carrega tarefas do arquivo CSV
void carregarTarefasCsv() {
    FILE *f = fopen("tarefas.csv", "r");
    if (!f) return;

    char linha[512];
    fgets(linha, sizeof(linha), f); // Ignora o cabeçalho

    totalTarefas = 0;
    while (fgets(linha, sizeof(linha), f) && totalTarefas < MAX_TAREFAS) {
        Tarefa t;
        char status[16];
        linha[strcspn(linha, "\n")] = '\0';

        sscanf(linha, "%d,\"%[^\"]\",%d,%15[^,\n]",
               &t.id, t.descricao, &t.prioridade, status);

        t.concluida = (strcmp(status, "Concluída") == 0);
        tarefas[totalTarefas++] = t;
    }

    fclose(f);
    printf("Tarefas carregadas de tarefas.csv\n");
}

// Carrega tarefas do arquivo de texto
void carregarTarefasTxt() {
    FILE *f = fopen("tarefas.txt", "r");
    if (!f) return;

    totalTarefas = 0;
    Tarefa t = {0};
    char linha[256];
    char status[16];

    // Loop para ler o arquivo linha por linha até o final
    while (fgets(linha, sizeof(linha), f)) {

        // Verifica se a linha atual começa com "ID:"
        if (strncmp(linha, "ID:", 3) == 0) {
            // Extrai o valor do ID da tarefa e armazena na struct temporária `t`
            sscanf(linha, "ID: %d", &t.id);

        // Verifica se a linha atual começa com "Descrição:"
        } else if (strncmp(linha, "Descrição:", 10) == 0) {
            // Lê toda a descrição da tarefa até a quebra de linha e armazena em `t.descricao`
            sscanf(linha, "Descrição: %[^\n]", t.descricao);

        // Verifica se a linha atual começa com "Prioridade:"
        
        } else if (strncmp(linha, "Prioridade:", 11) == 0) {
            // Lê a prioridade (1=baixa, 2=média, 3=alta) e armazena em `t.prioridade`
            sscanf(linha, "Prioridade: %d", &t.prioridade);

        // Verifica se a linha atual começa com "Status:"
        
        } else if (strncmp(linha, "Status:", 7) == 0) {
            // Lê o status textual ("Pendente" ou "Concluída") e armazena na string auxiliar `status`
            sscanf(linha, "Status: %[^\n]", status);

        // Verifica se a linha atual começa com "Data:"
        
        } else if (strncmp(linha, "Data:", 5) == 0) {
            // Lê a data de criação da tarefa e armazena em `t.dataCriacao`
            sscanf(linha, "Data: %[^\n]", t.dataCriacao);

            // Define o campo `concluida` com base no valor de `status`
            // Se `status` for "Concluída", `t.concluida` será 1 (true), caso contrário será 0 (false)
            t.concluida = (strcmp(status, "Concluída") == 0);

        // Verifica se chegou ao fim do bloco de uma tarefa (linha com "----")
        
        } else if (strncmp(linha, "----", 4) == 0) {
            // Garante que ainda há espaço no vetor de tarefas
            if (totalTarefas < MAX_TAREFAS) {
                // Adiciona a tarefa `t` ao array de tarefas e incrementa o contador
                tarefas[totalTarefas++] = t;

                // Reinicia todos os campos da struct `t` para garantir que os dados da próxima tarefa não sejam afetados
                t = (Tarefa){0};
            }
        }
    }

    // Adiciona última tarefa, se houver
    if (t.id != 0 && totalTarefas < MAX_TAREFAS) {
        tarefas[totalTarefas++] = t;
    }

    fclose(f);

    // Atualiza o próximo ID
    int maiorId = 0;
    for (int i = 0; i < totalTarefas; i++) {
        if (tarefas[i].id > maiorId) {
            maiorId = tarefas[i].id;
        }
    }
    proximoId = maiorId + 1;

    printf("Tarefas carregadas do arquivo texto com sucesso (%d tarefa%s).\n", totalTarefas, totalTarefas == 1 ? "" : "s");
}

// Tenta carregar primeiro do CSV, se não existir, tenta o TXT
void carregarTarefas() {
    FILE *f = fopen("tarefas.csv", "r");
    if (f) {
        fclose(f);
        carregarTarefasCsv();
        return;
    }

    f = fopen("tarefas.txt", "r");
    if (f) {
        fclose(f);
        carregarTarefasTxt();
        return;
    }

    printf("Nenhum arquivo de tarefas encontrado. Iniciando lista vazia.\n");
}