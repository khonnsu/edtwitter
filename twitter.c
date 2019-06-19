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
