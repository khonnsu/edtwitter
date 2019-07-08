#include "twitter.h"

void learquivo(FILE *arq, hashtag *l_hash, l_posts *posts, tweet *rts, l_ment *ments, l_rts *rts, l_enga *engas){

	//variaveis auxiliares para uso repetido no laço principal	
	user *aux_user;
	hashtag *aux_hash;
	tweet *aux_tweet;
	l_hash *mesmo_tweet;	

	char aux_nick[16];
	char simbolo;
	char aux_nomehash[280]; 
	int aux_likes;
	int aux_rts;
	int flagfim;
	
	//laço principal
	while(!feof(arq)){
		aux_tweet = malloc(sizeof(tweet));

		fseek(arq,1,SEEK_CUR);
		fscanf(arq,"%[^;]s",aux_nick); 	//pula '@' e recebe nickname lendo até ';'
		
		aux_user = malloc(sizeof(user));
		aux_user->nome=aux_nick;

		fseek(arq,1,SEEK_CUR);		//pula ';'
		mesmo_tweet = NULL;

		flagfim = 0;			//flag que indica se acabou leitura de texto
		do{
			fscanf(arq,"%[^;@#]s",aux_tweet->texto);	//lê até ';' '@' ou '#' e salva
			fscanf(arq,"%c",&simbolo);			//lê símbolo dentre os acima
			switch(simbolo){				//reage de acordo com símbolo acima
				case '@':				
					fscanf(arq,"%[^; ]s",aux_nick);		//lê até ';' ou espaço
					l_ment = mencao(ments,aux_nick); 	//trata mencao
					strcat(aux_tweet->texto,"@");
					strcat(atual->texto,aux_nick);		//salva no texto
					break;
				case '#':
					fscanf(arq,"%[^; ]s",aux_nomehash);	//lê até ';' ou espaço'
										//tratamento de hashtag
										//tratemento de mesmo_tweet
					strcat(aux_tweet->texto,"#");
					strcat(aux_tweet->texto,aux_nomehash);	//salva no texto
					break;
				case ';':
					flagfim=1;				//se chegou em ';' acaba
			}
		}while(!flagfim);
	
		fseek(arq,1,SEEK_CUR);
		fscanf(arq,"%d",&aux_rts;	//pula ';' e lê número de rts
		fseek(arq,1,SEEK_CUR);
		fscanf(arq,"%d",&aux_likes);	//pula ';' e lê número de likes

						//trata usuario do tweet
						//trata tweet
						//destroi mesmo_tweet
	}
}
hashtag* achahash(hashtag *ptlista, char nome[]){
	if(ptlista->dado == NULL){
		hashtag *novo;
		novo = malloc(sizeof(hashtag));
		novo = criahashtag(novo);
		novo->nome= nome;
		novo->usos++;
		ptlista->dado = novo;
	}
	else{
		hashtag *ptaux = ptlista->dado;
		while(ptaux->	
l_ments* mencao(l_ments *ptlista, char nome[]){

	if(ptlista->dado == NULL){
		user *novo;
		novo = malloc(sizeof(user));	
		novo = criauser(novo);
		novo->nome = nome;
		novo->mentions++;
		novo->engajamento++;
		ptlista->dado = novo;			//se lista é vazia, cria e devolve ponteiro
	}
	
	else{					// se não, procura até chegar no fim ou encontrar lugar
		user *ptaux = ptlista->dado;
		while(ptaux->proxment!=NULL && stricmp(nome,ptaux->nome)>= 0){
			ptaux=ptaux->proxment;
		}
	
		if(!stricmp(nome,ptaux->nome)){
			ptaux->mentions++;
			ptaux->engajamento++;
		}
		
		else{
			user *novo;
			novo = malloc(sizeof(user));
			criauser(novo);
			novo->nome = nome;
			novo->mentions++;
			novo->engajamento++;
			if(ptaux->proxment!=NULL){
				ptaux->proxment->antment = novo;
				novo->proxment = ptaux->proxment;
			}
			ptaux->proxment = novo;
			novo->antment = ptaux;
		}
	}
	
	return ptlista;
}	
			

user* criauser(user* novo){
	novo->nome = NULL;
	novo->posts=0;
	novo->mentions=0;
	novo->rts=0;
	novo->engajamento=0;
	novo->proxposts = NULL;
	novo->antposts= NULL;
	novo->proxment=NULL;
	novo->antment=NULL;
	novo->proxrts=NULL;
	novo->antrts=NULL;
	novo->proxenga=NULL;
	novo->antenga=NULL;
	
	return novo;	
}	

l_ment* criamenc(l_ment* novo){
	novo->dado = NULL;
	novo->prox = NULL;
	novo->ant = NULL;
	
	return novo;
}

l_posts* criapost(l_posts* novo){
	novo->dado = NULL;
	novo->prox = NULL;
	novo->ant = NULL;
	
	return novo;
}

l_rts* criarts(l_rts* novo){
	novo->dado = NULL;
	novo->prox = NULL;
	novo->ant = NULL;

	return novo;
}

l_enga* criarenga(l_enga* novo){
	novo->dado = NULL;
	novo->prox = NULL;
	novo->ant = NULL;

	return novo;
}

tweet* criatweet(tweet* novo){
	novo->texto = NULL;
	novo->rts = 0;
	novo->prox = NULL;
	novo->ant= NULL;
	
	return novo;
}

hashtag* criahashtag(hashtag* novo){
	novo->nome = NULL;
	novo->usos = 0;
	novo->relacionadas = 0;
	novo->prox = NULL;
	novo->ant = NULL;

	return novo;
}

hashtag* criarela(l_hash* novo){
	novo->dado = NULL;
	novo->encontros = 0;
	novo->prox = NULL;
	
	return novo;
}
 
