#DEFINE POST 0
#DEFINE MENC 1
#DEFINE RTS 2
#DEFINE INFLU 3

#DEFINE PROX 0
#DEFINE DIR 1
#DEFINE ESQ 2
#DEFINE ANT 3


typedef struct{
	char nickname[16]; //por causa do '\0' seu troxa
	int curtidas;
	int retweets;
	int mencoes;
	int posts;
	int influencia;
	struct tweet *tweets;

	struct usuario *pont[4][4]; //[0=post, 1=menc, 2=rts, 3=influ][0=prox, 1=dir, 2=esq]
}usuario;

//Estruturas para tweets

typedef struct{
	char texto[141];
	int curtidas;
	int retweets;
	struct lista_tweet *prox;
}tweet;

//Estruturas para hashtags

typedef struct{
	char nome[140];
	int usos;
	struct relacionadas *associadas;
	
	struct hashtag *pont[3];	//[0=prox(ordem de mais usados), 1=dir(menor alfabeticamente), 2=esq(maior alfabeticamente)]
}hashtag;
	
typedef struct{
	struct hashtag *dado;
	int encontros;
	struct relacionadas *pont[3];	//[0=prox(ordem de mais usados), 1=dir(menor alfabeticamente), 2=esq(maior alfabeticamente)]
	
}relacionadas;

//Funcoes 

int learquivo(char *nome, usuario *raiz_u, usuario *ini_u, usuario *fim_u, hashtag *raiz_h, hashtag *ini_h, hashtag *fim_h);

usuario verifica_usuario(char *nick, usuario *raiz, usuario *ini, usuario *fim);



usuario verifica_usuario(char *nick, usuario *raiz, usuario *ini, usuario *fim);{
if(raiz!=NULL){
	
	int i =strcmp(nick,raiz.nickname);
	if(i==0){	
			return raiz;
	}
	
	else if(i<0){
		raiz[POST][ESQ]= verifica_exist(char *nick, raiz->pont[POST][ESQ]){
	}
		
	else{
		raiz[POST][DIR]= verifica_exist(char *nick, raiz->POST][DIR]){
	}
	
}
else{
	usuario *novo;
	usuario *aux;
	novo= malloc(sizeof(usuario));
	strcpy(novo.nickname,nick);
	novo->curtidas= 0;
	novo->retweets= 0;
	novo->mencoes= 0;
	novo->posts = 0;
	novo->influencia = 0;
	novo->tweets= NULL;

	aux=fim;
	if(aux.posts==0)
	{
		
		while(strcmp(aux.nickname,raiz.nickname)<0)
		{
			aux=aux->ant;
		}
		
		
		//insere na lista
		
	}
	struct usuario *pont[4][3]; //[0=post, 1=menc, 2=rts, 3=influ][0=prox, 1=dir, 2=esq]
	return novo;
}

}

			


