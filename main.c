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

int main(void) {
	
	int i = 0,digi = 0,car = 0;
    Node *p = criaNodo();
    
    while(i == 0){
		printf("\n                    Menu\n\n");
		printf("Para carregar os arquivos citados no documento de entrada digite 1.\n");
		printf("Para inserir palavras manualmente digite 2.\n");
		printf("Para buscar por uma palavra digite 3.\n");
		printf("Para gerar o ranking de palavras digite 4\n");
		printf("Para sair digite 5\n\n");
		
		scanf("%d",&digi);
		
		if(digi == 1){
			car = carregar(p);
			if(car) printf("Carregamento efetuado com sucesso!!\n\n");
			else printf("Erro no carregamento dos arquivos!!\n\n");
		}
		
		else if(digi == 2){
			car = insere_manual(p);
			if(car) printf("Palavra(s) inserida(s) com sucesso!!\n\n");
			else printf("Erro ao inserir palavra(s)!!\n\n");
		}
		
		else if(digi == 3){
			busca_indice(p);
		}
		
		else if(digi == 4){
			Imprimir(p);
		}
		
		else if(digi == 5){
			i = 1;
			printf("Saiu!!\n\n");
		}
		
		else{
			printf("Digito inválido\n\n");
		}
	}

    //Destruir_id(p);
    printf("ola\n");
    Destruir(p);
    return 0;
}
