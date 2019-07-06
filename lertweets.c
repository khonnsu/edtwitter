#include "twitter.c"

int main(int argc, char **arg){

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

	USUARIO *meus_usuarios = cria_u(*meus_usuarios);
	HASHTAG *minhas_hashtags = cria_h(*minhas_hashtags);
	TWEET *meus_tweets = cria_t(*meus_tweets);

	learquivo(entra,*meus_usuarios,*minhas_hashtags,*meus_tweets);

	escrevearquivo(saida, *meus_usuarios, *minhas_hashtags, *meus_tweets, operacao,comeco);

	encerra(*meus_usuarios, *minhas_hashtags, *meus_tweets);



	return 0;
}
