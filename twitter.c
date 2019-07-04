/*
usuario *P_U_AeL[4][3] = [0=post, 1=menc, 2=rts, 3=enga]	[0=ini, 1=fim, 2=raiz]
hashtag *P_H_AeL[3] = [0=ini, 1=fim, 2=raiz]
tweet *P_H_L[2] =  [0=ini, 1=fim]
*/

typedef usuario** APONTA_USUARIOS;
typedef hashtag** APONTA_HASHTAGS;
typedef tweet** APONTA_TWEETS;

typedef usuario* USUARIO;
typedef hashtag* HASHTAG;
typedef tweet* TWEET;



#include "twitter.h"
int learquivo(FILE *arq,usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L){
  
    usuario *user;
    hashtag *hash;
    tweet *atual;
    l_hash *mesmo_T;
	  
    char nick[16];
    char simbolo;
    int fimtexto = 0;
    char n_mencionado[16];
    char hashtag[140];
    
    while(!feof(arq)){
      atual=malloc(sizeof(tweet));
	    
      fseek(arq, 1, SEEK_CUR);
      fscanf(arq ,"%[^;]s",nick);
      fseek(arq, 1, SEEK_CUR);
      *mesmo_T=NULL;
      do{
      	fscanf(arq ,"%[^;@#]s",atual->texto);
      	fscanf(arq,"%c",simbolo);
      	switch(simbolo){
		case '@':
	   		fscanf(arq,"%[^; ]s",n_mencionado);
			*P_U_AeL[MENC][RAIZ] = verifica_exist(n_mencionado,NULL,MENC, 0,NULL,NULL, NULL,*P_U_AeL,*P_H_AeL,*P_T_L);
	   		strcat(atual->texto,"@");
	  		strcat(atual->texto,auxnick);
			break;
		case '#':
			fscanf(arq,"%[^; ]s",hashtag);
			*P_H_AeL[RAIZ] = verifica_hashtag(hashtag ,mesmo_T, NULL, NULL, *P_H_AeL);
			strcat(atual->texto,"#");
			strcat(atual->texto,hashtag);
		case ';':
			fimtexto=1;
	}
      }while(!fimtexto);
      fseek(arq, 1, SEEK_CUR);
      fscanf(arq ,"%d",&atual->retweets);
      fseek(arq, 1, SEEK_CUR);
      fscanf(arq ,"%d",&atual->curtidas);
      fseek(arq, 1, SEEK_CUR);
	      
      *P_U_AeL[POST][RAIZ]= verifica_exist(nick, atual, POST, 0, NULL, NULL, NULL, *P_U_AeL, *P_H_AeL, *P_T_L);
      relaciona(*mesmo_T);
      destroi(mesmo_T);
       
      insere_lista_t(atual, P_T_L);
    }

}




