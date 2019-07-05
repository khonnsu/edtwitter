#include "twitter.c"

int main(int argc, char **argv){

	clock_t comeco = clock();

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

	USUARIO *meus_usuarios = cria_u();
	HASHTAG *minhas_hashtags = cria_h();
	TWEET *meus_tweets = cria_t();

	learquivo(entra,*P_U_AeL,*P_H_AeL,*P_T_L);

	escrevearquivo(saida,*P_U_AeL, *P_H_AeL, *P_T_l, operacao,comeco);

	encerra(*P_U_AeL, *P_H_AeL, *P_T_l);



	return 0;
}




