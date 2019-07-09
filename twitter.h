
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

typedef struct USUARIO usuario;
struct USUARIO{
	char nickname[16]; //por causa do '\0' seu troxa
	int curtidas;
	int contador [4];	//[0=post, 1=menc, 2=rts, 3=enga]
	struct tweet *tweets;

	struct usuario *pont[4*4]; //[0=post, 1=menc, 2=rts, 3=enga][0=prox, 1=dir, 2=esq, 3= ant]
};

//Estruturas para hashtags

typedef struct HASHTAG hashtag;
struct HASHTAG{
	char nome[140];
	int usos;
	struct
	{
	struct hashtag *dado;
	int encontros;
	struct relacionadas *pont[4];	//[0=prox, 1=dir, 2=esq, 3= ant]
    } *associadas[3]; // [0=ini, 1=fim, 2=raiz];

	struct hashtag *pont[4];	//[0=prox, 1=dir, 2=esq, 3= ant]
};

typedef struct RELACIONADAS relacionadas;
struct RELACIONADAS{
	struct hashtag *dado;
	int encontros;
	struct relacionadas *pont[4];	//[0=prox, 1=dir, 2=esq, 3= ant]

};

typedef struct L_HASH l_hash;
struct L_HASH{
	struct hashtag *dado;
	struct l_hash *prox;
};

//Estruturas para tweets

typedef struct TWEET tweet;
struct TWEET{
	char texto[141];
	int curtidas;
	int retweets;
	struct tweet *pont[4]; //[0=prox,3=ant]
	struct tweet *prox_user;
	l_hash *eh_as_hash;

};

typedef struct OPS ops;
struct OPS {
	int a;
	int b;
	int c;
	int d;
	int e;
	int f;
	int g;
	char hash[279];
};

typedef usuario* PUSUARIO;
typedef hashtag* PHASHTAG;
typedef tweet* PTWEET;

//Funcoes

int learquivo(FILE *arq,usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L);
usuario *verifica_usuario(char *nick,tweet *lido,int param,int outro,usuario *raiz, usuario *procurado,usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L);
usuario *cria_user(char *nick, tweet *lido, int flag_menc, usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L);
usuario *insere_lista_u(usuario *novo,int param,usuario **P_U_AeL);
int atualiza_lista_u(usuario *user,int param,usuario **P_U_AeL);
usuario *tira_lista(usuario *user,int param, usuario **P_U_AeL);
usuario *insere_pre_aux(usuario *user, usuario *aux,int param, usuario **P_U_AeL);
usuario *atualiza_arvore_u(usuario *filho,usuario *pai,int param,usuario **P_U_AeL);
hashtag *verifica_hashtag(char *hash, l_hash **mesmo_T, hashtag *raiz, hashtag **P_H_AeL);
hashtag *cria_hash(char *hash,hashtag **P_H_AeL);
hashtag *insere_lista_h(hashtag *novo,hashtag **P_H_AeL);
int atualiza_lista_h(hashtag *hash,hashtag **P_H_AeL);
hashtag *tira_lista_h(hashtag *hash, hashtag **P_H_AeL);
hashtag *insere_pre_aux_h(hashtag *hash, hashtag *aux,hashtag **P_H_AeL);
hashtag *atualiza_arvore_h(hashtag *filho,hashtag *pai, hashtag **P_H_AeL);
tweet *insere_lista_t(tweet *novo, tweet **P_T_L);
tweet *insere_pre_aux_t(tweet *t, tweet *aux, tweet **P_T_L);
void relaciona(l_hash *mesmo_T);
void ad_rel(hashtag *aux1, hashtag *aux2);
relacionadas *acha_rel(hashtag *procurada,  relacionadas **ponts,  relacionadas *raiz);
relacionadas *cria_r(hashtag *nova,relacionadas **P_R);
relacionadas *insere_lista_r(relacionadas *novo, relacionadas **P_R);
relacionadas *insere_pre_aux_r(relacionadas *novo, relacionadas *aux,relacionadas **P_R);
int atualiza_lista_r(relacionadas *novo,hashtag **P_R);
relacionadas *tira_lista_r(relacionadas *novo, relacionadas **P_R);
relacionadas *atualiza_arvore_r(relacionadas *filho,relacionadas *pai, relacionadas **P_L);
void leparametros(FILE *arquivo, ops *op);
void escrevearquivo(FILE *arq, usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L, ops op, clock_t comeco);
relacionadas* cadehashtag(char nome[], hashtag *raiz);
usuario **cria_u();
hashtag **cria_h ();
tweet **cria_t ();
void encerra(usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L);
void destroi_u(usuario **lixo);
void destroi_u_pont(usuario **lixo);
void destroi_t(tweet **lixo);
void destroi_t_pont(tweet **lixo);
void destroi_h(hashtag **lixo);
void destroi_r(relacionadas **lixo);
void destroi(l_hash **lixo);
void escreveop_a(FILE *arq,hashtag **P_H_AeL, ops op);
void escreveop_b(FILE *arq,usuario **P_U_AeL, ops op);
void escreveop_c(FILE *arq,tweet **P_T_L, ops op);
void escreveop_d(FILE *arq,usuario **P_U_AeL, ops op);
void escreveop_e(FILE *arq,usuario **P_U_AeL, ops op);
void escreveop_f(FILE *arq,usuario **P_U_AeL, ops op);
void escreveop_g(FILE *arq,hashtag **P_H_AeL, ops op);

