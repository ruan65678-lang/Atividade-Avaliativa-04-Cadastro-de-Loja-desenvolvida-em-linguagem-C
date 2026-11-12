/*
 * ATIVIDADE AVALIATIVA 04 - CADASTRO DE LOJA
 * Aluno: Ruan Silva Costa
 * RGM: 47538368
 * Curso: Engenharia de Software
 * Instituicao: UNICID
 * Linguagem: C
 */

#include <stdio.h>      // Permite usar printf, fgets, fopen, fprintf e outras funções de entrada/saída.
#include <stdlib.h>     // Permite usar strtol, strtof e funções gerais da biblioteca padrão.
#include <string.h>     // Permite usar strlen, strcmp, strcpy e strstr.
#include <ctype.h>      // Permite usar tolower para comparar textos sem diferenciar maiúsculas.
#include <errno.h>      // Permite verificar erros na conversão de números.

#define MAX 100                 // Define a quantidade máxima de produtos na memória.
#define TAM_NOME 50             // Define o tamanho máximo do nome do produto.
#define TAM_CATEGORIA 30        // Define o tamanho máximo da categoria.
#define TAM_FORNECEDOR 40       // Define o tamanho máximo do fornecedor.
#define ARQUIVO "produtos.txt"  // Define o nome do arquivo principal de dados.
#define TEMP "temp.txt"         // Define o nome do arquivo temporário usado ao salvar.
#define BACKUP "backup.txt"     // Define o nome do arquivo de segurança durante a substituição.

/* Estrutura que reúne todos os campos de um produto. */
typedef struct {
    int id;                         // Guarda o identificador único do produto.
    char nome[TAM_NOME];            // Guarda o nome do produto.
    char categoria[TAM_CATEGORIA];  // Guarda a categoria do produto.
    float preco;                    // Guarda o preço do produto.
    int quantidade;                 // Guarda a quantidade disponível no estoque.
    char fornecedor[TAM_FORNECEDOR];// Guarda o nome do fornecedor.
} Produto;                          // Cria o tipo Produto para uso no programa.

/* Lê uma linha do teclado e remove o caractere de quebra de linha. */
void lerTexto(const char *mensagem, char *destino, int tamanho) {
    size_t tamanhoTexto;                         // Guarda o tamanho do texto digitado.
    printf("%s", mensagem);                     // Mostra a mensagem solicitando a informação.
    if (fgets(destino, tamanho, stdin) == NULL) {// Tenta ler o texto com limite de tamanho.
        destino[0] = '\0';                      // Deixa o destino vazio se a leitura falhar.
        return;                                  // Encerra a função em caso de falha.
    }
    tamanhoTexto = strlen(destino);              // Calcula quantos caracteres foram lidos.
    if (tamanhoTexto > 0 && destino[tamanhoTexto - 1] == '\n') {// Verifica se terminou com Enter.
        destino[tamanhoTexto - 1] = '\0';        // Substitui o Enter pelo terminador de texto.
    } else {                                     // Executa quando o texto ocupou todo o espaço.
        int caractere;                           // Guarda temporariamente os caracteres restantes.
        while ((caractere = getchar()) != '\n' && caractere != EOF) { } // Limpa o restante da linha.
    }
}

/* Lê um número inteiro e repete a pergunta se a entrada não for válida. */
int lerInteiro(const char *mensagem) {
    char linha[100];                             // Reserva espaço para a entrada digitada.
    char *fim;                                   // Aponta para o primeiro caractere após o número.
    long valor;                                  // Guarda temporariamente o número convertido.
    while (1) {                                  // Repete até receber um inteiro válido.
        lerTexto(mensagem, linha, sizeof(linha));// Lê a entrada como texto.
        errno = 0;                               // Limpa o indicador de erro antes da conversão.
        valor = strtol(linha, &fim, 10);         // Converte o texto para inteiro na base decimal.
        while (*fim == ' ' || *fim == '\t') fim++; // Ignora espaços depois do número.
        if (linha[0] != '\0' && *fim == '\0' && errno == 0 && valor >= -2147483647L && valor <= 2147483647L) {
            return (int)valor;                   // Retorna o inteiro quando a conversão é válida.
        }
        printf("Entrada invalida. Digite um numero inteiro.\n"); // Informa o erro ao usuário.
    }
}

