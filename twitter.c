/*
usuario **P_U_AeL[4][3] = [0=post, 1=menc, 2=rts, 3=enga]	[0=ini, 1=fim, 2=raiz]
hashtag **P_H_AeL[3] = [0=ini, 1=fim, 2=raiz]
tweet **P_H_L[2] =  [0=ini, 1=fim]
*/
int learquivo(char *nome,usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L){
  FILE *arq;
  
  arq=fopen(nome,"r");
  if(arq==null)
    return -1;
  else{
	  
	  
      
    usuario *user;
    hashtag *hash;
    tweet *atual;
	  
    char nick[16];
    char simbolo;
    int fimtexto = 0;
    char mencionado[16];
    char hashtag[140];
    
    while(!feof(arq)){
      atual=malloc(sizeof(tweet));
	    
      fseek(arq, 1, SEEK_CUR);
      fscanf(arq ,"%[^;]s",nick);
      fseek(arq, 1, SEEK_CUR);
      do{
      	fscanf(arq ,"%[^;@#]s",atual->texto);
      	fscanf(arq,"%c",simbolo);
      	switch(simbolo){
		case '@':
	   		fscanf(arq,"%[^; ]s",mencionado);
	   		//verifica se existe usuario e insere em árvore de mais mencionados
	   		strcat(atual->texto,"@");
	  		strcat(atual->texto,auxnick);
			break;
		case '#':
			fscanf(arq,"%[^; ]s",hashtag);
			//verifica se existe hashtag e insere em árvore de mais usadas
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
	      
      verifica_exist(nick, atual, POST, NULL, NULL, P_U_AeL, P_H_AeL, P_T_L)   
       
      insere_lista_t(atual, rank_ini,rank_fim);
    }

}
}




usuario verifica_usuario(char *nick,tweet *lido,int param,usuario *raiz, usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L)
{
if(pai==NULL)
  raiz= P_U_AeL[param][RAIZ];
	
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
			
			
		atualiza_lista_u(raiz,POST,P_U_AeL)		
	   	atualiza_lista_u(raiz, RTS,P_U_AeL);
	        atualiza_lista_u(raiz, ENGA,P_U_AeL);		//atualiza listas
	    break;
			
	    case MENC:
		raiz->contador[MENC]++; // incrementa contador de numero de MENÇÕES
		raiz->contador[ENGA]= raiz->curtidas + raiz->contador[MENC] + raiz->contador[RTS];	// atualiza o engajamento
			
		atualiza_lista_u(raiz, ENGA,P_U_AeL);		//atualiza lista
	    break;
			
	}
            return raiz;
        }

        else if(i<0)
        {
            if(raiz->pont[param][ESQ]==NULL)
            {
                raiz->pont[param][ESQ]= verifica_exist(nick, lido, param, raiz->pont[param][ESQ], raiz, P_U_AeL, P_H_AeL, tweet P_T_L);
		    atualiza_arvore_u(raiz->pont[param][ESQ], raiz, pai, param, P_U_AeL);
		return raiz;
            }
            else
                return verifica_exist(nick, lido, param,raiz->pont[param][ESQ], raiz, P_U_AeL, P_H_AeL, tweet P_T_L);

        }

        else
        {
            if(raiz->pont[param][DIR]==NULL)
            {
                raiz->pont[param][DIR]= verifica_exist(nick,lido,param, raiz->pont[POST][DIR], raiz, P_U_AeL, P_H_AeL, tweet P_T_L);
		    atualiza_arvore_u(raiz->pont[param][DIR], raiz, pai, param, P_U_AeL);
                return raiz->pont[param][DIR];
            }
            else
                return verifica_exist(nick,lido,param, raiz->pont[param][DIR],raiz, P_U_AeL, P_H_AeL, tweet P_T_L );
            }

    }
    else // não encontrou na arvore e achou ponto para incerção
    {
       switch(param)
	{
	       case POST:
		return cria_user(nick, lido, 0, P_U_AeL, P_H_AeL, tweet P_T_L);
    		
	       break;
		       
	       case MENC:
		  return cria_user(nick, NULL, 1, P_U_AeL, P_H_AeL, tweet P_T_L);
	       break;
       }
    }	
}	


	
	
usuario cria_user(char *nick, tweet *lido, int flag_menc, usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L)
{	
	usuario *novo;
        novo= malloc(sizeof(usuario));
        strcpy(novo.nickname,nick);
		
	int i, j;
	for(i=0;i<4;i++)
	{
	    novo->contador[i]=0;
	    for(j=0;j<4;j++)
		    novo->pont[i][j]=NULL;
	}
	
	if(flag_menc)
	    novo->contador[ENGA]= 1;
	   
	
	if(lido!=NULL){
	lido->prox_rank=NULL;
	lido->prox_user=NULL;
        novo->curtidas= lido->curtidas;
        novo->tweets= lido;
	novo->contador[POST]=1;
	novo->contador[RTS]=lido->retweets;
	novo->contador[ENGA]= novo->curtidas +novo->contador[ENGA] +novo->contador[RTS];
	}
	
	
		insere_lista_u(novo, POST,P_U_AeL);
		insere_lista_u(novo, MENC,P_U_AeL);
		insere_lista_u(novo, RTS,P_U_AeL);
		insere_lista_u(novo, ENGA,P_U_AeL);

        return novo;
}





