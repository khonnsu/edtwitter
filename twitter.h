
typedef struct{
	char nickname[15];
	int curtidas;
	int retweets;
	int mencoes;
	struct tweet *tweets;
	struct l_posts *posts;
	struct l_menc *mencoes;
	struct l_rts *retweets;
	struct l_influ *influencia;
	struct usuario *prox;
}usuario;

//Estruturas derivadas do usuario
	
typedef struct{
	struct usuario *dado;
	int posts;
	struct l_posts *prox;
	struct arv_posts *arvore;
}l_posts;

typedef struct{
	struct usuario *dado;
	struct arv_posts *dir;
	struct arv_posts *esq;
}arv_posts;

typedef struct{
	struct usuario *dado;
	int mencoes;
	struct l_menc *prox;
	struct arv_menc *arvore;
}l_menc;

typedef struct{
	struct usuario *dado;
	struct arv_menc *dir;
	struct arv_menc *esq;
}arv_menc;

typedef struct{
	struct usuario *dado;
	int retweets;
	struct l_rts *prox;
	struct arv_rts *arvore;
}l_rts;

typedef struct{
	struct usuario *dado;
	struct arv_rts *dir;
	struct arv_rts *esq;
}arv_rts;

typedef struct{
	struct usuario *dado;
	int influencia;	
	struct l_influ *prox;
	struct arv_influ *arvore;
}l_influ;

typedef struct{
	struct usuario *dado;
	struct arv_influ *dir;
	struct arv_influ *esq;
}arv_influ;

//Estruturas para tweets

typedef struct{
	char texto[141];
	int curtidas;
	int retweets;
	struct lista_tweet *prox;
	struct arv_tweet *arvore
}tweet;

typedef struct{
	struct tweet *dado;
	struct arv_tweet *dir;
	struct arv_tweet *esq;
}arv_tweet;

//Estruturas para hashtags

typedef struct{
	char nome[30];
	int usos;
	struct relacionadas *associadas;
	struct hashtag *prox;
	struct arv_hashtag *arvore;
}hashtag;

typedef struct{
	struct hashtag *dado;
	struct arv_hashtag *dir;
	struct arv_hashtag *esq;
}arv_hashtag;
	
typedef struct{
	struct hashtag *dado;
	int encontros;
	struct relacionadas *prox;
	struct arv_hashtag *arvore;
}relacionadas;

//Funcoes 

void learquivo(struct usuario pt_user struct hashtag ptl_hash, struct arv_hashtag ptarv_hash, struct tweet ptl_tweet, struct arv_tweet ptarv_tweet);