/* Lê um preço e aceita somente valores numéricos não negativos. */
float lerPreco(const char *mensagem) {
    char linha[100];                             // Reserva espaço para o preço digitado.
    char *fim;                                   // Aponta para o final do número convertido.
    float valor;                                 // Guarda o preço convertido.
    while (1) {                                  // Repete até receber um preço válido.
        lerTexto(mensagem, linha, sizeof(linha));// Lê o preço como texto.
        errno = 0;                               // Limpa o indicador de erro.
        valor = strtof(linha, &fim);             // Converte o texto para número decimal.
        while (*fim == ' ' || *fim == '\t') fim++; // Ignora espaços no final.
        if (linha[0] != '\0' && *fim == '\0' && errno == 0 && valor >= 0.0f) {
            return valor;                        // Retorna o preço se a entrada for válida.
        }
        printf("Preco invalido. Digite um valor numerico maior ou igual a zero.\n"); // Mostra o erro.
    }
}

/* Converte uma cópia do texto para minúsculas, sem alterar o original. */
void paraMinusculo(const char *origem, char *destino, size_t tamanho) {
    size_t i;                                    // Controla a posição dos caracteres.
    for (i = 0; i + 1 < tamanho && origem[i] != '\0'; i++) { // Percorre até o limite do destino.
        destino[i] = (char)tolower((unsigned char)origem[i]); // Converte o caractere com segurança.
    }
    destino[i] = '\0';                          // Finaliza a string convertida.
}

/* Compara dois textos ignorando diferenças entre maiúsculas e minúsculas. */
int compararTexto(const char *a, const char *b) {
    char textoA[200];                            // Reserva espaço para a primeira cópia.
    char textoB[200];                            // Reserva espaço para a segunda cópia.
    paraMinusculo(a, textoA, sizeof(textoA));    // Converte a primeira cópia para minúsculas.
    paraMinusculo(b, textoB, sizeof(textoB));    // Converte a segunda cópia para minúsculas.
    return strcmp(textoA, textoB);               // Retorna zero quando os textos são iguais.
}

/* Verifica se um texto contém outro, ignorando maiúsculas e minúsculas. */
int contemTexto(const char *texto, const char *busca) {
    char textoA[200];                            // Reserva espaço para o texto pesquisado.
    char textoB[200];                            // Reserva espaço para o termo de busca.
    paraMinusculo(texto, textoA, sizeof(textoA));// Converte o texto para minúsculas.
    paraMinusculo(busca, textoB, sizeof(textoB));// Converte o termo de busca para minúsculas.
    return strstr(textoA, textoB) != NULL;       // Retorna verdadeiro se encontrar o termo.
}

/* Procura um ID no vetor e informa se ele já existe. */
int idExiste(const Produto *lista, int total, int id) {
    int i;                                       // Controla a posição do vetor.
    for (i = 0; i < total; i++) {                // Percorre todos os produtos cadastrados.
        if (lista[i].id == id) return 1;         // Retorna 1 quando encontra o ID.
    }
    return 0;                                   // Retorna 0 quando o ID não existe.
}

/* Procura um nome de produto já cadastrado, podendo ignorar um ID na alteração. */
int nomeExiste(const Produto *lista, int total, const char *nome, int ignorarId) {
    int i;                                       // Controla a posição do vetor.
    for (i = 0; i < total; i++) {                // Percorre os produtos existentes.
        if (lista[i].id != ignorarId && compararTexto(lista[i].nome, nome) == 0) { // Compara nomes.
            return 1;                            // Informa que já existe outro produto com esse nome.
        }
    }
    return 0;                                   // Informa que o nome ainda não está cadastrado.
}

