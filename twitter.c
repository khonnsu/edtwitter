int learquivo(char *nome,usuario *raiz_post, usuario *ini_post, usuario *fim_post,usuario *raiz_menc, usuario *ini_menc, usuario *fim_menc, usuario *ini_rts, usuario *fim_rts,usuario *raiz_enga, usuario *ini_enga, usuario *fim_enga, hashtag *raiz_r, hashtag *ini_h, hashtag *fim_h){
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
    char texto_tweet[141];
    
    while(!feof(arq)){
      atual=malloc(sizeof(tweet));
      scanf("%[^;]s",nick);
      user = verifica_exist(nick, raiz_post, ini_post, fim_post,raiz_menc, ini_menc, fim_menc, ini_rts, fim_rts, raiz_enga, ini_enga, fim_enga );
      if(user == NULL){
        user=malloc(sizeof(user));
        user->nickname = nick;
      }
      
      
          
    }
 
    
    else
  }

}







usuario verifica_usuario(char *nick,usuario *raiz_post, usuario *ini_post, usuario *fim_post,usuario *raiz_menc, usuario *ini_menc, usuario *fim_menc,usuario *raiz_rts, usuario *ini_rts, usuario *fim_rts,usuario *raiz_enga, usuario *ini_enga, usuario *fim_enga)
{
    if(raiz_post!=NULL)
    {

        int i =strcmp(nick,raiz_post->nickname);
        if(i==0)
        {
            return raiz_post;
        }

        else if(i<0)
        {
            if(raiz_post->pont[POST][ESQ]==NULL)
            {
                raiz_post->pont[POST][ESQ]= verifica_exist(nick, raiz_pont->pont[POST][ESQ], ini_post, fim_post,raiz_menc, ini_menc, fim_menc, raiz_rts, ini_rts, fim_rts, raiz_enga, ini_enga, fim_enga);
                return raiz_post->pont[POST][ESQ];
            }
            else
                return verifica_exist(nick, raiz_post->pont[POST][ESQ], ini_post, fim_post,raiz_menc, ini_menc, fim_menc, raiz_rts, ini_rts, fim_rts, raiz_enga, ini_enga, fim_enga);

        }

        else
        {
            if(raiz->pont[POST][DIR]==NULL)
            {
                raiz_post->pont[POST][DIR]= verifica_exist(nick, raiz_post->pont[POST][DIR], ini_post, fim_post,raiz_menc, ini_menc, fim_menc, raiz_rts, ini_rts, fim_rts, raiz_enga, ini_enga, fim_enga);
                return raiz_post->pont[POST][DIR];
            }
            else
                return verifica_exist(nick, raiz->pont[POST][DIR], ini_post, fim_post,raiz_menc, ini_menc, fim_menc, raiz_rts, ini_rts, fim_rts, raiz_enga, ini_enga, fim_enga );

            }

    }
    else // não encontrou na arvore e achou ponto para incerção
    {
	    return cria_user(nick,ini_post, fim_post,raiz_menc, ini_menc, fim_menc, raiz_rts, ini_rts, fim_rts, raiz_enga, ini_enga, fim_enga );
    }	
}	


	
	
usuario cria_user(char *nick, usuario *ini_post, usuario *fim_post,usuario *raiz_menc, usuario *ini_menc, usuario *fim_menc, usuario *ini_rts, usuario *fim_rts,usuario *raiz_enga, usuario *ini_enga, usuario *fim_enga)
{	
	usuario *novo;
        novo= malloc(sizeof(usuario));
        strcpy(novo.nickname,nick);
        novo->curtidas= 0;
        novo->tweets= NULL;
	    
	int i, j;
	for(i=0;i<4;i++)
	{
	    novo->contador[i]=0;
	    for(j=0;j<4;j++)
		    novo->pont[i][j]=NULL;
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

            if(aux==ini)
            {
                if(strcmp(novo->nickname,aux->nickname)<0)
                {
                    novo->pont[param][ANT]= NULL;
                    novo->pont[param][PROX]= aux;
                    aux->pont[param][ANT]= novo;
                    ini=novo;
                }
                else
                {
                    novo->pont[param][ANT]=aux;
                    novo->pont[param][PROX]=NULL;
                    aux->pont[param][PROX]=novo;
                    fim=novo;
                }

            }
            else
            {

                while((aux->contador[param]) < (novo->contar[param]) && aux!=ini)	// encontra primeiro item da lista com numero >= de posts
                {
                    aux=aux->pont[param][ANT];
                }

                while(strcmp(novo->nickname,aux->nickname)<0 && aux->contador[param] == novo->contador[param] && aux!=ini) // acha ordem alfabetica dentro entre os itens com o mesmo numero de acessos (aux sera anterior a novo)
                {
                    aux=aux->pont[param][ANT];
                }
		    

                if(aux == fim)	// caso tenha que inserir o novo no fim da lista
                {
                    novo->pont[param][ANT]=aux;
                    novo->pont[param][PROX]=NULL;
                    aux->pont[param][PROX]=novo;
                    fim=novo;
                }
                else if(aux == ini &&  aux->contador[param] == novo->contador[param] && strcmp(novo->nickname,aux->nickname)<0) //// caso tenha que inserir o novo no inicio da lista
                {
                    novo->pont[param][ANT]= NULL;
                    novo->pont[param][PROX]= aux;
                    aux->pont[param][ANT]= novo;
                    ini=novo;
                }
                else
                {
                    usuario terceiro;
                    terceiro = aux->pont[param][PROX];


                    aux->pont[param][PROX] = novo;
                    terceiro->pont[param][ANT] = novo;

                    novo->pont[param][ANT]= aux;
                    novo->pont[param][PROX]= terceiro;
                }
            }
            else
            {
                novo->pont[param][ANT]=NULL;
                novo->pont[param][PROX]=NULL;
            }
        }
	
	return novo;

}
