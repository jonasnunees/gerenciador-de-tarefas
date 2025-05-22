# 🗂️ Gerenciador de Tarefas em C

Um projeto simples e eficiente de gerenciamento de tarefas feito em linguagem C, com suporte a diferentes formatos de salvamento e funcionalidades úteis como:

- Cadastro e listagem de tarefas
- Marcar como concluída e remover
- Prioridade (baixa, média, alta)
- Salvamento e carregamento em **.txt** e **.csv**
- Registro de **data de criação**
- Interface de terminal simples e funcional

## 📂 Estrutura dos Arquivos

- `main.c`: ponto de entrada do programa
- `tarefas.c`: implementação das funções principais
- `tarefas.h`: cabeçalho com definições da estrutura `Tarefa`
- `tarefas.txt` / `tarefas.csv`: arquivos gerados com as tarefas salvas

## 🛠️ Funcionalidades

✅ Adicionar tarefa com:
- Descrição  
- Prioridade  
- Data e hora de criação automática  

✅ Marcar como concluída  
✅ Editar descrição  
✅ Remover tarefa  
✅ Listar todas as tarefas  
✅ Buscar por palavra-chave  
✅ Ordenar por prioridade  
✅ Salvar e carregar:
- Formato texto simples
- Formato CSV  
✅ Exportação automática no formato escolhido  

## 💾 Exemplo de uso (terminal)

```
$ ./gerenciador
Escolha uma opção:

Adicionar tarefa

Listar tarefas

Marcar como concluída

Remover tarefa

Salvar tarefas

Carregar tarefas
```

## 🛠️ Como compilar e executar

Pré-requisitos
Um compilador C (como gcc, clang, etc.)

Terminal de linha de comando (Linux, macOS ou Windows com PowerShell / CMD / Git Bash)

Compilando o programa
No terminal, navegue até a pasta onde estão os arquivos .c e .h do projeto e execute:
```
gcc main.c tarefas.c -o gerenciador
```

- main.c: contém o menu principal e a lógica de interação com o usuário.
- tarefas.c: contém a implementação das funções de manipulação de tarefas.
- -o gerenciador: define o nome do executável gerado (gerenciador.exe no Windows ou gerenciador no Linux/macOS).

Executando o programa
Depois de compilar, rode o programa com:

```
./gerenciador
```

No Windows, use:

```
gerenciador.exe
```

## 📌 Sobre o projeto

Este projeto foi feito com o objetivo de praticar lógica de programação, manipulação de arquivos e organização modular em C. É ideal para quem está começando ou quer um exemplo real de projeto em C para estudo e evolução.


## 🧠 Autor

**Jonas**  
Desenvolvedor iniciante focado em C, com planos de evoluir para interfaces gráficas e contribuir com projetos open source acessíveis e eficientes.

---

⭐ Se você gostou, deixe uma estrela no repositório e acompanhe meus próximos projetos!
