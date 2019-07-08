#include "planob.h"

int main(int arg, char **argv){

	clock_t comeco = clock();

	FILE *entra = fopen(arg[1],"r");
	if(entra==NULL){
		printf("Erro ao abrir arquivo de entrada\n");
		return -1;
	}
	FILE *param = fopen(arg[2], "r");
	if(param==NULL){
		printf("Erro ao abrir arquvo de operacoes\n");
		return -1;
	}
	FILE *saida = fopen(arg[3],"w");
	if(saida==NULL){
		printf("Erro ao criar arquivo de saida\n");
		return -1;
	}

	operacoes ops;




	return 0;
}