usuario insere_lista_u(usuario *novo,int param,usuario **P_U_AeL){
	if(P_U_AeL[param][FIM]!=NULL) // caso a lista não seja vazia
        {
            usuario *aux;
            aux=fim;

                while((aux->contador[param]) < (novo->contardor[param]) && aux!=NULL)	// encontra primeiro item da lista com numero >= de posts
                {
                    aux=aux->pont[param][ANT];
                }

                while(strcmp(novo->nickname,aux->nickname)<0 && aux->contador[param] == novo->contador[param] && aux!=NULL) // acha ordem alfabetica dentro entre os itens com o mesmo numero de acessos (aux sera anterior a novo)
                {
                    aux=aux->pont[param][ANT];
                }
		 
		if(aux==NULL)
		   P_U_AeL[param][INI]=novo;
		
		novo= insere_pre_aux(novo, aux, param);
                
        }
	else
       	{
 	        novo->pont[param][ANT]=NULL;
                novo->pont[param][PROX]=NULL;
        }
	
	return novo;

}


int atualiza_lista_u(usuario *user,int param,usuario **P_U_AeL){
	if(user!=ini)
		if(user->contador[param] > user->pont[param][ANT]->contador[param])
		{
			usuario aux;
			aux= user->pont[param][ANT];
	
			while(aux!=NULL && (aux->contador[param] < user->contador[param]))
			{
				
				aux= aux->pont[param][ANT];
			}
	
			while(strcmp(novo->nickname,aux->nickname)<0 && aux->contador[param] == novo->contador[param] && aux!=NULL)
			{
				aux= aux->pont[param][ANT];
			}
			
			if(user==fim)
			   fim= user->pont[param][ANT];
			user= tira_lista(user, param);
			user= insere_pre_aux(user, aux, param);
		
	                 return 1;
		}
                    return 0;

	
}

usuario tira_lista(usuario *user,int param, usuario **P_U_AeL)
{
	if(user == P_U_AeL[param][FIM]){
		user->pont[param][ANT]->pont[param][PROX] = NULL;
		fim= user->pont[param][ANT];
		user->pont[param][ANT]= NULL;
	}
	else{
		user->pont[param][ANT]->pont[param][PROX]= user->pont[param][PROX];
		user->pont[param][PROX]->pont[param][ANT]= user->pont[param][ANT];
		
		user->pont[param][ANT]=NULL;
		user->pont[param][PROX]=NULL;	
	}
	return user;
	
}

usuario insere_pre_aux(usuario *user, usuario *aux,int param, usuario **P_U_AeL){
	if(aux==NULL)
	{
		user->pont[param][PROX]=P_U_AeL[param][INI];
		P_U_AeL[param][INI]->pont[param][ANT]= user;
		P_U_AeL[param][INI]= user;
	}
	else
	{
		usuario terceiro;
		terceiro = aux->pont[param][PROX];
		
		aux->pont[param][PROX]= user;
		terceiro->pont[param][ANT]= user;
		
		user->pont[param][ANT]= aux;
		user->pont[param][PROX]= terceiro;
	}
	
	return user;
}


void atualiza_arvore_u(usuario *filho,usuario *pai,usuario *vo,int param,usuario **P_U_AeL){
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
	   else
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
	
	   P_U_AeL[param][RAIZ] = filho;
	   pai->pont[param][j] = filho->pont[param][k];
	   filho->pont[param][k] = pai;
	}
	   
   }	   
}

tweet insere_lista_t(tweet *novo,tweet *ini,tweet *fim){
	if(fim!=NULL) // caso a lista não seja vazia
        {
            tweet *aux;
            aux=fim;

            if(aux==ini)
            {
                if(strcmp(novo->texto,aux->texto)<0)
                {
                    novo->rank[ANT]= NULL;
                    novo->rank[PROX]= aux;
                    aux->rank[ANT]= novo;
                    ini=novo;
                }
                else
                {
                    novo->rank[ANT]=aux;
                    novo->rank[PROX]=NULL;
                    aux->rank[PROX]=novo;
                    fim=novo;
                }

            }
            else
            {

                while((aux->retweets) < (novo->retweets) && aux!=ini)	// encontra primeiro item da lista com numero >= de posts
                {
                    aux=aux->rank[ANT];
                }

                while(strcmp(novo->texto,aux->texto)<0 && aux->retweets == novo->retweets && aux!=ini) // acha ordem alfabetica dentro entre os itens com o mesmo numero de acessos (aux sera anterior a novo)
                {
                    aux=aux->rank[ANT];
                }
		    

                if(aux == fim)	// caso tenha que inserir o novo no fim da lista
                {
                    novo->rank[ANT]=aux;
                    novo->rank[PROX]=NULL;
                    aux->rank[PROX]=novo;
                    fim=novo;
                }
                else if(aux == ini &&  aux->retweets == novo->retweets && strcmp(novo->texto,aux->texto)<0) //// caso tenha que inserir o novo no inicio da lista
                {
                    novo->rank[ANT]= NULL;
                    novo->rank[PROX]= aux;
                    aux->rank[ANT]= novo;
                    ini=novo;
                }
                else
                {
                    tweet terceiro;
                    terceiro = aux->rank[PROX];


                    aux->rank[PROX] = novo;
                    terceiro->rank[ANT] = novo;

                    novo->rank[ANT]= aux;
                    novo->rank[PROX]= terceiro;
                }
            }
            else
            {
                novo->rank[ANT]=NULL;
                novo->rank[PROX]=NULL;
            }
        }
	
	return novo;

}