/* Carrega os produtos do arquivo para o vetor, usando ponteiros. */
void carregar(Produto *lista, int *total) {
    FILE *arquivo = fopen(ARQUIVO, "r");        // Abre o arquivo principal para leitura.
    char linha[250];                             // Reserva espaço para ler cada registro.
    *total = 0;                                  // Começa a contagem de produtos em zero.
    if (arquivo == NULL) return;                 // Sai se o arquivo ainda não existir.
    while (*total < MAX && fgets(linha, sizeof(linha), arquivo) != NULL) { // Lê registro por registro.
        Produto p;                               // Cria uma variável temporária para o produto.
        if (sscanf(linha, "%d|%49[^|]|%29[^|]|%f|%d|%39[^\r\n]", &p.id, p.nome, p.categoria,
                   &p.preco, &p.quantidade, p.fornecedor) == 6) { // Confere se os seis campos foram lidos.
            if (!idExiste(lista, *total, p.id)) { // Evita carregar IDs repetidos do arquivo.
                lista[*total] = p;               // Copia o produto para a próxima posição do vetor.
                (*total)++;                      // Atualiza a quantidade de produtos carregados.
            }
        }
    }
    fclose(arquivo);                             // Fecha o arquivo após terminar a leitura.
}

/* Salva o vetor em arquivo temporário e substitui o arquivo principal com segurança básica. */
int salvar(const Produto *lista, int total) {
    FILE *arquivo = fopen(TEMP, "w");           // Cria o arquivo temporário para escrita.
    int i;                                       // Controla a posição do vetor.
    if (arquivo == NULL) {                       // Verifica se o temporário foi aberto.
        printf("Erro ao criar arquivo temporario.\n"); // Informa o problema.
        return 0;                                // Indica que o salvamento falhou.
    }
    for (i = 0; i < total; i++) {                // Percorre todos os produtos.
        if (fprintf(arquivo, "%d|%s|%s|%.2f|%d|%s\n", lista[i].id, lista[i].nome,
                    lista[i].categoria, lista[i].preco, lista[i].quantidade, lista[i].fornecedor) < 0) {
            fclose(arquivo);                     // Fecha o temporário se ocorrer erro de escrita.
            remove(TEMP);                        // Remove o arquivo temporário incompleto.
            printf("Erro ao gravar os dados.\n"); // Informa o problema.
            return 0;                            // Indica falha.
        }
    }
    if (fclose(arquivo) != 0) {                  // Fecha e verifica se houve erro na gravação final.
        remove(TEMP);                            // Remove o temporário incompleto.
        printf("Erro ao finalizar a gravacao.\n"); // Informa o problema.
        return 0;                                // Indica falha.
    }
    remove(BACKUP);                              // Remove um backup antigo, se existir.
    if (rename(ARQUIVO, BACKUP) != 0) {          // Tenta renomear o arquivo atual para backup.
        FILE *teste = fopen(ARQUIVO, "r");      // Verifica se o arquivo original existe.
        if (teste != NULL) {                     // Entra se havia um arquivo original.
            fclose(teste);                       // Fecha o arquivo usado no teste.
            remove(TEMP);                        // Descarta o temporário para preservar o original.
            printf("Nao foi possivel proteger o arquivo original.\n"); // Informa a falha.
            return 0;                            // Interrompe sem apagar o arquivo original.
        }
    }
    if (rename(TEMP, ARQUIVO) != 0) {            // Tenta colocar o temporário no lugar do arquivo principal.
        rename(BACKUP, ARQUIVO);                 // Tenta restaurar o arquivo anterior.
        remove(TEMP);                            // Remove o temporário se a substituição falhar.
        printf("Erro ao substituir o arquivo. O backup foi restaurado quando possivel.\n"); // Informa o erro.
        return 0;                                // Indica falha.
    }
    remove(BACKUP);                              // Apaga o backup depois da substituição bem-sucedida.
    return 1;                                    // Indica que os dados foram salvos.
}

