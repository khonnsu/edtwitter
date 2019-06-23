#DEFINE POST 0
#DEFINE MENC 1
#DEFINE RTS 2
#DEFINE ENGA 3

#DEFINE PROX 0
#DEFINE DIR 1
#DEFINE ESQ 2
#DEFINE ANT 3


typedef struct{
	char nickname[16]; //por causa do '\0' seu troxa
	int curtidas;
	int contador [4];	//[0=post, 1=menc, 2=rts, 3=enga]
	struct tweet *tweets;

	struct usuario *pont[4][4]; //[0=post, 1=menc, 2=rts, 3=enga][0=prox, 1=dir, 2=esq, 3= ant]
}usuario;

//Estruturas para tweets

typedef struct{
	char texto[141];
	int curtidas;
	int retweets;
	struct lista_tweet *rank[4]; //[0=prox,3=ant]
	struct lista_tweet *prox_user;
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

int learquivo(char *nome,usuario *raiz_post, usuario *ini_post, usuario *fim_post,usuario *raiz_menc, usuario *ini_menc, usuario *fim_menc, usuario *ini_rts, usuario *fim_rts,usuario *raiz_enga, usuario *ini_enga, usuario *fim_enga, hashtag *raiz_r, hashtag *ini_h, hashtag *fim_h, tweet *rank_ini, tweet *rank_fim);

usuario verifica_usuario(char *nick,tweet *lido,usuario *raiz_post, usuario *ini_post, usuario *fim_post,usuario *raiz_menc, usuario *ini_menc, usuario *fim_menc,usuario *raiz_rts, usuario *ini_rts, usuario *fim_rts,usuario *raiz_enga, usuario *ini_enga, usuario *fim_enga);

usuario cria_user(char *nick, tweet *lido, int flag_menc, usuario *ini_post, usuario *fim_post,usuario *raiz_menc, usuario *ini_menc, usuario *fim_menc, usuario *ini_rts, usuario *fim_rts,usuario *raiz_enga, usuario *ini_enga, usuario *fim_enga);
	
uruario insere_lista_u(usuario *novo,int param,usuario *ini,usuario *fim);

usuario atualiza_lista_u(usuario *novo,int param,usuario *ini,usuario *fim);

usuario tira_lista(usuario *user,int param, usuario *ini,usuario *fim);

usuario insere_pre_aux(usuario *user, usuario *aux,int param, usuario *ini,usuario *fim);

tweet insere_lista_t(tweet *novo,tweet *ini,tweet *fim);
