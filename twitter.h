#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define POST 0
#define MENC 1
#define RTS 2
#define ENGA 3

#define PROX 0
#define DIR 1
#define ESQ 2
#define ANT 3

#define INI 0
#define FIM 1
#define RAIZ 2

typedef struct{
	char nickname[16]; //por causa do '\0' seu troxa
	int curtidas;
	int contador [4];	//[0=post, 1=menc, 2=rts, 3=enga]
	struct tweet *tweets;

	struct usuario *pont[4*4]; //[0=post, 1=menc, 2=rts, 3=enga][0=prox, 1=dir, 2=esq, 3= ant]
}usuario;

//Estruturas para hashtags

typedef struct{
	char nome[140];
	int usos;
	struct
	{
	struct hashtag *dado;
	int encontros;
	struct relacionadas *pont[4];	//[0=prox, 1=dir, 2=esq, 3= ant]
    } *associadas[3]; // [0=ini, 1=fim, 2=raiz];

	struct hashtag *pont[4];	//[0=prox, 1=dir, 2=esq, 3= ant]
}hashtag;

typedef struct{
	struct hashtag *dado;
	int encontros;
	struct relacionadas *pont[4];	//[0=prox, 1=dir, 2=esq, 3= ant]

}relacionadas;

typedef struct{
	struct hashtag *dado;
	struct l_hash *prox;
}l_hash;

//Estruturas para tweets

typedef struct{
	char texto[141];
	int curtidas;
	int retweets;
	struct tweet *pont[4]; //[0=prox,3=ant]
	struct tweet *prox_user;
	l_hash *eh_as_hash;

}tweet;

typedef struct{
	int a;
	int b;
	int c;
	int d;
	int e;
	int f;
	int g;
	char hash[279];
}ops;

//Funcoes

int learquivo(FILE *arq,usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L);
