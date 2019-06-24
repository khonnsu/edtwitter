int learquivo(char *nome,usuario *raiz_post, usuario *ini_post, usuario *fim_post,usuario *raiz_menc, usuario *ini_menc, usuario *fim_menc, usuario *ini_rts, usuario *fim_rts,usuario *raiz_enga, usuario *ini_enga, usuario *fim_enga, hashtag *raiz_r, hashtag *ini_h, hashtag *fim_h, tweet *rank_ini, tweet *rank_fim){
  FILE *arq;
  
  arq=fopen(nome,"r");
  if(arq==null)
    return -1;
  else{
      
    usuario *user;
    raiz_u = user;
    ini_u = user;
    fim_u = user;

    hashtag *hash;
    raiz_h = hash;
    ini_h = hash;
    fim_h = hash;
    
    char nick[16];
    tweet atual;
    
    while(!feof(arq)){
      atual=malloc(sizeof(tweet));
	    
      fscanf(arq ,"%[^;]s",nick);
      fseek(arq, 1, SEEK_CUR);
      fscanf(arq ,"%[^;]s",atual->texto);
      fseek(arq, 1, SEEK_CUR);
      fscanf(arq ,"%d",&atual->retweets);
      fseek(arq, 1, SEEK_CUR);
      fscanf(arq ,"%d",&atual->curtidas);
      fseek(arq, 1, SEEK_CUR);
	      
      verifica_exist(nick, atual, raiz_post, ini_post, fim_post,raiz_menc, ini_menc, fim_menc, ini_rts, fim_rts, raiz_enga, ini_enga, fim_enga ); 
       
      insere_lista_t(atual, rank_ini,rank_fim);
    }

}
}







usuario verifica_usuario(char *nick,tweet *lido,usuario *raiz_post, usuario *ini_post, usuario *fim_post,usuario *raiz_menc, usuario *ini_menc, usuario *fim_menc,usuario *raiz_rts, usuario *ini_rts, usuario *fim_rts,usuario *raiz_enga, usuario *ini_enga, usuario *fim_enga)
{
    if(raiz_post!=NULL)
    {

        int i =strcmp(nick,raiz_post->nickname);
        if(i==0)
        {
	    lido->prox_user= raiz_post->tweets;
	    raiz_post->tweets= lido;			//insere na lista de posts do usuario
		
		
	    raiz_post->contador[POSTS]++; // incrementa contador de numero de posts
		
	    raiz_post->curtidas += lido->curtidas;	// soma o numero de curtidas do novo tweet
		
	    raiz_post->contador[RTS] += lido->retweets;	//soma o numero de rts do novo tweet
	    
	    raiz_post->contador[ENGA]= raiz_post->curtidas + raiz_post->contador[MENC] + raiz_post->contador[RTS];	// atualiza o engajamento

	    if(atualiza_lista_u(raiz_post, POST,ini_post,fim_post))
                atualiza_arvore_u(raiz_post,POST,raiz_post);

	    raiz_post= atualiza_lista_u(raiz_post, MENC,ini_menc,fim_menc);
	    raiz_post= atualiza_lista_u(raiz_post, RTS,ini_rts,fim_rts);
	    raiz_post= atualiza_lista_u(raiz_post, ENGA,ini_enga,fim_enga);		//atualiza listas
		
		
            return raiz_post;
        }

        else if(i<0)
        {
            if(raiz_post->pont[POST][ESQ]==NULL)
            {
                raiz_post->pont[POST][ESQ]= verifica_exist(nick, lido, raiz_pont->pont[POST][ESQ], ini_post, fim_post,raiz_menc, ini_menc, fim_menc, raiz_rts, ini_rts, fim_rts, raiz_enga, ini_enga, fim_enga);
		return raiz_post->pont[POST][ESQ];
            }
            else
                return verifica_exist(nick, lido, raiz_post->pont[POST][ESQ], ini_post, fim_post,raiz_menc, ini_menc, fim_menc, raiz_rts, ini_rts, fim_rts, raiz_enga, ini_enga, fim_enga);

        }

        else
        {
            if(raiz->pont[POST][DIR]==NULL)
            {
                raiz_post->pont[POST][DIR]= verifica_exist(nick,lido, raiz_post->pont[POST][DIR], ini_post, fim_post,raiz_menc, ini_menc, fim_menc, raiz_rts, ini_rts, fim_rts, raiz_enga, ini_enga, fim_enga);
                return raiz_post->pont[POST][DIR];
            }
            else
                return verifica_exist(nick,lido, raiz->pont[POST][DIR], ini_post, fim_post,raiz_menc, ini_menc, fim_menc, raiz_rts, ini_rts, fim_rts, raiz_enga, ini_enga, fim_enga );

            }

    }
    else // não encontrou na arvore e achou ponto para incerção
    {
	    return cria_user(nick, lido, 0,ini_post, fim_post,raiz_menc, ini_menc, fim_menc, raiz_rts, ini_rts, fim_rts, raiz_enga, ini_enga, fim_enga );
    }	
}	


	
	
usuario cria_user(char *nick, tweet *lido, int flag_menc, usuario *ini_post, usuario *fim_post,usuario *raiz_menc, usuario *ini_menc, usuario *fim_menc, usuario *ini_rts, usuario *fim_rts,usuario *raiz_enga, usuario *ini_enga, usuario *fim_enga)
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
	
	
		insere_lista_u(novo, POST,ini_post,fim_post);
		insere_lista_u(novo, MENC,ini_menc,fim_menc);
		insere_lista_u(novo, RTS,ini_rts,fim_rts);
		insere_lista_u(novo, ENGA,ini_enga,fim_enga);

        return novo;
}





usuario insere_lista_u(usuario *novo,int param,usuario *ini,usuario *fim){
	if(fim!=NULL) // caso a lista não seja vazia
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
		    
		novo= insere_pre_aux(novo, aux, param);
                
        }
	else
       	{
 	        novo->pont[param][ANT]=NULL;
                novo->pont[param][PROX]=NULL;
        }
	
	return novo;

}


int atualiza_lista_u(usuario *user,int param,usuario *ini,usuario *fim){
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
			
			
			user= tira_lista(user, param);
			user= insere_pre_aux(user, aux, param);
		
	                 return 1
		}
	         else
                    return 0;
	
	
}

usuario tira_lista(usuario *user,int param, usuario *ini,usuario *fim)
{
	if(user == fim){
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

usuario insere_pre_aux(usuario *user, usuario *aux,int param, usuario *ini,usuario *fim){
	if(aux==NULL)
	{
		user->pont[param][PROX]=ini;
		ini->pont[param][ANT]= user;
		ini= user;
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


usuario atualiza_arvore_u(usuario *procurado,int param,usuario *raiz){
   if(procurado!=raiz)
     if(procurado->contador[param] < raiz->contador[param])
        if(strcmp(procurado->nickname,raiz->nickname)<0)
           raiz->pont[param][ESQ]= atualiza_arvore_u(procurado,param,raiz->pont[param][ESQ]);
        else
           raiz->pont[param][DIR]= atualiza_arvore_u(procurado,param,raiz->pont[param][DIR]);

     else

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
