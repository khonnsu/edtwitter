#include <stdio.h>
#include "twitter.h"

int main(int argc, char **argv){

	FILE *ent = fopen(arg[1],"r");
	if(ent==NULL){
		printf("Erro ao abrir arquivo de entrada\n");		
		return -1;
	}
	FILE *ops = fopen(arg[2],"r");
	if(ops==NULL){
		printf("Erro ao abrir arquivo de operacoes\n");
		return -1;
	}	
	FILE *sai = fopen(arg[3],"w");
	if(sai=NULL){
		printf("Erro ao criar arquivo de saída\n");
		return -1;
	}
		
	int opa,opb,opc,opd,ope,opf;
	char opg;

	leparametros(ops,&opa,&opb,&opc,&opd,&ope,&opf,&opg);

			

	 
