#ifndef TAREFAS_H
#define TAREFAS_H

// Define o número máximo de tarefas que o programa pode armazenar
#define MAX_TAREFAS 100

// Define uma estrutura chamada "Tarefa", que representa uma tarefa no sistema
typedef struct {
    int id;                        // Identificador único da tarefa
    char descricao[256];          // Texto que descreve a tarefa
    int concluida;                // Indica se a tarefa foi concluída (0 = não, 1 = sim)
    int prioridade;               // Nível de prioridade: 1 (baixa), 2 (média), 3 (alta)
    char dataCriacao[20];         // Data em que a tarefa foi criada (formato string)
} Tarefa;

// Declaração de um vetor global de tarefas, com no máximo MAX_TAREFAS elementos
extern Tarefa tarefas[MAX_TAREFAS];

// Variável global que armazena o número total de tarefas atualmente registradas
extern int totalTarefas;

// Variável global que indica o próximo ID disponível para uma nova tarefa
extern int proximoId;

// -------------------------
// Funções do Gerenciador
// -------------------------

// Inicializa o sistema de tarefas, zerando contadores e preparando o ambiente
void inicializarTarefas();

// Exibe todas as tarefas na tela (id, descrição, prioridade, status, etc.)
void listarTarefas();

// Adiciona uma nova tarefa com descrição e prioridade informadas
void adicionarTarefa(const char *descricao, int prioridade);

// Marca uma tarefa como concluída com base no seu ID
void marcarComoConcluida(int id);

// Remove uma tarefa do sistema com base no seu ID
void removerTarefa(int id);

// Salva todas as tarefas em um arquivo no formato definido pelo usuário
void salvarTarefasEmArquivo(const char *nomeArquivo);

// Carrega tarefas de um arquivo previamente salvo
void carregarTarefasDoArquivo(const char *nomeArquivo);

// Permite editar a descrição de uma tarefa existente, buscando pelo ID
void editarDescricaoTarefa(int id, const char *novaDescricao);

// Ordena as tarefas de acordo com a prioridade (alta > média > baixa)
void ordenarTarefasPorPrioridade(void);

// Busca tarefas que contenham uma palavra-chave na descrição.
// Armazena os índices encontrados no vetor resultados, limitado por maxResultados.
int buscarTarefasPorPalavraChave(const char *palavraChave, int resultados[], int maxResultados);

// Salva as tarefas no formato .txt (texto simples)
void salvarTarefasTxt(void);

// Salva as tarefas no formato .csv (planilha)
void salvarTarefasCsv(void);

// Função genérica que chama a função de salvar no formato escolhido
void salvarTarefas(void);

// Função genérica que chama a função de carregar de acordo com o formato escolhido
void carregarTarefas(void);

#endif // TAREFAS_H
