int learquivo(char *nome,usuario *raiz_u, usuario *ini_u, usuario *fim_u, hashtag *raiz_h, hashtag *ini_h, hashtag *fim_h){

  FILE *arq;
  char temp[16];
  
  arq=fopen(nome,"r");
  if(arq==null)
    return -1;
  else
  {
    while(!feof(arq))
    {
      atual=malloc(sizeof(tweet));
      scanf("%[^;]s",temp);
    }
    if(verifica_existencia(temp))
    {
    
    }
  }

}