usuario *verifica_usuario(char *nick,tweet *lido,int param,int outro,usuario *raiz, usuario *pai, usuario *procurado,usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L)
{
if(pai==NULL)
  raiz= *P_U_AeL[param][RAIZ];
	
    if(raiz!=NULL)
    {

        int i =strcmp(nick,raiz->nickname);
        if(i==0)
        {
			switch(param)
			{
			    case POST:
				   lido->prox_user= raiz->tweets;
				   raiz->tweets= lido;			//insere na lista de posts do usuario


				   raiz->contador[POSTS]++; // incrementa contador de numero de posts

				   raiz->curtidas += lido->curtidas;	// soma o numero de curtidas do novo tweet

				   raiz->contador[RTS] += lido->retweets;	//soma o numero de rts do novo tweet

				   raiz->contador[ENGA]= raiz->curtidas + raiz->contador[MENC] + raiz->contador[RTS];	// atualiza o engajamento


				   atualiza_lista_u(raiz,POST,*P_U_AeL)		
				   atualiza_lista_u(raiz, RTS,*P_U_AeL);
				   atualiza_lista_u(raiz, ENGA,*P_U_AeL);		//atualiza listas
					
				   *P_U_AeL[MENC][RAIZ] = verifica_exist(nick,lido,param, 1, NULL, NULL, raiz,*P_U_AeL, *P_H_AeL, *P_T_L);

			    break;

			    case MENC:
				raiz->contador[MENC]++; // incrementa contador de numero de MENÇÕES
				raiz->contador[ENGA]= raiz->curtidas + raiz->contador[MENC] + raiz->contador[RTS];	// atualiza o engajamento

				    atualiza_lista_u(raiz, ENGA,*P_U_AeL);		//atualiza lista
				    *P_U_AeL[POST][RAIZ] = verifica_exist(nick,lido,param, 1, NULL, NULL, raiz,*P_U_AeL, *P_H_AeL, *P_T_L);

			    break;

			}

		
		return raiz;
	}

        else if(i<0)
        {
		usuario *temp = raiz->pont[param][ESQ];
                raiz->pont[param][ESQ]= verifica_exist(nick, lido, param, outro, raiz->pont[param][ESQ], raiz, procurado,*P_U_AeL, *P_H_AeL, *P_T_L);
		if(temp!=raiz->pont[param][ESQ])
		    raiz = atualiza_arvore_u(raiz->pont[param][ESQ], raiz, pai, param, *P_U_AeL);
		return raiz;
        }
        else
        {	
		usuario *temp = raiz->pont[param][DIR];
		
                raiz->pont[param][DIR]= verifica_exist(nick,lido,param, outro, raiz->pont[POST][DIR], raiz,procurado , *P_U_AeL, *P_H_AeL, *P_T_L);
		if(temp!=raiz->pont[param][DIR])
		    raiz = atualiza_arvore_u(raiz->pont[param][DIR], raiz, pai, param, *P_U_AeL);
                return raiz;
        }
	    
    else // não encontrou na arvore e achou ponto para incerção
    {
       if(!outro)
       {
	       switch(param)
		{
		       case POST:
			return cria_user(nick, lido, 0, *P_U_AeL, *P_H_AeL, *P_T_L);

		       break;

		       case MENC:
			  return cria_user(nick, NULL, 1, *P_U_AeL, *P_H_AeL, *P_T_L);
		       break;
	       }
       }
       else
       {
	       return procurado;
       }
    }	
}	


	
	
usuario *cria_user(char *nick, tweet *lido, int flag_menc, usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L)
{	
	usuario *novo;
        novo= malloc(sizeof(usuario));
        strcpy(novo.nickname,nick);
	novo->pont=malloc(16*sizeof(*usuario));
		
	int i, j;
	for(i=0;i<4;i++)
	{
	    novo->contador[i]=0;
	    for(j=0;j<4;j++)
		    novo->pont[i][j]=NULL;
	}
	
	if(flag_menc)
	{    
	    novo->contador[ENGA]= 1;
	}
	   
	
	if(lido!=NULL){
	lido->pont[PROX]=NULL;
	lido->prox_user=NULL;
        novo->curtidas= lido->curtidas;
        novo->tweets= lido;
	novo->contador[POST]=1;
	novo->contador[RTS]=lido->retweets;
	novo->contador[ENGA]= novo->curtidas +novo->contador[ENGA] +novo->contador[RTS];
	}
	
	
		insere_lista_u(novo, POST,*P_U_AeL);
		insere_lista_u(novo, MENC,*P_U_AeL);
		insere_lista_u(novo, RTS,*P_U_AeL);
		insere_lista_u(novo, ENGA,*P_U_AeL);
	
	

        return novo;
}





usuario *insere_lista_u(usuario *novo,int param,usuario **P_U_AeL){
	if(*P_U_AeL[param][FIM]!=NULL) // caso a lista não seja vazia
        {
            usuario *aux;
            aux=*P_U_AeL[param][FIM];

                while aux!=NULL)	// encontra primeiro item da lista com numero >= de posts
                {
	            if(aux->contador[param]) >= (novo->contador[param]))
			    break;
                    aux=aux->pont[param][ANT];
                }

                while(aux!=NULL) // acha ordem alfabetica dentro entre os itens com o mesmo numero de acessos (aux sera anterior a novo)
                {
		    if(strcmp(novo->nickname,aux->nickname)>= 0 && aux->contador[param] == novo->contador[param])
			    break;
                    aux=aux->pont[param][ANT];
                }
		
		novo= insere_pre_aux(novo, aux, param);
                
        }
	else
       	{
 	        novo->pont[param][ANT]=NULL;
                novo->pont[param][PROX]=NULL;
		*P_U_AeL[param][INI]= novo;
		*P_U_AeL[param][FIM]= novo;
        }
	
	return novo;

}


int atualiza_lista_u(usuario *user,int param,usuario **P_U_AeL){
	if(user!=*P_U_AeL[param][INI])
		if(user->contador[param] > user->pont[param][ANT]->contador[param])
		{
			usuario *aux;
			aux= user->pont[param][ANT];
	
			while(aux!=NULL)
			{
				if(aux->contador[param]) >= (user->contador[param]))
			    		break;
				aux= aux->pont[param][ANT];
			}
	
			while(aux!=NULL)
			{
				if(strcmp(user->nickname,aux->nickname)>= 0 && aux->contador[param] == user->contador[param])
			    		break;
				aux= aux->pont[param][ANT];
			}
			user= tira_lista(user, param, *P_U_AeL);
			user= insere_pre_aux(user, aux, param, *P_U_AeL);
		
	                 return 1;
		}
                    return 0;
}
	
	
	

