
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
}tweet;

typedef struct{
	struct tweet *dado;
	struct lista_tweet *prox;
}lista_tweet;

typedef struct{
	char nome[30];
	int usos;
	struct lista_tweet *aparicoes;
	struct lista_hashtag *associadas;
}hashtag;

typedef struct{
	struct hashtag *dado;
	int encontros;
	struct lista_hashtag *prox;
}lista_hashtag;
