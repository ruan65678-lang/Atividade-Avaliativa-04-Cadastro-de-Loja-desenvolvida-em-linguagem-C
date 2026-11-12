# Cadastro de Loja - Atividade Avaliativa 04

## Identificação do aluno

- **Nome:** Ruan Silva Costa
- **RGM:** 47538368
- **Curso:** Engenharia de Software
- **Instituição:** UNICID
- **Atividade:** Avaliativa 04 - Cadastro de Loja

## Descrição

Programa desenvolvido em linguagem C para cadastrar e administrar produtos de uma loja. O projeto utiliza estrutura (`struct`), vetor de estruturas, ponteiros, manipulação de arquivos, buscas e algoritmo Bubble Sort.

## Funcionalidades

- Criação automática do arquivo `produtos.txt` com quatro registros iniciais, caso ele ainda não exista.
- Listagem dos produtos em formato de tabela.
- Inserção com ID incremental automático.
- Bloqueio de produtos com nomes duplicados (comparação sem diferenciar maiúsculas e minúsculas).
- Alteração e exclusão por ID.
- Busca por nome ou categoria.
- Ordenação por nome (A-Z e Z-A) e por preço (menor-maior e maior-menor), usando Bubble Sort.
- Exportação para `produtos.csv`, separado por vírgulas.
- Salvamento por arquivo temporário, com tentativa de preservar/restaurar o arquivo anterior em caso de falha na substituição.

## Arquivos

- `main.c`: código-fonte do programa.
- `produtos.txt`: arquivo de dados usado pelo programa.
- `produtos.csv`: arquivo criado quando a opção de exportação é escolhida.

## Como compilar

Com GCC instalado, abra o terminal na pasta do projeto e execute:

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o cadastro
```

No Windows, execute:

```bash
cadastro.exe
```

No Linux ou macOS, execute:

```bash
./cadastro
```

## Observação

O arquivo `produtos.txt` usa o caractere `|` como separador interno. O CSV exportado usa vírgulas como separador e coloca os campos de texto entre aspas para preservar vírgulas que eventualmente apareçam nos dados.