usuario *tira_lista(usuario *user,int param, usuario **P_U_AeL)
{
	if(user == *P_U_AeL[param][FIM]){
		user->pont[param][ANT]->pont[param][PROX] = NULL;
		*P_U_AeL[param][FIM] = user->pont[param][ANT];
		user->pont[param][ANT]= NULL;
	}
	else
	{
		
		user->pont[param][ANT]->pont[param][PROX]= user->pont[param][PROX];
		user->pont[param][PROX]->pont[param][ANT]= user->pont[param][ANT];
		user->pont[param][ANT]=NULL;
		user->pont[param][PROX]=NULL;	
	}
	return user;
	
}
	
	

usuario *insere_pre_aux(usuario *user, usuario *aux,int param, usuario **P_U_AeL){
	if(aux==NULL)
	{
		user->pont[param][PROX]=*P_U_AeL[param][INI];
		*P_U_AeL[param][INI]->pont[param][ANT]= user;
		*P_U_AeL[param][INI]= user;
	}
	else
	{
		if(aux!=*P_U_AeL[param][FIM])
		{
			usuario *terceiro;
			terceiro = aux->pont[param][PROX];
			
			aux->pont[param][PROX]= user;
			terceiro->pont[param][ANT]= user;
		
			user->pont[param][ANT]= aux;
			user->pont[param][PROX]= terceiro;
		}
		else
		{
			user->pont[param][ANT]=*P_U_AeL[param][FIM];
			*P_U_AeL[param][FIM]->pont[param][PROX]= user;
			*P_U_AeL[param][FIM]= user;
		}
	}
	
	return user;
}
	
	


usuario *atualiza_arvore_u(usuario *filho,usuario *pai,usuario *vo,int param,usuario **P_U_AeL){
   if(filho->contador[param]>pai->contador[param])
   {
	int i, j, k;
	
	if(vo!=NULL){
	   if(vo->pont[param][DIR] == pai)
	      i=DIR;
	   else
	      i=ESQ;
	   
	   if(pai->pont[param][DIR] == filho)
	   {
	      j=DIR;
	      k=ESQ;
	   }
	   else8
	   {
	      j=ESQ;
	      k=DIR;
	   }
	   
	vo->pont[param][i] = filho;
	pai->pont[param][j] = filho->pont[param][k];
	filho->pont[param][k] = pai;
	}
	   
	else
	{
	   if(pai->pont[param][DIR] == filho)
	   {
	      j=DIR;
	      k=ESQ;
	   }
	   else
	   {
	      j=ESQ;
	      k=DIR;
	   }
	
	   *P_U_AeL[param][RAIZ] = filho;
	   pai->pont[param][j] = filho->pont[param][k];
	   filho->pont[param][k] = pai;
	}
      return filho; 
   }
   return pai;
}

	
	




