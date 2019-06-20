int learquivo(char *nome,usuario *raiz_u, usuario *ini_u, usuario *fim_u, hashtag *raiz_h, hashtag *ini_h, hashtag *fim_h){
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
      user = verifica_exist(nick);
      if(user == NULL){
        user=malloc(sizeof(user));
        user->nickname = nick;
      }
      
      
          
    }
 
    
    else
  }

}







usuario verifica_usuario(char *nick, usuario *raiz, usuario *ini, usuario *fim)
{
    if(raiz!=NULL)
    {

        int i =strcmp(nick,raiz.nickname);
        if(i==0)
        {
            return raiz;
        }

        else if(i<0)
        {
            if(raiz->pont[POST][ESQ]==NULL)
            {
                raiz[POST][ESQ]= verifica_exist(char *nick, raiz->pont[POST][ESQ]);
                return raiz[POST][ESQ];
            }
            else
                return verifica_exist(char *nick, raiz->pont[POST][ESQ]);

        }

        else
        {
            if(raiz->pont[POST][DIR]==NULL)
            {
                raiz[POST][DIR]= verifica_exist(char *nick, raiz->POST][DIR]);
                return raiz[POST][DIR];
            }
            else
                return verifica_exist(char *nick, raiz->POST][DIR]);

            }

    }



    else
    {
        usuario *novo;
        novo= malloc(sizeof(usuario));
        strcpy(novo.nickname,nick);
        novo->curtidas= 0;
        novo->retweets= 0;
        novo->mencoes= 0;
        novo->posts = 0;
        novo->influencia = 0;
        novo->tweets= NULL;

        if(fim!=NULL) // caso a lista não seja vazia
        {
	    usuario *aux;
            aux=fim;
	
	
	    while(aux.posts > novo.posts && aux!=ini)
            {
                aux=aux->pont[POST][ANT];
            }
		
            while(strcmp(novo.nickname,aux.nickname)<0 && aux.posts > novo.posts && aux!=ini)
            {
                aux=aux->pont[POST][ANT];
            }

            if(aux->pont[POST][PROX] == fim)
            {
                novo->pont[POST][ANT]=aux;
                novo->pont[POST][PROX]=aux->pont[POST][PROX];
                aux->pont[POST][PROX]=novo;
                fim=novo;
            }
            else if(aux->pont[POST][ANT] == ini &&  aux.posts >= novo.posts && strcmp(novo.nickname,aux.nickname)<0)
            {
                novo->pont[POST][ANT]= NULL;
                novo->pont[POST][PROX]= aux;
                aux->pont[POST][ANT]= novo;
                ini=novo;
            }
            else
            {
                usuario terceiro;
                terceiro = aux->pont[POST][PROX];


                aux->pont[POST][PROX] = novo;
                terceiro->pont[POST][ANT] = novo;

                novo->pont[POST][ANT]= aux;
                novo->pont[POST][PROX]= terceiro;
            }
        }
        else
        {
            novo->pont[POST][ANT]=NULL;
            novo->pont[POST][PROX]=NULL;
        }

        return novo;
    }

}
