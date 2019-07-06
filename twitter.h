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

usuario *cria_user(char *nick, tweet *lido, int flag_menc, usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L);
usuario *verifica_usuario(char *nick,tweet *lido,int param,int outro,usuario *raiz, usuario *procurado,usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L);
usuario *insere_lista_u(usuario *novo,int param,usuario **P_U_AeL);
usuario *tira_lista(usuario *user,int param, usuario **P_U_AeL);
usuario *insere_pre_aux(usuario *user, usuario *aux,int param, usuario **P_U_AeL);
usuario *atualiza_arvore_u(usuario *filho,usuario *pai,int param,usuario **P_U_AeL);

hashtag *cria_hash(char *hash,hashtag **P_H_AeL);
hashtag *insere_lista_h(hashtag *novo,hashtag **P_H_AeL);
hashtag *tira_lista_h(hashtag *hash, hashtag **P_H_AeL);
hashtag *insere_pre_aux_h(hashtag *hash, hashtag *aux,hashtag **P_H_AeL);
hashtag *atualiza_arvore_h(hashtag *filho,hashtag *pai, hashtag **P_H_AeL);

tweet *insere_lista_t(tweet *novo, tweet **P_T_L);
tweet *insere_pre_aux_t(tweet *t, tweet *aux, tweet **P_T_L);


relacionadas *acha_rel(hashtag *procurada,  relacionadas **ponts,  relacionadas *raiz);
relacionadas *cria_r(hashtag *nova,relacionadas **P_R);
relacionadas *insere_lista_r(relacionadas *novo, relacionadas **P_R);
relacionadas *insere_pre_aux_r(relacionadas *novo, relacionadas *aux,relacionadas **P_R);
relacionadas *tira_lista_r(relacionadas *novo, relacionadas **P_R);
relacionadas *atualiza_arvore_r(relacionadas *filho,relacionadas *pai, relacionadas **P_L);


relacionadas* cadehashtag(char nome[], hashtag *raiz);