hashtag *verifica_hashtag(char *hash, l_hash *mesmo_T, hashtag *raiz, hashtag *pai, hashtag **P_H_AeL)
{
if(pai==NULL)
  raiz= *P_H_AeL[RAIZ];
	
    if(raiz!=NULL)
    {
        int i =strcmp(hash,raiz->nome);
        if(i==0)
        {
	    raiz->usos++; // incrementa contador de usos da hashtag
		
	    atualiza_lista_h(raiz ,*P_H_AeL)		//atualiza lista
		    
	   l_hash *aux;
	   aux= mesmoT;
	   while(aux->prox!=NULL)
	      aux=aux->prox;
	   aux->prox=malloc(sizeof(l_hash));
	   aux->prox->dado= raiz;
           aux->prox->prox= NULL;
	  
	
           return raiz;
        }

        else if(i<0)
        {
                hashtag *temp = raiz->pont[ESQ];
		
		raiz->pont[ESQ] = verifica_hashtag(hash ,mesmo_T , raiz->pont[ESQ], raiz, *P_H_AeL);
		if(temp!=raiz->pont[ESQ])
		    raiz = atualiza_arvore_h(raiz->pont[ESQ], raiz, pai, *P_H_AeL);
		return raiz;

        }
        else
        {
		hashtag *temp = raiz->pont[DIR];
                raiz->pont[DIR]= verifica_hashtag(hash,mesmo_T, raiz->pont[DIR], raiz, *P_H_AeL);
		if(temp!=raiz->pont[DIR])
		    raiz = atualiza_arvore_h(raiz->pont[DIR], raiz, pai, *P_H_AeL);
                return raiz;
        }
    else // não encontrou na arvore e achou ponto para incerção
    {
	raiz= cria_hash(hash, *P_H_AeL);
	
	l_hash *aux;
	aux= mesmoT;
	while(aux->prox!=NULL)
	   aux=aux->prox;
	aux->prox=malloc(sizeof(l_hash));
	aux->prox->dado= raiz;
        aux->prox->prox= NULL;
	    
	    
	return raiz;
    }	
}	


	
	
hashtag *cria_hash(char *hash,hashtag **P_H_AeL)
{	
	hashtag *novo;
        novo= malloc(sizeof(hashtag));
        strcpy(novo.nome,nick);
		
        novo->usos= 1;

        novo = insere_lista_h(novo,*P_H_AeL);
	
	hash->associadas = malloc(3*sizeof(*relacionadas));	
	int i;
	for(i=0;i<3;i++)
		hash->associadas[i]=NULL;

        return novo;
}





hashtag *insere_lista_h(hashtag *novo,hashtag **P_H_AeL){
	if(*P_H_AeL[FIM]!=NULL) // caso a lista não seja vazia
        {
            hashtag *aux;
            aux=*P_H_AeL[FIM];

                while(aux!=NULL)	// encontra primeiro item da lista com numero >= de posts
                {
		    if((aux->usos) >= (novo->usos))
			    break;
                    aux=aux->pont[ANT];
                }

                while(aux!=NULL) // acha ordem alfabetica dentro entre os itens com o mesmo numero de acessos (aux sera anterior a novo)
                {
		    if(strcmp(novo->nome,aux->nome)>= 0 && aux->usos == novo->usos)
			    break;
                    aux=aux->pont[ANT];
                }
		
		novo= insere_pre_aux_h(novo, aux, *P_H_AeL);
                
        }
	else
       	{
 	        novo->pont[ANT]=NULL;
                novo->pont[PROX]=NULL;
		*P_U_AeL[INI]= novo;
		*P_U_AeL[FIM]= novo;
        }
	
	return novo;

}


int atualiza_lista_h(hashtag *hash ,hashtag **P_H_AeL){
	if(hash!=*P_H_AeL[INI])
		if(hash->usos > hash->pont[ANT]->usos)
		{
			hashtag *aux;
			aux= hash->pont[ANT];
	
			while(aux!=NULL)
			{
				if(aux->usos) >= (hash->usos))
			    		break;
				aux= aux->pont[ANT];
			}
	
			while(aux!=NULL)
			{
				if(strcmp(hash->nome,aux->nome)>= 0 && aux->usos == hash->usos)
			    		break;
				aux= aux->pont[ANT];
			}
			
			hash= tira_lista_h(hash, *P_H_AeL);
			hash= insere_pre_aux_h(hash, aux, *P_H_AeL);
		
	                 return 1;
		}
                    return 0;
}

hashtag *tira_lista_h(hashtag *hash, hashtag **P_H_AeL)
{
	if(hash == *P_H_AeL[FIM]){
		hash->pont[ANT]->pont[PROX] = NULL;
		*P_H_AeL[FIM] = hash->pont[ANT];
		hash->pont[ANT]= NULL;
	}
	else{
		hash->pont[ANT]->pont[PROX]= hash->pont[PROX];
		hash->pont[PROX]->pont[ANT]= hash->pont[ANT];
		
		hash->pont[ANT]=NULL;
		hash->pont[PROX]=NULL;	
	}
	return hash;
	
}

hashtag *insere_pre_aux_h(hashtag *hash, hashtag *aux,hashtag **P_H_AeL){
	if(aux==NULL)
	{
		hash->pont[PROX]=P_H_AeL[INI];
		*P_H_AeL[INI]->pont[ANT]= hash;
		*P_H_AeL[INI]= hash;
	}
	else
	{
	   if(aux!=*P_H_AeL[FIM])
	   {
		hashtag *terceiro;
		terceiro = aux->pont[PROX];
		
		aux->pont[PROX]= hash;
		terceiro->pont[ANT]= hash;
		
		hash->pont[ANT]= aux;
		hash->pont[PROX]= terceiro;
	   }
	   else
           {
		hash->pont[ANT]=*P_H_AeL[FIM];
		*P_H_AeL[FIM]->pont[PROX]= hash;
		*P_H_AeL[FIM]= hash;
	   }
	 }
	
	return hash;
}


