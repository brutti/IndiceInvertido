/*
 * Jefferson Coppini, Nicholas Brutti
 * Estrutura de Dados II - UFFS 2015/2
 * Trabalho G1 - Índice invertido
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "upIndice.h"

#define MAX 11234

void Destruir(Node *t) {
	if(!t) return;
	if(t->esq) Destruir(t->esq);
	if(t->data) Destruir(t->meio);
	if(t->id) free(t->id);
	if(t->dir) Destruir(t->dir);
	free(t);
}

/*void Destruir(Node* t) {
	if(t) {
		Destruir(t->esq);
		if(t->id) free(t->id);
		if(t->data) Destruir(t->meio);
		Destruir(t->dir);
		free(t);
	}
}*/
	
void Percorrer(struct Node* t, char* buffer, int tam){
	FILE *rank = NULL;
	rank = fopen("rank.txt","a");
    if(t) {
		Percorrer(t->esq, buffer, tam);   //vai á esquerda
		buffer[tam] = t->data;
		
		if (t->fim) {    //fim da palavra
		buffer[tam+1] = '\0';
			int i = 0;
			while(t->id[i] != 0) {
				if(i == 0) fprintf(rank,"%s %d ", buffer,t->id[i]);
				else fprintf(rank,"%d ", t->id[i]);                    //imprime índices
				i++;
			}
			fprintf(rank,"\n");
		}
        Percorrer(t->meio, buffer, tam + 1);   //vai ao meio
		Percorrer(t->dir, buffer, tam);       //vai á direita
    }
    fclose(rank);
}
 
void Imprimir(Node* t) {
    char buffer[MAX];
    Percorrer(t, buffer, 0);
}

Node* Insere(Node* t, char *palavra, int arqs) {
    if (!t) {
    	t = (Node *) malloc(sizeof(Node)); //cria o nodo
    	t->fim = 0;
    	t->id = NULL;
    	if(palavra) t->data = *palavra;
    	else t->data = 0;
    	t->esq = t->meio = t->dir  = NULL;
    	if(!palavra) return t;
    }
    if ((*palavra) < t->data) 
    	t->esq = Insere(t->esq, palavra,arqs); // insere á esquerda
    else if ((*palavra) > t->data)
		t->dir = Insere(t->dir, palavra,arqs); // insere á direita
    else{
        if (*(palavra+1)) //Se a próxima posição for diferente de \0
            t->meio = Insere(t->meio, palavra+1,arqs); // insere no meio
        else {
			int cont = 0;
			while(cont<= t->fim){
				if(t->id){
					if(t->id[cont] == arqs) break;
				}
				cont++;
			}
			if(cont>t->fim){
				t->fim++;
				t->id = (char *) realloc(t->id, (t->fim+1) * sizeof(char));  // insere índice
				t->id[t->fim-1] = arqs;
				t->id[t->fim] = 0;
			}
		}
    }
    return t;
}

Node* criaNodo() {
	return Insere(NULL, NULL, 0);
}

Node* BuscarPalavra(Node *t, char *palavra) {
    if(!t){
		 return t;
	}
    if(*palavra < (t)->data) return BuscarPalavra(t->esq, palavra); // busca á esquerda
    else if(*palavra > (t)->data) return BuscarPalavra(t->dir, palavra); //busca á direita
    else {
        if(*(palavra+1) == '\0' && t->fim) return t; 
        return BuscarPalavra(t->meio, palavra+1); //busca ao meio
    }
}


void busca_indice(Node*t){
	char aux2[MAX];
	Node* aux = NULL;
	int cont = 0;
	aux = t;
	printf("Digite a palavra a ser buscada!\n");
	getchar();
	fgets(aux2,MAX,stdin);      // Leitura usuário
	aux2[strlen(aux2)-1] = '\0';
	aux = BuscarPalavra(aux,aux2);
	if(!aux){
		printf("Palavra não encontrada\n"); // palavra não está na arvore
	}
	if(aux) {
		printf("%s ",aux2);
		while(aux->id[cont] != 0) {
			printf("%d ", aux->id[cont]);
			cont++;
		}
	}
	printf("\n");
}	
 
int carregar(Node* t){
	FILE *textos = NULL, *texto_ind = NULL;
	int arqs = 0, tam = 0,arqs2=0;
	char nome_arquivo[MAX];
	char let;
	char *palavra = NULL;

	textos = fopen("entrada.txt","r"); // texto de entrada
	
	if(!textos){
		printf("\nArquivo de entrada não consta no diretório !!! \n\n");
		return 0;
	}
	
	fscanf(textos, "%d\n", &arqs); // Leitura do número de textos
	
	while(fgets(nome_arquivo, MAX, textos) && arqs--){
		nome_arquivo[strlen(nome_arquivo)-1]='\0';
		arqs2++;
      	if((texto_ind = fopen(nome_arquivo, "r+"))==NULL) return 0;
      		
      	while((let=fgetc(texto_ind)) != EOF){
			let = tolower(let);
			
			if((let > 96 && let < 123) || (let > 47 && let < 58 )){
				palavra = (char *)realloc(palavra, ((++tam)+1) * sizeof(char));
    			palavra[tam - 1] = let;
 	 			palavra[tam] = '\0';
 	 		}
 	 		else{
				if(palavra != NULL){
					Insere(t, palavra, arqs2); // insere palavra na árvore
					tam = 0;
					free(palavra);
					palavra = NULL;
				}		
			
			}
		}
	}
	fclose(textos);
	fclose(texto_ind);
	return 1;
}

int insere_manual(Node* t){
	char aux2[MAX];
	char *palavra = NULL;
	int cont = 0;
	printf("digite a palavra!\n");
	getchar();
	fgets(aux2,MAX,stdin);     // Leitura do usuário
	aux2[strlen(aux2)-1] = '\0';
	int tam = 0;
	
	while(aux2[cont]){
		if((aux2[cont] > 96 && aux2[cont] < 123) || (aux2[cont] > 47 && aux2[cont] < 58 )){
			palavra = (char *)realloc(palavra, ((++tam)+1) * sizeof(char));
    		palavra[tam - 1] = aux2[cont];
 	 		palavra[tam] = '\0';
 	 	}
 	 	if((aux2[cont+1]<= 96 && aux2[cont+1] >= 123) || (aux2[cont+1] <= 47 && aux2[cont+1] >= 58 ) || aux2[cont+1] == '\0'){
			if(palavra != NULL){
				Insere(t, palavra, 1);
				tam = 0;
				free(palavra);
				palavra = NULL;
				return 1;
			}
			return 0;		
			
		}
		cont++;
	}
	return 0;
}
