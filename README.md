# Cadastro de Loja — Atividade Avaliativa 04

## 1. Identificação do aluno

- **Aluno:** Ruan Silva Costa
- **RGM:** 47538368
- **Curso:** Engenharia de Software
- **Instituição:** Universidade Cidade de São Paulo (UNICID)
- **Atividade:** Avaliativa 04 — Algoritmos de Ordenação e Manipulação de Arquivos
- **Linguagem:** C

## 2. Objetivo do projeto

Desenvolver um programa de cadastro de produtos para uma loja, utilizando conceitos de programação em C, estruturas de dados, ponteiros, manipulação de arquivos e algoritmos de ordenação.

O sistema permite cadastrar e administrar produtos, pesquisar informações, organizar os registros e exportar os dados para um arquivo CSV.

## 3. Funcionalidades

O programa disponibiliza as seguintes operações por meio de um menu:

- **Criar arquivo inicial:** cria `produtos.txt` com quatro produtos de exemplo quando o arquivo ainda não existe.
- **Listar produtos:** apresenta os registros em formato de tabela.
- **Inserir produto:** cadastra um novo produto com ID incremental automático.
- **Verificar duplicidade:** impede o cadastro de produtos com nomes já existentes, sem diferenciar letras maiúsculas e minúsculas.
- **Alterar produto:** permite modificar os dados de um produto localizado pelo ID.
- **Excluir produto:** remove um produto pelo ID.
- **Buscar por nome:** pesquisa produtos pelo nome.
- **Buscar por categoria:** pesquisa produtos pela categoria.
- **Ordenar por nome (A–Z):** organiza os produtos em ordem alfabética crescente.
- **Ordenar por nome (Z–A):** organiza os produtos em ordem alfabética decrescente.
- **Ordenar por preço (menor–maior):** apresenta primeiro os produtos mais baratos.
- **Ordenar por preço (maior–menor):** apresenta primeiro os produtos mais caros.
- **Exportar CSV:** gera o arquivo `produtos.csv`, utilizando vírgulas como separadores.

As operações de ordenação são realizadas sobre uma cópia do vetor e não alteram a ordem armazenada no arquivo de dados.

## 4. Conceitos utilizados

### Estrutura de dados

O programa utiliza a estrutura `Produto` para agrupar as informações de cada item:

- ID;
- nome;
- categoria;
- preço;
- quantidade;
- fornecedor.

Os produtos são armazenados em um vetor de estruturas chamado `lista`, com capacidade máxima definida pela constante `MAX`.

### Ponteiros

Ponteiros são utilizados para acessar e manipular dados, como nas funções que recebem o vetor de produtos e o endereço da variável que controla a quantidade de registros. Também são utilizados na leitura e escrita de arquivos.

### Manipulação de arquivos

O arquivo `produtos.txt` mantém os dados entre as execuções do programa. Os registros são gravados em linhas, com os campos separados pelo caractere `|`.

Nas operações de salvamento, o programa grava os dados em um arquivo temporário e tenta substituir o arquivo principal. Também utiliza um arquivo de backup para tentar preservar ou restaurar os dados se a substituição falhar.

### Algoritmo Bubble Sort

O método Bubble Sort é utilizado para ordenar os produtos. O algoritmo compara elementos vizinhos e realiza trocas quando eles estão fora da ordem desejada.

São disponibilizadas quatro opções de ordenação: nome crescente, nome decrescente, preço crescente e preço decrescente.

### Comparação e busca de textos

As comparações e buscas por nome ou categoria não diferenciam letras maiúsculas e minúsculas.

## 5. Arquivos do projeto

| Arquivo | Descrição |
|---|---|
| `main.c` | Código-fonte do programa em linguagem C. |
| `produtos.txt` | Arquivo utilizado para armazenar os produtos cadastrados. |
| `README.md` | Documentação do projeto. |
| `IDENTIFICACAO.txt` | Identificação do aluno e da atividade. |
| `produtos.csv` | Arquivo gerado pelo programa ao selecionar a opção de exportação. |

## 6. Dados iniciais

Quando `produtos.txt` ainda não existe, o programa cria o arquivo com os seguintes registros:

| ID | Produto | Categoria | Preço (R$) | Quantidade | Fornecedor |
|---:|---|---|---:|---:|---|
| 1 | Camiseta Basica | Vestuario | 49,90 | 30 | Moda Brasil |
| 2 | Mouse Optico USB | Informatica | 59,99 | 15 | TecnoShop |
| 3 | Shampoo 300ml | Higiene Pessoal | 22,50 | 40 | Beleza Pura |
| 4 | Cafe 500g | Alimentos | 18,00 | 25 | Graos do Sul |

O arquivo existente não é sobrescrito na inicialização, preservando os dados já cadastrados.

## 7. Como compilar e executar

É necessário ter um compilador C, como o GCC, instalado no computador.

### Compilar

Abra o terminal na pasta do projeto e execute:

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o cadastro
```

### Executar no Windows

```bash
cadastro.exe
```

No PowerShell, se necessário:

```powershell
.\cadastro.exe
```

### Executar no Linux ou macOS

```bash
./cadastro
```

Após iniciar, escolha uma opção no menu digitando o número correspondente.

## 8. Observações

- O limite de produtos é definido pela constante `MAX`, atualmente configurada para 100 registros.
- Os tamanhos máximos dos campos de texto são definidos pelas constantes no início do código.
- O arquivo de dados utiliza `|` como separador interno.
- O arquivo CSV exportado utiliza vírgulas como separadores e aspas nos campos de texto.
- A ordenação é exibida na tela e não modifica a ordem dos registros gravados.

## 9. Considerações finais

O projeto reúne conceitos estudados na disciplina, aplicando estruturas, vetores, ponteiros, funções, manipulação de arquivos, buscas e ordenação Bubble Sort em um sistema de cadastro de produtos.

A atividade tem como objetivo praticar esses conteúdos por meio de um programa funcional e organizado em linguagem C.