hashtag *atualiza_arvore_h(hashtag *filho,hashtag *pai,hashtag *vo, hashtag **P_H_AeL){
if(filho->usos > pai->usos)
   {
	int i, j, k;
	
	if(vo!=NULL){
	   if(vo->pont[DIR] == pai)
	      i=DIR;
	   else
	      i=ESQ;
	   
	   if(pai->pont[DIR] == filho)
	   {
	      j=DIR;
	      k=ESQ;
	   }
	   else
	   {
	      j=ESQ;
	      k=DIR;
	   }
	   
	   vo->pont[i] = filho;
	   pai->pont[j] = filho->pont[k];
	   filho->pont[k] = pai;
	}  
	else
	{
	   if(pai->pont[DIR] == filho)
	   {
	      j=DIR;
	      k=ESQ;
	   }
	   else
	   {
	      j=ESQ;
	      k=DIR;
	   }
	
	   *P_U_AeL[RAIZ] = filho;
	   pai->pont[j] = filho->pont[k];
	   filho->pont[k] = pai;
	}
      return filho;
   }
return pai;
}
	
	
tweet *insere_lista_t(tweet *novo, tweet *P_T_L){
	if(*P_T_L[FIM]!=NULL) // caso a lista não seja vazia
        {
            tweet *aux;
            aux=*P_T_L[FIM];
	   	while(aux!=NULL)
                {
		    if((aux->retweets) >= (novo->retweets))
			    break;
                    aux=aux->pont[ANT];
                }
		while(aux!=NULL) // acha ordem alfabetica dentro entre os itens com o mesmo numero de acessos (aux sera anterior a novo)
                {
		    if(strcmp(novo->texto,aux->texto)>= 0 && aux->retweets == novo->retweets)
			    break;
                    aux=aux->pont[ANT];
                }
		
	    novo= insere_pre_aux_t(novo, aux, *P_T_L);
	}
        else
       	{
 	        novo->pont[ANT]=NULL;
                novo->pont[PROX]=NULL;
		*P_T_L[INI]= novo;
		*P_T_L[FIM]= novo;
        }
	
	return novo;

}
	
tweet *insere_pre_aux_t(tweet *t, tweet *aux, tweet **P_T_L){
	if(aux==NULL)
	{
		t->pont[PROX]=*P_T_L[INI];
		*P_T_L[INI]->pont[ANT]= t;
		*P_T_L[INI]= t;
	}
	else
	{
	   if(aux!=P_T_L[FIM])
	   {
		tweet *terceiro;
		terceiro = aux->pont[PROX];
		
		aux->pont[PROX]= t;
		terceiro->pont[ANT]= t;
		
		t->pont[ANT]= aux;
		t->pont[PROX]= terceiro;
	   }
	   else
           {
		t->pont[ANT]=*P_T_L[FIM];
		*P_T_L[FIM]->pont[PROX]= t;
		*P_T_L[FIM]= t;
	   }
	 }
	
	return t;
}
	
void relaciona(l_hash *mesmo_T)
{
	if(mesmo_T!=NULL)
	{
		hashtag *aux1, *aux2;
		l_hash *cursor;
		while(mesmo_T!=NULL)
		{
		    aux1 = mesmo_T->dado;
		    cursor = mesmo_T->prox;
		    while(cursor!=NULL)
		    {
			aux2=cursor->dado;
			ad_rel(aux1, aux2);
			ad_rel(aux2, aux1);
			cursor=cursor->prox;
		    }
		    mesmo_T= mesmo_T->prox;
		}
			
	}
	
}

void ad_rel(hashtag *aux1 , hashtag *aux2)
{
    if(aux1->associadas[RAIZ]==NULL)
    {
	aux1->associadas= malloc(3* sizeof(*relacionadas));
	for(i=0; i<3; i++)
	   aux1->associadas[i]=NULL;

	    
        aux1->associadas[raiz] = cria_r(aux2, aux1->associadas); 
	    
    }
    else
    {
	   
	  aux1->associadas[RAIZ] = acha_rel(aux2, aux1->associadas, aux1->associadas[RAIZ], NULL);
    }
	
}
	
