
typedef struct{
	char nickname[15];
	int curtidas;
	int retweets;
	int mencoes; // talvez se necessario tornar mencoes uma lista assim como os tweets
	struct lista_tweet *postagens;
}usuario;

typedef struct{
	char texto[141];
	int curtidas;
	int retweets;
	struct lista_tweet *prox;
}tweet;

typedef struct{
	struct tweet *dado;
	struct arv_tweet dir;
	struct arv_tweet esq;
}arv_tweet;

typedef struct{
	char nome[30];
	int usos;
	struct relacionadas *associadas;
	struct hashtag *prox;
}hashtag;

typedef struct{
	struct hashtag lista;
	struct arv_hashtag dir;
	struct arv_hashtag esq;
}arv_hashtag;
	

typedef struct{
	struct hashtag *dado;
	int encontros;
	struct relacionadas *prox;
}relacionadas;