/* Cria o arquivo inicial somente quando ele ainda não existe. */
void criarArquivoInicial(void) {
    FILE *arquivo = fopen(ARQUIVO, "r");        // Tenta abrir o arquivo para verificar se já existe.
    if (arquivo != NULL) {                       // Entra se o arquivo já existe.
        fclose(arquivo);                         // Fecha o arquivo existente.
        return;                                  // Não sobrescreve os dados do usuário.
    }
    arquivo = fopen(ARQUIVO, "w");              // Cria o arquivo caso ele não exista.
    if (arquivo == NULL) {                       // Verifica se a criação falhou.
        printf("Nao foi possivel criar %s.\n", ARQUIVO); // Informa o erro.
        return;                                  // Encerra a função.
    }
    fprintf(arquivo, "1|Camiseta Basica|Vestuario|49.90|30|Moda Brasil\n"); // Insere o primeiro exemplo.
    fprintf(arquivo, "2|Mouse Optico USB|Informatica|59.99|15|TecnoShop\n"); // Insere o segundo exemplo.
    fprintf(arquivo, "3|Shampoo 300ml|Higiene Pessoal|22.50|40|Beleza Pura\n"); // Insere o terceiro exemplo.
    fprintf(arquivo, "4|Cafe 500g|Alimentos|18.00|25|Graos do Sul\n"); // Insere o quarto exemplo.
    fclose(arquivo);                             // Fecha o arquivo depois de criar os registros.
}

/* Mostra os produtos em formato de tabela sem modificar o arquivo. */
void listar(const Produto *lista, int total) {
    int i;                                       // Controla a posição do vetor.
    printf("\n%-5s | %-25s | %-20s | %-10s | %-10s | %-20s\n", "ID", "PRODUTO", "CATEGORIA", "PRECO", "QUANTIDADE", "FORNECEDOR"); // Imprime o cabeçalho.
    printf("---------------------------------------------------------------------------------------------------------------\n"); // Desenha a separação.
    if (total == 0) printf("Nenhum produto cadastrado.\n"); // Informa quando o cadastro está vazio.
    for (i = 0; i < total; i++) {                // Percorre os produtos cadastrados.
        printf("%-5d | %-25.25s | %-20.20s | R$ %-7.2f | %-10d | %-20.20s\n", lista[i].id,
               lista[i].nome, lista[i].categoria, lista[i].preco, lista[i].quantidade, lista[i].fornecedor); // Exibe os campos.
    }
}

/* Descobre o próximo ID usando o maior ID existente mais um. */
int gerarId(const Produto *lista, int total) {
    int maior = 0;                                // Começa considerando que ainda não há IDs positivos.
    int i;                                       // Controla a posição do vetor.
    for (i = 0; i < total; i++) {                // Percorre todos os produtos.
        if (lista[i].id > maior) maior = lista[i].id; // Atualiza o maior ID encontrado.
    }
    return maior + 1;                            // Retorna o próximo ID incremental.
}

/* Cadastra um produto novo, impedindo nomes e IDs duplicados. */
void inserir(Produto *lista, int *total) {
    Produto novo;                                // Cria a estrutura que receberá os dados novos.
    if (*total >= MAX) {                         // Verifica se o vetor está cheio.
        printf("Limite de %d produtos atingido.\n", MAX); // Informa o limite.
        return;                                  // Impede inserir além do vetor.
    }
    lerTexto("Nome do produto: ", novo.nome, sizeof(novo.nome)); // Lê o nome do produto.
    if (novo.nome[0] == '\0') {                  // Verifica se o nome ficou vazio.
        printf("O nome nao pode ficar vazio.\n"); // Informa a regra.
        return;                                  // Cancela o cadastro.
    }
    if (nomeExiste(lista, *total, novo.nome, -1)) { // Verifica se já existe produto com o mesmo nome.
        printf("Produto com esse nome ja cadastrado.\n"); // Informa a duplicidade.
        return;                                  // Impede cadastrar o duplicado.
    }
    lerTexto("Categoria: ", novo.categoria, sizeof(novo.categoria)); // Lê a categoria.
    novo.preco = lerPreco("Preco: ");            // Lê e valida o preço.
    novo.quantidade = lerInteiro("Quantidade: "); // Lê a quantidade.
    if (novo.quantidade < 0) {                   // Verifica se a quantidade é negativa.
        printf("A quantidade nao pode ser negativa.\n"); // Informa a regra.
        return;                                  // Cancela o cadastro.
    }
    lerTexto("Fornecedor: ", novo.fornecedor, sizeof(novo.fornecedor)); // Lê o fornecedor.
    novo.id = gerarId(lista, *total);             // Gera o ID automaticamente.
    while (idExiste(lista, *total, novo.id)) novo.id++; // Garante que o ID não esteja repetido.
    lista[*total] = novo;                         // Coloca o novo produto no final do vetor.
    (*total)++;                                  // Atualiza o total de produtos.
    if (salvar(lista, *total)) printf("Produto cadastrado com ID %d.\n", novo.id); // Salva e confirma.
}