relacionadas *acha_rel(hashtag *procurada,  relacionadas **ponts,  relacionadas *raiz, relacionadas *pai)
{
if(raiz!=NULL)
    {
        int i =strcmp(procurada->nome,raiz->dado->nome);
        if(i==0)
        {
	    raiz->encontros++; // incrementa contador de usos da hashtag
		
	    atualiza_lista_r(raiz , *ponts)		//atualiza lista 
	
           return raiz;
        }

        else if(i<0)
        {
                relacionadas *temp = raiz->pont[ESQ];
		
		raiz->pont[ESQ] = acha_rel(procurada, *ponts, raiz->pont[ESQ], raiz);
		if(temp!=raiz->pont[ESQ])
		    raiz = atualiza_arvore_r(raiz->pont[ESQ], raiz, pai, *ponts);
		return raiz;

        }
        else
        {
		relacionadas *temp = raiz->pont[DIR];
                raiz->pont[DIR]= acha_rel(procurada,*ponts , raiz->pont[DIR], raiz);
		if(temp!=raiz->pont[DIR])
		    raiz = atualiza_arvore_r(raiz->pont[DIR], raiz, pai, *ponts);
                return raiz;
        }
    else // não encontrou na arvore e achou ponto para incerção
    {
	raiz= cria_r(aux2, *ponts);    
	return raiz;
	    
    }	
}
}
	
	
relacionadas *cria_r(hashtag *nova,relacionadas **P_R)
{	
	relacionadas *novo;
        novo= malloc(3*sizeof(*relacionadas));
        strcpy(novo->dado->nome,nova->nome);
		
        novo->encontros= 1;

        novo = insere_lista_r(novo,*P_R);

        return novo;
}
	
	
relacionadas *insere_lista_r(relacionadas *novo, relacionadas **P_R)
{	
	if(*P_R[FIM]!=NULL) // caso a lista não seja vazia
        {
            relacionadas *aux;
            aux=*P_R[FIM];

                while(aux!=NULL)	// encontra primeiro item da lista com numero >= de posts
                {
		    if((aux->encontros) >= (novo->encontros))
			    break;
                    aux=aux->pont[ANT];
                }

                while(aux!=NULL) // acha ordem alfabetica dentro entre os itens com o mesmo numero de acessos (aux sera anterior a novo)
                {
		    if(strcmp(novo->dado->nome,aux->dado->nome)>= 0 && aux->encontros == novo->encontros)
			    break;
                    aux=aux->pont[ANT];
                }
		
		novo= insere_pre_aux_r(novo, aux, *P_R);
                
        }
	else
       	{
 	        novo->pont[ANT]=NULL;
                novo->pont[PROX]=NULL;
		*P_R[INI]= novo;
		*P_R[FIM]= novo;
        }
	
	return novo;

}
}
	
relacionadas *insere_pre_aux_r(relacionadas *novo, relaciondas *aux,relaciondas **P_R)
{
	if(aux==NULL)
	{
		novo->pont[PROX]=*P_L[INI];
		*P_L[INI]->pont[ANT]= novo;
		*P_L[INI]= novo;
	}
	else
	{
	   if(aux!=*P_L[FIM])
	   {
		relaciondas *terceiro;
		terceiro = aux->pont[PROX];
		
		aux->pont[PROX]= novo;
		terceiro->pont[ANT]= novo;
		
		novo->pont[ANT]= aux;
		novo->pont[PROX]= terceiro;
	   }
	   else
           {
		novo->pont[ANT]=*P_R[FIM];
		*P_R[FIM]->pont[PROX]= novo;
		*P_R[FIM]= novo;
	   }
	 }
	
	return novo;
}
	
	
int atualiza_lista_r(relaciondas *novo ,hashtag **P_R){
	if(novo!=*P_R[INI])
		if(novos->encontros > novo->pont[ANT]->encontros)
		{
			relacionadas *aux;
			aux= novo->pont[ANT];
	
			while(aux!=NULL)
			{
				if(aux->encontros) >= (novo->encontros))
			    		break;
				aux= aux->pont[ANT];
			}
	
			while(aux!=NULL)
			{
				if(strcmp(novo->nome,aux->nome)>= 0 && aux->encontros == user->encontros)
			    		break;
				aux= aux->pont[ANT];
			}
			
			novo= tira_lista_r(hash, *P_R);
			novo= insere_pre_aux_r(hash, aux, *P_R);
		
	                 return 1;
		}
                    return 0;
}
	
	
relacionadas *tira_lista_r(relacionadas *novo, relacionadas **P_R)
{
	if(novo == *P_R[FIM]){
		novo->pont[ANT]->pont[PROX] = NULL;
		*P_R[FIM] = novo->pont[ANT];
		novo->pont[ANT]= NULL;
	}
	else{
		novo->pont[ANT]->pont[PROX]= novo->pont[PROX];
		novo->pont[PROX]->pont[ANT]= novo->pont[ANT];
		
		novo->pont[ANT]=NULL;
		novo->pont[PROX]=NULL;	
	}
	return novo;
	
}

