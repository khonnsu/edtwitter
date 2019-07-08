#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
	char nome[16];
	int posts;
	int mentions;
	int rts;
	int engajamento;
}user;

typedef struct{
	struct user *dado;
	struct l_posts *prox;
	struct l_posts *ant;
}l_posts;

typedef struct{
	struct user *dado;
	struct l_ments *prox;
	struct l_ments *ant;
}l_ments;

typedef struct{
	struct user *dado;
	struct l_rts *prox;
	struct l_rts *ant;
}l_rts;

typedef struct{
	struct user *dado;
	struct l_enga *prox;
	struct l_enga *ant;
}l_enga;

typedef struct{
	char texto[281];
	int rts;
	struct tweet prox;
	struct tweet ant;
}tweet;

typedef struct{
	char nome[280];
	int usos;
	struct hashtag *prox;
	struct hashtag *ant;
	struct l_hash *relacionadas;
}hashtag;

typedef struct{
	struct hashtag *dado;
	int encontros;
	struct l_hash *prox;
	struct l_hash *ant;
}l_hash;

typedef struct{
	int quantidade[7];
	char hashtag[280];
}operacoes;