/* Altera os dados de um produto localizado pelo ID. */
void alterar(Produto *lista, int total) {
    int id = lerInteiro("Digite o ID do produto que deseja alterar: "); // Solicita o ID.
    int i;                                       // Controla a posição do vetor.
    for (i = 0; i < total; i++) {                // Procura o produto no vetor.
        if (lista[i].id == id) {                 // Verifica se encontrou o ID.
            Produto alterado = lista[i];         // Copia os dados atuais para permitir validar antes de alterar.
            lerTexto("Novo nome: ", alterado.nome, sizeof(alterado.nome)); // Lê o novo nome.
            if (alterado.nome[0] == '\0' || nomeExiste(lista, total, alterado.nome, id)) { // Valida nome vazio ou duplicado.
                printf("Nome vazio ou ja utilizado por outro produto. Alteracao cancelada.\n"); // Informa o problema.
                return;                          // Cancela sem modificar o produto original.
            }
            lerTexto("Nova categoria: ", alterado.categoria, sizeof(alterado.categoria)); // Lê a nova categoria.
            alterado.preco = lerPreco("Novo preco: "); // Lê o novo preço.
            alterado.quantidade = lerInteiro("Nova quantidade: "); // Lê a nova quantidade.
            if (alterado.quantidade < 0) {       // Verifica se a quantidade é negativa.
                printf("Quantidade invalida. Alteracao cancelada.\n"); // Informa o erro.
                return;                          // Cancela a alteração.
            }
            lerTexto("Novo fornecedor: ", alterado.fornecedor, sizeof(alterado.fornecedor)); // Lê o fornecedor novo.
            lista[i] = alterado;                 // Atualiza o produto somente depois de validar os dados.
            if (salvar(lista, total)) printf("Produto alterado com sucesso.\n"); // Salva a alteração.
            return;                              // Encerra após encontrar e alterar.
        }
    }
    printf("ID nao encontrado.\n");             // Informa quando nenhum produto possui o ID.
}

/* Exclui um produto e desloca os elementos seguintes uma posição para trás. */
void excluir(Produto *lista, int *total) {
    int id = lerInteiro("Digite o ID do produto que deseja excluir: "); // Solicita o ID.
    int i;                                       // Controla a busca.
    int j;                                       // Controla o deslocamento dos elementos.
    for (i = 0; i < *total; i++) {               // Percorre os produtos.
        if (lista[i].id == id) {                 // Verifica se encontrou o produto.
            for (j = i; j < *total - 1; j++) {   // Percorre as posições posteriores.
                lista[j] = lista[j + 1];         // Move o próximo produto para a posição atual.
            }
            (*total)--;                          // Diminui a quantidade de produtos.
            if (salvar(lista, *total)) printf("Produto excluido com sucesso.\n"); // Salva a lista atualizada.
            return;                              // Encerra depois da exclusão.
        }
    }
    printf("ID nao encontrado.\n");             // Informa se o ID não existe.
}

/* Busca produtos por nome ou categoria, sem diferenciar maiúsculas e minúsculas. */
void buscar(const Produto *lista, int total, int campo) {
    char termo[100];                             // Guarda o texto digitado para a busca.
    Produto encontrados[MAX];                   // Cria um vetor temporário para os resultados.
    int quantidadeEncontrada = 0;                // Conta quantos resultados foram encontrados.
    int i;                                       // Controla a posição do vetor original.
    lerTexto("Digite o nome ou categoria que deseja buscar: ", termo, sizeof(termo)); // Lê o termo.
    for (i = 0; i < total; i++) {                // Percorre todos os produtos.
        if ((campo == 1 && contemTexto(lista[i].nome, termo)) || // Pesquisa no nome quando campo vale 1.
            (campo == 2 && contemTexto(lista[i].categoria, termo))) { // Pesquisa na categoria quando campo vale 2.
            encontrados[quantidadeEncontrada] = lista[i]; // Copia o produto encontrado.
            quantidadeEncontrada++;             // Atualiza a quantidade de resultados.
        }
    }
    printf("\nResultado da busca:\n");         // Identifica a seção de resultados.
    listar(encontrados, quantidadeEncontrada);  // Exibe somente os produtos encontrados.
}