relaciondas *atualiza_arvore_r(relacionadas *filho,relacionadas *pai,relacionadas *vo, relacionadas **P_L){
if(filho->encontros > pai->encontros)
   {
	int i, j, k;
	
	if(vo!=NULL){
	   if(vo->pont[DIR] == pai)
	      i=DIR;
	   else
	      i=ESQ;
	   
	   if(pai->pont[DIR] == filho)
	   {
	      j=DIR;
	      k=ESQ;
	   }
	   else
	   {
	      j=ESQ;
	      k=DIR;
	   }
	   
	   vo->pont[i] = filho;
	   pai->pont[j] = filho->pont[k];
	   filho->pont[k] = pai;
	}  
	else
	{
	   if(pai->pont[DIR] == filho)
	   {
	      j=DIR;
	      k=ESQ;
	   }
	   else
	   {
	      j=ESQ;
	      k=DIR;
	   }
	
	   *P_R[RAIZ] = filho;
	   pai->pont[j] = filho->pont[k];
	   filho->pont[k] = pai;
	}
      return filho;
   }
return pai;
}	


void leparametros(FILE *arquivo, ops *op){	//recebe ponteiro para estrutura com operacoes
	fscanf(arquivo,"%*2c%d",op->a);
	fscanf(arquivo,"%*3c%d",op->b);
	fscanf(arquivo,"%*3c%d",op->c);
	fscanf(arquivo,"%*3c%d",op->d);
	fscanf(arquivo,"%*3c%d",op->e);
	fscanf(arquivo,"%*3c%d",op->f);
	fscanf(arquivo,"%*3c%*[ #]%[;]s",op->hash);
	fscanf(arquivo,"%*c%d",op->g);

	fclose(arquivo);
}

