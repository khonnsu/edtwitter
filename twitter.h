#DEFINE POST 0
#DEFINE MENC 1
#DEFINE RTS 2
#DEFINE ENGA 3

#DEFINE PROX 0
#DEFINE DIR 1
#DEFINE ESQ 2
#DEFINE ANT 3

#DEFINE INI 0
#DEFINE FIM 1
#DEFINE RAIZ 2

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
	l_hash *eh_as_hash;
	
}tweet;

//Estruturas para hashtags

typedef struct{
	char nome[140];
	int usos;
	relacionadas *associadas;
	
	struct hashtag *pont[4];	//[0=prox, 1=dir, 2=esq, 3= ant]
}hashtag;
	
typedef struct{
	struct hashtag *dado;
	int encontros;
	struct relacionadas *pont[4];	//[0=prox, 1=dir, 2=esq, 3= ant]
	
}relacionadas;

typedef struct{
	struct hashtag *dado;
	struct relacionadas *prox;
}l_hash;

//Funcoes 

int learquivo(char *nome,usuario *raiz_post, usuario *ini_post, usuario *fim_post,usuario *raiz_menc, usuario *ini_menc, usuario *fim_menc, usuario *ini_rts, usuario *fim_rts,usuario *raiz_enga, usuario *ini_enga, usuario *fim_enga, hashtag *raiz_r, hashtag *ini_h, hashtag *fim_h, tweet *rank_ini, tweet *rank_fim);

usuario verifica_usuario(char *nick, tweet *lido, int param, usario *pai, usuario **P_U_AeL, tweet **P_T_L);

usuario cria_user(char *nick, tweet *lido, int flag_menc, usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L);
	
usuario insere_lista_u(usuario *novo, int param, usuario **P_U_AeL);

int atualiza_lista (usuario *user, int param, usuario **P_U_AeL);

usuario tira_lista(usuario *user, int param, usuario **P_U_AeL);

usuario insere_pre_aux(usuario *user, usario *aux, int param, usuario **P_U_AeL);

void atualiza_arvore_u(usuario *filho, usuario *pai, usuario *vo, int param, usuario **P_U_AeL);

tweet insere_lista_t(tweet *novo,tweet *ini,tweet *fim);

usuario verifica_hashtag(char *nick, tweet *lido, int param, usuario *raiz, usuario *pai, usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L);