/* Ordena uma cópia do vetor usando Bubble Sort, sem alterar a ordem original na memória. */
void ordenar(const Produto *lista, int total, int tipo) {
    Produto copia[MAX];                          // Cria um vetor para ordenar sem alterar o cadastro carregado.
    Produto auxiliar;                            // Guarda temporariamente um produto durante a troca.
    int i;                                       // Controla as passagens do Bubble Sort.
    int j;                                       // Controla as comparações entre vizinhos.
    int trocar;                                  // Indica se dois produtos precisam trocar de posição.
    for (i = 0; i < total; i++) copia[i] = lista[i]; // Copia todos os produtos para o vetor auxiliar.
    for (i = 0; i < total - 1; i++) {            // Executa as passagens do Bubble Sort.
        for (j = 0; j < total - 1 - i; j++) {    // Compara elementos vizinhos ainda não ordenados.
            trocar = 0;                          // Começa cada comparação sem solicitar troca.
            if (tipo == 1 && compararTexto(copia[j].nome, copia[j + 1].nome) > 0) trocar = 1; // Nome A-Z.
            if (tipo == 2 && compararTexto(copia[j].nome, copia[j + 1].nome) < 0) trocar = 1; // Nome Z-A.
            if (tipo == 3 && copia[j].preco > copia[j + 1].preco) trocar = 1; // Preço menor para maior.
            if (tipo == 4 && copia[j].preco < copia[j + 1].preco) trocar = 1; // Preço maior para menor.
            if (trocar) {                        // Executa quando a comparação exige inversão.
                auxiliar = copia[j];             // Guarda o primeiro produto temporariamente.
                copia[j] = copia[j + 1];         // Coloca o segundo produto na primeira posição.
                copia[j + 1] = auxiliar;         // Coloca o produto guardado na segunda posição.
            }
        }
    }
    listar(copia, total);                        // Mostra a lista ordenada sem salvar essa ordem no arquivo.
}

/* Escreve um campo CSV entre aspas e duplica aspas internas, conforme o formato CSV. */
void escreverCampoCSV(FILE *arquivo, const char *campo) {
    const char *p = campo;                       // Cria um ponteiro para percorrer o texto.
    fputc('"', arquivo);                         // Abre o campo com aspas.
    while (*p != '\0') {                         // Percorre todos os caracteres do campo.
        if (*p == '"') fputc('"', arquivo);     // Duplica uma aspa encontrada dentro do texto.
        fputc(*p, arquivo);                      // Escreve o caractere atual.
        p++;                                     // Avança o ponteiro para o próximo caractere.
    }
    fputc('"', arquivo);                         // Fecha o campo com aspas.
}

/* Exporta todos os produtos para produtos.csv, usando vírgula como separador. */
void exportarCSV(const Produto *lista, int total) {
    FILE *arquivo = fopen("produtos.csv", "w"); // Cria o arquivo CSV para escrita.
    int i;                                       // Controla a posição do vetor.
    if (arquivo == NULL) {                       // Verifica se o arquivo foi aberto.
        printf("Nao foi possivel criar produtos.csv.\n"); // Informa o erro.
        return;                                  // Encerra a exportação.
    }
    fprintf(arquivo, "ID,Produto,Categoria,Preco,Quantidade,Fornecedor\n"); // Escreve o cabeçalho CSV.
    for (i = 0; i < total; i++) {                // Percorre os produtos cadastrados.
        fprintf(arquivo, "%d,", lista[i].id);   // Escreve o ID e a primeira vírgula.
        escreverCampoCSV(arquivo, lista[i].nome);// Escreve o nome protegido por aspas.
        fputc(',', arquivo);                     // Separa nome e categoria.
        escreverCampoCSV(arquivo, lista[i].categoria); // Escreve a categoria protegida por aspas.
        fprintf(arquivo, ",%.2f,%d,", lista[i].preco, lista[i].quantidade); // Escreve preço e quantidade.
        escreverCampoCSV(arquivo, lista[i].fornecedor); // Escreve o fornecedor protegido por aspas.
        fputc('\n', arquivo);                   // Finaliza a linha do produto.
    }
    fclose(arquivo);                             // Fecha o CSV após terminar a exportação.
    printf("Dados exportados para produtos.csv.\n"); // Confirma a exportação.
}