void escrevearquivo(FILE *arq, usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L, ops op, clock_t comeco){
	clock_t fim;
	float tempo;
	int cont;
	
	fprintf(arq,"--- OP A\n");
	cont=0;
	hashtag *aux_hash = P_H_AeL[INI];	
	if(op.a == 0){			
		while(aux_hash!=NULL){
			fprintf(arq,"#%s, %d\n", aux_hash->nome, aux_hash->usos);
			aux_hash=aux_hash->pont[PROX];
		}
	}
	else{
		while(cont<op.a&&aux_hash!=NULL){
		fprintf(arq,"#%s, %d\n", aux_hash->nome, aux_hash->usos);
		aux_hash=aux_hash->pont[PROX];
		cont++;
		}
	}
	fprintf(arq,"--- OP B\n");
	cont=0;
	usuario *aux_user = P_U_AeL[POST][INI];
	if(op.b == 0){
		while(aux_user!=NULL){
			fprintf(arq,"@%s, %d\n", aux_user->nickname, aux_user->contador[POST]);
			aux_user=aux_user->pont[POST][PROX];
		}
	}
	else{
		while(cont<op.b&&aux_user!=NULL){
			fprintf(arq,"@%s, %d\n", aux_user->nickname, aux_user->contador[POST]);
			aux_user=aux_user[POST][PROX];
			cont++;
		}
	}
	fprintf(arq,"--- OP C\n");
	cont = 0;
	tweet *aux_tweet = P_T_L[INI];
	if(op.c == 0){
		while(aux_tweet!=NULL){
			fprintf(arq,"%s, %d\n", aux_tweet->texto, aux_tweet->curtidas);
			aux_tweet=aux_tweet->pont[0];
		}
	}
	else{
		while(cont<op.c&&aux_tweet!=NULL){
			fprintf(arq,"%s, %d\n", aux_tweet->texto, aux_tweet->curtidas);
			aux_tweet=aux_tweet->pont[0];
			cont++;
		}
	}
	fprintf(arq,"--- OP D\n");
	cont = 0;
	aux_user = P_U_AeL[MENC][INI];
	if(op.d == 0){
		while(aux_user!=NULL){
			fprintf(arq,"@%s, %d\n", aux_user->nickname, aux_user->contador[MENC]);
			aux_user=aux_user->pont[MENC][PROX];
		}
	}
	else{
		while(cont<op.d&&aux_user!=NULL){
			fprintf(arq,"@%s, %d\n", aux_user->nickname, aux_user->contador[MENC]);
			aux_user=aux_user->pont[MENC][PROX];
			cont++;
		}
	}
	fprintf(arq,"--- OP E\n");
	cont = 0;
	aux_user = P_U_AeL[RTS][INI];
	if(op.e == 0){
		while(aux_user!=NULL){
			fprintf(arq,"@%s, %d\n", aux_user->nickname, aux_user->contador[RTS]);
			aux_user=aux_user->pont[RTS][PROX];
		}
	}
	else{
		while(cont<op.e&&aux_user!=NULL){
			fprintf(arq,"@%s, %d\n", aux_user->nickname, aux_user->contador[RTS];
			aux_user=aux_user->pont[RTS][PROX];
			cont++
		}
	}
	fprinf(arq,"--- OP F\n");
	cont=0;
	aux_user = P_U_AeL[MENC][INI];
	if(op.f == 0){
		while(aux_user!=NULL){
			fprintf(arq,"@%s, %d\n", aux_user->nickname, aux_user->contador[MENC];
			aux_user=aux_user->pont[MENC][PROX];
		}
	}
	else{
		while(cont<op.f&&aux_user!=NULL){
			fprintf(arq,"@%s, %d\n", aux_user->nickname, aux_user->contador[MENC];
			aux_user=aux_user->pont[MENC][PROX];
			cont++;
		}
	}
	fprinf(arq,"--- OP G\n");
	cont=0;
	relacionadas *aux_rel = cadehashtag(op.hash, *P_H_AeL[RAIZ]);
	if(relacionadas==NULL){
		fprintf(arq,"Hashtag nao encontrada.\n");
	}
	else{
		if(op.g == 0){
			while(aux_user!=NULL){
				fprintf(arq,"#%s, %d\n", aux_rel->dado->nome, aux_rel->encontros);
				aux_rel=aux_rel->pont[PROX];
			}
		}
		else{	
			while(cont<op.g&&aux_user!=NULL){
				fprintf(arq,"#%s, %d\n", aux_rel->dado->nome, aux_rel->encontros);
				aux_rel=aux_rel->pont[PROX];
				cont++;
			}
		}
	}
	fim = clock(); 
	tempo =(float)(fim-comeco)/CLOCKS_PER_SEC;
	fprinf(arq,"TEMPO:%f segundos",tempo);
		
	return;
}
				
relacionadas* cadehashtag(char nome[], hashtag *raiz){
	if(raiz==NULL) return NULL;	
	hashtag *aux_hash = raiz
	i=strcmp(nome,aux_hash->nome);
	if(i==0)
		return aux_hash->associadas;
	else if(i<0)
		return cadehashtag(nome,aux_hash->pont[ESQ]);
	else if(i>0)
		return cadehashtag(nome,aux_hash->pont[DIR]);		
	
}

void cria(usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L)
{
	int i, j;
	for(i=0;i<3;i++)
	{
		*P_U_AeL=malloc(12*sizeof(*usuario));
		*P_H_AeL=malloc(3*sizeof(*hashtag));
		*P_T_L=malloc(3*sizeof(*tweet));
		for(j=0;j<4;j++)
		  *P_U_AeL[j][i]=NULL;
		*P_H_AeL[i]=NULL; 
		*P_T_L[i]=NULL;
	}
}
				
void encerra(usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L)
{
	destroi_u(*P_U_AeL);
	destroi_h(*P_H_AeL);
	destroi_t(*P_T_L);
}

void destroi_u(usuario **lixo)
{
	usuario *aux;
	while(*lixo[POST][INI]!=NULL)
	{
	     aux= *lixo[POST][INI];
	     *lixo[POST][INI] = *lixo[POST][INI]->pont[PROX];
	     destroi_u_pont(aux->pont);
	     free(aux);
	}
}
				
void destroi_u_pont(usuario **lixo)
{
	usuario *aux;
	int i;
	for(i=0; i<16; i++,*lixo = lixo[1])
	{
	     aux= *lixo;
	     free(aux);
	}
}
				
void destroi_t(tweet **lixo)
{
	tweet *aux;
	while(*lixo[INI]!=NULL)
	{
	     aux= *lixo[INI];
	     *lixo[INI] = *lixo[INI]->pont[PROX];
	     destroi_t_pont(aux->pont);
	     free(aux);
	}
}
				
				
void destroi_t_pont(tweet **lixo)
{
	tweet *aux;
	int i;
	for(i=0; i<4; i++,*lixo = lixo[1])
	{
	     aux= *lixo;
	     free(aux);
	}
}	

		  
void destroi_h(hashtag **lixo)
{
	hashtag *aux;
	while(*lixo[INI]!=NULL)
	{
	     aux= *lixo[INI];
	     *lixo[INI] = *lixo[INI]->pont[PROX];
	     destroi_r(aux->associadas);
	     free(aux);
	}
}
				
				
void destroi_r(relacionadas **lixo)
{
	relacionadas *aux;
	while(*lixo[INI]!=NULL)
	{
	     aux= *lixo[INI];
	     *lixo[INI] = *lixo[INI]->prox;
	     free(aux);
	}
}
				
void destroi(l_hash **lixo)
{
	l_hash *aux;
	while(*lixo[INI]!=NULL)
	{
	     aux= *lixo[INI];
	     *lixo[INI] = *lixo[INI]->pont[PROX];
	     free(aux);
	}
}
				
	
				
