int learquivo(char *nome,usuario *raiz_u, usuario *ini_u, usuario *fim_u, hashtag *raiz_h, hashtag *ini_h, hashtag *fim_h){
  FILE *arq;
  
  arq=fopen(nome,"r");
  if(arq==null)
    return -1;
  else{
	usuario *user;
	hashtag *hash;
	tweet *t_lido;
	  
	char nick[16];
    	char texto_tweet[141];
    
    	while(!feof(arq)){
    		fscanf("%*c%[^;]s",nick);
    		user = verifica_usuario(nick);
    		if(user == NULL){
        		user=malloc(sizeof(user));
        		user->nickname = nick;
      		}
		t_lido=malloc(sizeof(tweet));
		fscanf("%[^#][^@][^;]s",t_lido->texto);		
		
		
		
		user=insere_tweet(tweet)
      
          
    	}
 
    
  }

}




usuario verifica_usuario(char *nick, usuario *raiz){
if(raiz!=NULL){
	
	
	if(strcmp(nick,raiz.nickname)==0){	
		return raiz;
	}
	
	else if(strcmp(nick,raiz.nickname)<0){
		return verifica_usuario(char *nick, raiz->esq){
	}
		
	else
	{
		return verifica_usuario(char *nick, raiz->dir){
	}
}
else
	return NULL; 
}

