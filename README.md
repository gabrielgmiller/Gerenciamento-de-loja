# Gerenciamento-de-loja

# LojaManager

## Descrição

LojaManager é um aplicativo desenvolvido em C que simula o gerenciamento de uma loja. O aplicativo permite o controle de funcionários, clientes, fornecedores e produtos, oferecendo ações individuais e em massa para facilitar a administração do negócio.

## Funcionalidades

- **Gerenciamento de Funcionários**
  - Adicionar, remover e listar funcionários.
  - Atualizar informações de funcionários.
  - Ações em massa para gerenciamento coletivo de funcionários.

- **Gerenciamento de Clientes**
  - Adicionar, remover e listar clientes.
  - Atualizar informações de clientes.
  - Ações em massa para gerenciamento coletivo de clientes.

- **Gerenciamento de Estoque**
  - Adicionar, remover e listar produtos.
  - Atualizar informações de produtos.
  - Ações em massa para gerenciamento coletivo de produtos.

- **Gerenciamento de Fornecedores**
  - Adicionar, remover e listar fornecedores.
  - Atualizar informações de fornecedores.
  - Ações em massa para gerenciamento coletivo de fornecedores.

- **Interacoes**
  - Menu com opções para interações específicas.

## Requisitos

- Compilador C (recomendado: GCC)
- Sistema operacional compatível com C (Windows, Linux, macOS)

## Como Compilar e Executar

1. Clone o repositório para sua máquina local:

    ```bash
    git clone https://github.com/seu-usuario/LojaManager.git
    ```

2. Navegue até o diretório do projeto:

    ```bash
    cd LojaManager
    ```

3. Compile o código-fonte:

    ```bash
    gcc -o LojaManager main.c -Wall
    ```

4. Execute o aplicativo:

    ```bash
    ./LojaManager
    ```

## Estrutura do Projeto

- `main.c`: Arquivo principal do programa.
- `funcionarios.c` e `funcionarios.h`: Funções e definições relacionadas aos funcionários.
- `clientes.c` e `clientes.h`: Funções e definições relacionadas aos clientes.
- `fornecedores.c` e `fornecedores.h`: Funções e definições relacionadas aos fornecedores.
- `produtos.c` e `produtos.h`: Funções e definições relacionadas aos produtos.

## Exemplo de Uso

### Menu Principal

```plaintext
=== MENU PRINCIPAL ===

1. Gerenciar Funcionário
2. Gerenciar Cliente
3. Gerenciar Estoque
4. Gerenciar Fornecedor
5. Interacoes
0. Sair
Escolha uma opção:

----------------------

1. Criar Base
2. Adicionar
3. Remover
4. Pesquisar
5. Imprimir Base
6. Selecao Natural e Intercalacao
7. Merge Sort Externo
0. Voltar
Escolha uma opção:
