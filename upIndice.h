/*
 * Jefferson Coppini, Nicholas Brutti
 * Estrutura de Dados II - UFFS 2015/2
 * Trabalho G1 - Índice invertido
 */

#ifndef hINDICE

#define hINDICE

// Estrutura do nodo
typedef struct Node {
    char data, fim, *id;
    struct Node *esq, *meio, *dir;
} Node;

/*Recebe uma árvore como parâmetro. 
 *Libera a árvore passada por parâmetro.*/
void Destruir(Node* t);

/*Recebe uma árvore como parâmetro.
 *Libera os ponteiros alocados dinâmicamente.*/
//void Destruir_id(Node* t);

/*Recebe uma árvore, um ponteiro para char e um inteiro como parâmetro.
 *percorre a árvore passada por parâmetro e imprime as palavras em ordem alfabética.*/
void Percorrer(struct Node* t, char* buffer, int tam);

/*Recebe uma árvore como parâmetro.
 *Chama a função principal para impressão.*/
void Imprimir(Node* t);

/*Recebe como parâmetro uma árvore, um ponteiro para uma palavra e o número do texto que ela está.
 *Insere na árvore um caractere por nodo e também o número do arquivo no nodo da última
  letra da palavra.
 *Retorna um ponteiro para a raiz da árvore. */
Node* Insere(Node* t, char *palavra, int arqs);

//inicializa a árvore.
Node* criaNodo();

/*Recebe como parâmetro uma árvore e uma palavra.
 *Busca na árvore a palavra passada por parâmetro.
 *Retorna o ponteiro para o nodo procurado. */
Node* BuscarPalavra(Node *t, char *palavra);

/*Recebe como parâmetro uma árvore.
 *Solicita a palavra ao usuário e repassa a mesma para a função BuscarPalavra*/ 
void busca_indice(Node*t);

/*Recebe como parâmetro uma árvore.
 *Carrega o conteúdo válido dos documentos citados no arquivo de entrada na árvore repassada.
 *Retorna 1 em caso de sucesso e 0 caso contrário. */
int carregar(Node* t);

/*Recebe como parâmetro uma árvore.
 *Insere uma palavra digitada pelo usário na árvore passada por parâmetro.
 *Retorna 1 em caso de sucesso e 0 caso contrário */
int insere_manual( Node* t);

#endif
