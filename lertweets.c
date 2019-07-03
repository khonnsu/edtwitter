#include <stdio.h>
#include "twitter.h"

int main(int argc, char **argv){

	FILE *entra = fopen(arg[1],"r");
	if(entra==NULL){
		printf("Erro ao abrir arquivo de entrada\n");		
		return -1;
	}
	FILE *param = fopen(arg[2],"r");
	if(param==NULL){
		printf("Erro ao abrir arquivo de operacoes\n");
		return -1;
	}	
	FILE *saida = fopen(arg[3],"w");
	if(saida=NULL){
		printf("Erro ao criar arquivo de saída\n");
		return -1;
	}
		
	ops operacao;		

	leparametros(param,&operacao);

			

	 