/* Exibe as opções disponíveis no sistema. */
void mostrarMenu(void) {
    printf("\n========== CADASTRO DE LOJA ==========\n"); // Mostra o título do sistema.
    printf("1 - Listar produtos\n");             // Opção para listar todos os produtos.
    printf("2 - Inserir produto\n");             // Opção para cadastrar um produto.
    printf("3 - Alterar produto\n");             // Opção para alterar um produto.
    printf("4 - Excluir produto\n");             // Opção para excluir um produto.
    printf("5 - Buscar por nome\n");             // Opção para buscar pelo nome.
    printf("6 - Buscar por categoria\n");        // Opção para buscar pela categoria.
    printf("7 - Ordenar nome (A-Z)\n");           // Opção para ordenar nomes crescentemente.
    printf("8 - Ordenar nome (Z-A)\n");           // Opção para ordenar nomes decrescentemente.
    printf("9 - Ordenar preco (menor para maior)\n"); // Opção para ordenar preços crescentemente.
    printf("10 - Ordenar preco (maior para menor)\n"); // Opção para ordenar preços decrescentemente.
    printf("11 - Exportar para CSV\n");          // Opção para exportar os dados.
    printf("0 - Sair\n");                        // Opção para encerrar o programa.
    printf("=====================================\n"); // Fecha visualmente o menu.
}

/* Função principal: inicializa os dados e controla o menu do programa. */
int main(void) {
    Produto lista[MAX];                           // Declara o vetor que armazenará os produtos.
    int total = 0;                               // Guarda a quantidade atual de produtos.
    int opcao;                                   // Guarda a opção escolhida no menu.
    criarArquivoInicial();                       // Garante que o arquivo inicial exista.
    do {                                         // Repete o menu até o usuário escolher sair.
        carregar(lista, &total);                 // Atualiza o vetor com os dados do arquivo.
        mostrarMenu();                           // Exibe as opções do sistema.
        opcao = lerInteiro("Escolha uma opcao: "); // Lê a opção escolhida.
        switch (opcao) {                         // Direciona para a funcionalidade selecionada.
            case 1: listar(lista, total); break; // Lista todos os produtos.
            case 2: inserir(lista, &total); break; // Insere um novo produto.
            case 3: alterar(lista, total); break; // Altera um produto existente.
            case 4: excluir(lista, &total); break; // Exclui um produto existente.
            case 5: buscar(lista, total, 1); break; // Busca pelo nome.
            case 6: buscar(lista, total, 2); break; // Busca pela categoria.
            case 7: ordenar(lista, total, 1); break; // Ordena nome de A até Z.
            case 8: ordenar(lista, total, 2); break; // Ordena nome de Z até A.
            case 9: ordenar(lista, total, 3); break; // Ordena preço do menor para o maior.
            case 10: ordenar(lista, total, 4); break; // Ordena preço do maior para o menor.
            case 11: exportarCSV(lista, total); break; // Exporta os dados para CSV.
            case 0: printf("Encerrando o programa...\n"); break; // Informa que o programa será encerrado.
            default: printf("Opcao invalida. Tente novamente.\n"); // Trata opções que não existem.
        }
    } while (opcao != 0);                        // Continua enquanto a opção for diferente de zero.
    return 0;                                    // Encerra o programa informando sucesso ao sistema operacional.
}