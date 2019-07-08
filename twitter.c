/*
usuario *P_U_AeL[4][3] = [0=post, 1=menc, 2=rts, 3=enga]	[0=ini, 1=fim, 2=raiz]
hashtag *P_H_AeL[3] = [0=ini, 1=fim, 2=raiz]
tweet *P_H_L[2] =  [0=ini, 1=fim]
*/

#include "twitter.h"

typedef usuario* USUARIO;
typedef hashtag* HASHTAG;
typedef tweet* TWEET;


/*
usuario *cria_user(char *nick, tweet *lido, int flag_menc, usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L);
usuario *verifica_usuario(char *nick,tweet *lido,int param,int outro,usuario *raiz, usuario *procurado,usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L);
usuario *insere_lista_u(usuario *novo,int param,usuario **P_U_AeL);
usuario *tira_lista(usuario *user,int param, usuario **P_U_AeL);
usuario *insere_pre_aux(usuario *user, usuario *aux,int param, usuario **P_U_AeL);
usuario *atualiza_arvore_u(usuario *filho,usuario *pai,int param,usuario **P_U_AeL);

hashtag *cria_hash(char *hash,hashtag **P_H_AeL);
hashtag *insere_lista_h(hashtag *novo,hashtag **P_H_AeL);
hashtag *tira_lista_h(hashtag *hash, hashtag **P_H_AeL);
hashtag *insere_pre_aux_h(hashtag *hash, hashtag *aux,hashtag **P_H_AeL);
hashtag *atualiza_arvore_h(hashtag *filho,hashtag *pai, hashtag **P_H_AeL);

tweet *insere_lista_t(tweet *novo, tweet **P_T_L);
tweet *insere_pre_aux_t(tweet *t, tweet *aux, tweet **P_T_L);


relacionadas *acha_rel(hashtag *procurada,  relacionadas **ponts,  relacionadas *raiz);
relacionadas *cria_r(hashtag *nova,relacionadas **P_R);
relacionadas *insere_lista_r(relacionadas *novo, relacionadas **P_R);
relacionadas *insere_pre_aux_r(relacionadas *novo, relacionadas *aux,relacionadas **P_R);
relacionadas *tira_lista_r(relacionadas *novo, relacionadas **P_R);
relacionadas *atualiza_arvore_r(relacionadas *filho,relacionadas *pai, relacionadas **P_L);


relacionadas* cadehashtag(char nome[], hashtag *raiz);
*/



int learquivo(FILE *arq,usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L)
{

    usuario *user;
    hashtag *hash;
    tweet *atual;
    l_hash *mesmo_T;

    char nick[16];
    char auxnick[16];
    char simbolo;
    int fimtexto = 0;
    char n_mencionado[16];
    char hashtag[140];

    while(!feof(arq))
    {
        atual=malloc(sizeof(tweet));

        fseek(arq, 1, SEEK_CUR);
        fscanf(arq,"%[^;]s",nick);
        fseek(arq, 1, SEEK_CUR);
        mesmo_T=NULL;
        do
        {
            fscanf(arq,"%[^;@#]s",atual->texto);
            fscanf(arq,"%c",&simbolo);
            switch(simbolo)
            {
            case '@':
                fscanf(arq,"%[^; ]s",n_mencionado);
                P_U_AeL[MENC*3+RAIZ] = verifica_usuario(n_mencionado,NULL,MENC, 0, P_U_AeL[MENC*3+RAIZ], NULL,*P_U_AeL,*P_H_AeL,*P_T_L);
                strcat(atual->texto,"@");
                strcat(atual->texto,auxnick);
                break;
            case '#':
                fscanf(arq,"%[^; ]s",hashtag);
                P_H_AeL[RAIZ] = verifica_hash(hashtag,mesmo_T,P_H_AeL[RAIZ],*P_H_AeL);
                strcat(atual->texto,"#");
                strcat(atual->texto,hashtag);
            case ';':
                fimtexto=1;
            }
        }
        while(!fimtexto);
        fseek(arq, 1, SEEK_CUR);
        fscanf(arq,"%d",&atual->retweets);
        fseek(arq, 1, SEEK_CUR);
        fscanf(arq,"%d",&atual->curtidas);
        fseek(arq, 1, SEEK_CUR);

        P_U_AeL[POST*3+RAIZ]= verifica_usuario(nick, atual, POST, 0, P_U_AeL[POST*3+RAIZ], NULL, *P_U_AeL, *P_H_AeL, *P_T_L);
        relaciona(mesmo_T);
        destroi(mesmo_T);

        insere_lista_t(atual, *P_T_L);
    }

}


usuario *verifica_usuario(char *nick,tweet *lido,int param,int outro,usuario *raiz, usuario *procurado,usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L)
{
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


                raiz->contador[POST]++; // incrementa contador de numero de posts

                raiz->curtidas += lido->curtidas;	// soma o numero de curtidas do novo tweet

                raiz->contador[RTS] += lido->retweets;	//soma o numero de rts do novo tweet

                raiz->contador[ENGA]= raiz->curtidas + raiz->contador[MENC] + raiz->contador[RTS];	// atualiza o engajamento


                atualiza_lista_u(raiz,POST,*P_U_AeL);
                atualiza_lista_u(raiz, RTS,*P_U_AeL);
                atualiza_lista_u(raiz, ENGA,*P_U_AeL);		//atualiza listas

                break;

            case MENC:
                raiz->contador[MENC]++; // incrementa contador de numero de MENÇÕES
                raiz->contador[ENGA]= raiz->curtidas + raiz->contador[MENC] + raiz->contador[RTS];	// atualiza o engajamento

                atualiza_lista_u(raiz, ENGA,*P_U_AeL);		//atualiza lista

                break;

            }


            return raiz;
        }

        else if(i<0)
        {
            usuario *temp = raiz->pont[param*4+ESQ];
            raiz->pont[param*4+ESQ]= verifica_usuario(nick, lido, param, outro, raiz->pont[param*4+ESQ], procurado,*P_U_AeL, *P_H_AeL, *P_T_L);
            if(temp!=raiz->pont[param*4+ESQ])
                raiz = atualiza_arvore_u(raiz->pont[param*4+ESQ],raiz, param, *P_U_AeL);
            return raiz;
        }
        else
        {
            usuario *temp = raiz->pont[param*4+DIR];

            raiz->pont[param*4+DIR]= verifica_usuario(nick,lido,param, outro, raiz->pont[param*4+DIR],procurado, *P_U_AeL, *P_H_AeL, *P_T_L);
            if(temp!=raiz->pont[param*4+DIR])
                raiz = atualiza_arvore_u(raiz->pont[param*4+DIR],raiz, param, *P_U_AeL);
            return raiz;
        }
    }

    else // não encontrou na arvore e achou ponto para incerção
    {
        if(!outro)
        {
            switch(param)
            {
            case POST:
                raiz = cria_user(nick, lido, 0, *P_U_AeL, *P_H_AeL, *P_T_L);
                P_U_AeL[MENC*3+RAIZ] = verifica_usuario(nick,lido,param, 1, P_U_AeL[MENC*3+RAIZ], raiz,*P_U_AeL, *P_H_AeL, *P_T_L);
                return raiz;
                break;

            case MENC:
                raiz = cria_user(nick, NULL, 1, *P_U_AeL, *P_H_AeL, *P_T_L);
                P_U_AeL[POST*3+RAIZ] = verifica_usuario(nick,lido,param, 1, P_U_AeL[POST*3+RAIZ], raiz,*P_U_AeL, *P_H_AeL, *P_T_L);
                return raiz;
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
    strcpy(novo->nickname,nick);

    *novo->pont = malloc(16*sizeof(usuario*));

    int i, j;

    for(i=0; i<4; i++)
    {
        novo->contador[i]=0;
        for(j=0; j<4; j++)
            novo->pont[i*4+j]=NULL;
    }

    if(flag_menc)
    {
        novo->contador[ENGA]= 1;
    }


    if(lido!=NULL)
    {
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





usuario *insere_lista_u(usuario *novo,int param,usuario **P_U_AeL)
{
    if(P_U_AeL[param*3+FIM]!=NULL) // caso a lista não seja vazia
    {
        usuario *aux;
        aux=P_U_AeL[param*3+FIM];

        while (aux!=NULL)	// encontra primeiro item da lista com numero >= de posts
        {
            if(aux->contador[param] >= novo->contador[param])
                break;
            aux=aux->pont[param*4+ANT];
        }

        while(aux!=NULL) // acha ordem alfabetica dentro entre os itens com o mesmo numero de acessos (aux sera anterior a novo)
        {
            if(strcmp(novo->nickname,aux->nickname)>= 0 && aux->contador[param] == novo->contador[param])
                break;
            aux=aux->pont[param*4+ANT];
        }

        novo= insere_pre_aux(novo, aux, param, *P_U_AeL);

    }
    else
    {
        novo->pont[param*4+ANT]=NULL;
        novo->pont[param*4+PROX]=NULL;
        P_U_AeL[param*3+INI]= novo;
        P_U_AeL[param*3+FIM]= novo;
    }

    return novo;

}


int atualiza_lista_u(usuario *user,int param,usuario **P_U_AeL)
{
    if(user!=P_U_AeL[param*3+INI])
    {
        usuario *aux;
        aux= user->pont[param*4+ANT];
        if(user->contador[param] > aux->contador[param])
        {

            while(aux!=NULL)
            {
                if(aux->contador[param] >= (user->contador[param]))
                    break;
                aux= aux->pont[param*4+ANT];
            }

            while(aux!=NULL)
            {
                if(strcmp(user->nickname,aux->nickname)>= 0 && aux->contador[param] == user->contador[param])
                    break;
                aux= aux->pont[param*4+ANT];
            }
            user= tira_lista(user, param, *P_U_AeL);
            user= insere_pre_aux(user, aux, param, *P_U_AeL);

            return 1;
        }
    }
    return 0;
}




usuario *tira_lista(usuario *user,int param, usuario **P_U_AeL)
{
    usuario *aux;
    aux=user->pont[param*4+ANT];

    if(user == P_U_AeL[param*3+FIM])
    {
        aux->pont[param*4+PROX] = NULL;
        P_U_AeL[param*3+FIM] = aux;

    }
    else
    {
        aux->pont[param*4+PROX]= user->pont[param*4+PROX];

        aux=user->pont[param*4+PROX];
        aux->pont[param*4+ANT]= user->pont[param*4+ANT];

    }

    user->pont[param*4+ANT]=NULL;
    user->pont[param*4+PROX]=NULL;
    return user;

}



usuario *insere_pre_aux(usuario *user, usuario *aux,int param, usuario **P_U_AeL)
{
    if(aux==NULL)
    {
        user->pont[param*4+PROX]=P_U_AeL[param*3+INI];
        P_U_AeL[param*3+INI]->pont[param*4+ANT]= user;
        P_U_AeL[param*3+INI]= user;
    }
    else
    {
        if(aux!=P_U_AeL[param*3+FIM])
        {
            usuario *terceiro;
            terceiro = aux->pont[param*4+PROX];

            aux->pont[param*4+PROX]= user;
            terceiro->pont[param*4+ANT]= user;

            user->pont[param*4+ANT]= aux;
            user->pont[param*4+PROX]= terceiro;
        }
        else
        {
            user->pont[param*4+ANT]=P_U_AeL[param*3+FIM];
            P_U_AeL[param*3+FIM]->pont[param*4+PROX]= user;
            P_U_AeL[param*3+FIM]= user;
        }
    }

    return user;
}




usuario *atualiza_arvore_u(usuario *filho,usuario *pai,int param,usuario **P_U_AeL)
{
    if(filho->contador[param] > pai->contador[param])
    {
        int j, k; //k=!j

        if(pai->pont[param*4+DIR] == filho)
        {
            j=DIR;
            k=ESQ;
        }
        else
        {
            j=ESQ;
            k=DIR;
        }

        pai->pont[param*4+j] = filho->pont[param*4+k];
        filho->pont[param*4+k] = pai;
        return filho;
    }
    else
        return pai;
}







hashtag *verifica_hashtag(char *hash, l_hash *mesmo_T, hashtag *raiz, hashtag **P_H_AeL)
{
    if(raiz!=NULL)
    {
        int i =strcmp(hash,raiz->nome);
        if(i==0)
        {
            raiz->usos++; // incrementa contador de usos da hashtag

            atualiza_lista_h(raiz,*P_H_AeL);	//atualiza lista

            l_hash *aux;
            aux= mesmo_T;
            while(aux->prox!=NULL)
                aux=aux->prox;
            aux->prox=malloc(sizeof(l_hash));
            aux=aux->prox;
            aux->dado= raiz;
            aux->prox= NULL;


            return raiz;
        }

        else if(i<0)
        {
            hashtag *temp = raiz->pont[ESQ];

            raiz->pont[ESQ] = verifica_hashtag(hash,mesmo_T, raiz->pont[ESQ], *P_H_AeL);
            if(temp!=raiz->pont[ESQ])
                raiz = atualiza_arvore_h(raiz->pont[ESQ], raiz, *P_H_AeL);
            return raiz;

        }
        else
        {
            hashtag *temp = raiz->pont[DIR];
            raiz->pont[DIR]= verifica_hashtag(hash,mesmo_T, raiz->pont[DIR], *P_H_AeL);
            if(temp!=raiz->pont[DIR])
                raiz = atualiza_arvore_h(raiz->pont[DIR], raiz, *P_H_AeL);
            return raiz;
        }
    }
    else // não encontrou na arvore e achou ponto para incerção
    {
        raiz= cria_hash(hash, *P_H_AeL);

        l_hash *aux;
        aux= mesmo_T;

        while(aux->prox!=NULL)
        aux=aux->prox;
        aux->prox=malloc(sizeof(l_hash));
        aux = aux->prox;
        aux->dado= raiz;
        aux->prox= NULL;


        return raiz;
    }
}




hashtag *cria_hash(char *hash,hashtag **P_H_AeL)
{
    hashtag *novo;
    novo= malloc(sizeof(hashtag));
    strcpy(novo->nome,hash);

    novo->usos= 1;

    novo = insere_lista_h(novo,P_H_AeL);

    *novo->associadas = malloc(3*sizeof(relacionadas));
    int i;
    for(i=0; i<3; i++)
        novo->associadas[i]=NULL;

    return novo;
}





hashtag *insere_lista_h(hashtag *novo,hashtag **P_H_AeL)
{
    if(P_H_AeL[FIM]!=NULL) // caso a lista não seja vazia
    {
        hashtag *aux;
        aux=P_H_AeL[FIM];

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
        P_H_AeL[INI]= novo;
        P_H_AeL[FIM]= novo;
    }

    return novo;

}


int atualiza_lista_h(hashtag *hash,hashtag **P_H_AeL)
{
    if(hash!=P_H_AeL[INI])
    {
        hashtag *aux;
        aux= hash->pont[ANT];
        if(hash->usos > aux->usos)
        {
            while(aux!=NULL)
            {
                if((aux->usos) >= (hash->usos))
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

    }
    return 0;
}

hashtag *tira_lista_h(hashtag *hash, hashtag **P_H_AeL)
{
    hashtag *aux;
    aux = hash->pont[ANT];
    if(hash == P_H_AeL[FIM])
    {
        aux->pont[PROX] = NULL;

        P_H_AeL[FIM] = hash->pont[ANT];
    }
    else
    {
        aux->pont[PROX]= hash->pont[PROX];

        aux = hash->pont[PROX];
        aux->pont[ANT]= hash->pont[ANT];
    }

    hash->pont[ANT]=NULL;
    hash->pont[PROX]=NULL;
    return hash;

}

hashtag *insere_pre_aux_h(hashtag *hash, hashtag *aux,hashtag **P_H_AeL)
{
    if(aux==NULL)
    {
        hash->pont[PROX]=P_H_AeL[INI];
        P_H_AeL[INI]->pont[ANT]= hash;
        P_H_AeL[INI]= hash;
    }
    else
    {
        if(aux!=P_H_AeL[FIM])
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
            hash->pont[ANT]=P_H_AeL[FIM];
            P_H_AeL[FIM]->pont[PROX]= hash;
            P_H_AeL[FIM]= hash;
        }
    }

    return hash;
}


hashtag *atualiza_arvore_h(hashtag *filho,hashtag *pai, hashtag **P_H_AeL)
{
    if(filho->usos > pai->usos)
    {
        int j, k;  //k=!j

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
        pai->pont[j] = filho->pont[k];
        filho->pont[k] = pai;
        return filho;
    }
    return pai;
}


tweet *insere_lista_t(tweet *novo, tweet **P_T_L)
{
    if(P_T_L[FIM]!=NULL) // caso a lista não seja vazia
    {
        tweet *aux;
        aux=P_T_L[FIM];
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
        P_T_L[INI]= novo;
        P_T_L[FIM]= novo;
    }

    return novo;

}

tweet *insere_pre_aux_t(tweet *t, tweet *aux, tweet **P_T_L)
{
    if(aux==NULL)
    {
        t->pont[PROX]=P_T_L[INI];
        P_T_L[INI]->pont[ANT]= t;
        P_T_L[INI]= t;
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
            t->pont[ANT]=P_T_L[FIM];
            P_T_L[FIM]->pont[PROX]= t;
            P_T_L[FIM]= t;
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

void ad_rel(hashtag *aux1, hashtag *aux2)
{
    if(aux1->associadas[RAIZ]==NULL)
    {
        *aux1->associadas = malloc(3* sizeof(relacionadas*));
        int i;
        for(i=0; i<3; i++)
            aux1->associadas[i]=NULL;


        aux1->associadas[RAIZ] = cria_r(aux2, aux1->associadas);

    }
    else
    {

        aux1->associadas[RAIZ] = acha_rel(aux2, aux1->associadas, aux1->associadas[RAIZ]);
    }

}

relacionadas *acha_rel(hashtag *procurada,  relacionadas **ponts,  relacionadas *raiz)
{
    if(raiz!=NULL)
    {
        hashtag *aux;
        aux= raiz->dado;
        int i = strcmp(procurada->nome,aux->nome);
        if(i==0)
        {
            raiz->encontros++; // incrementa contador de usos da hashtag

            atualiza_lista_r(raiz, *ponts);		//atualiza lista

            return raiz;
        }

        else if(i<0)
        {
            relacionadas *temp = raiz->pont[ESQ];

            raiz->pont[ESQ] = acha_rel(procurada, *ponts, raiz->pont[ESQ]);
            if(temp!=raiz->pont[ESQ])
                raiz = atualiza_arvore_r(raiz->pont[ESQ], raiz, *ponts);
            return raiz;

        }
        else
        {
            relacionadas *temp = raiz->pont[DIR];
            raiz->pont[DIR]= acha_rel(procurada,*ponts, raiz->pont[DIR]);
            if(temp!=raiz->pont[DIR])
                raiz = atualiza_arvore_r(raiz->pont[DIR], raiz, *ponts);
            return raiz;
        }
    }
    else // não encontrou na arvore e achou ponto para incerção
    {
        raiz= cria_r(procurada, *ponts);
        return raiz;

    }
}


relacionadas *cria_r(hashtag *nova,relacionadas **P_R)
{
    relacionadas *novo;
    novo= malloc(3*sizeof(relacionadas*));
    hashtag *aux;
    aux = novo->dado;
    strcpy(aux->nome,nova->nome);

    novo->encontros= 1;

    novo = insere_lista_r(novo,*P_R);

    return novo;
}


relacionadas *insere_lista_r(relacionadas *novo, relacionadas **P_R)
{
    if(P_R[FIM]!=NULL) // caso a lista não seja vazia
    {
        relacionadas *aux;
        hashtag *aux2, *aux3;
        aux=P_R[FIM];

        while(aux!=NULL)	// encontra primeiro item da lista com numero >= de posts
        {
            if((aux->encontros) >= (novo->encontros))
                break;
            aux=aux->pont[ANT];
        }

        while(aux!=NULL) // acha ordem alfabetica dentro entre os itens com o mesmo numero de acessos (aux sera anterior a novo)
        {
            aux2 = novo->dado;
            aux3 = aux->dado;

            if(strcmp(aux2->nome,aux3->nome)>= 0 && aux->encontros == novo->encontros)
                break;
            aux=aux->pont[ANT];
        }

        novo= insere_pre_aux_r(novo, aux, *P_R);

    }
    else
    {
        novo->pont[ANT]=NULL;
        novo->pont[PROX]=NULL;
        P_R[INI]= novo;
        P_R[FIM]= novo;
    }

    return novo;

}


relacionadas *insere_pre_aux_r(relacionadas *novo, relacionadas *aux,relacionadas **P_R)
{
    if(aux==NULL)
    {
        novo->pont[PROX]=P_R[INI];
        P_R[INI]->pont[ANT]= novo;
        P_R[INI]= novo;
    }
    else
    {
        if(aux!=P_R[FIM])
        {
            relacionadas *terceiro;
            terceiro = aux->pont[PROX];

            aux->pont[PROX]= novo;
            terceiro->pont[ANT]= novo;

            novo->pont[ANT]= aux;
            novo->pont[PROX]= terceiro;
        }
        else
        {
            novo->pont[ANT]=P_R[FIM];
            P_R[FIM]->pont[PROX]= novo;
            P_R[FIM]= novo;
        }
    }

    return novo;
}


int atualiza_lista_r(relacionadas *novo,hashtag **P_R)
{
    if(novo!=P_R[INI])
    {
        relacionadas *aux;
        aux= novo->pont[ANT];
        if(novo->encontros > aux->encontros)
        {
            while(aux!=NULL)
            {
                if((aux->encontros) >= (novo->encontros))
                    break;
                aux= aux->pont[ANT];
            }

            hashtag *aux2,*aux3;

            while(aux!=NULL)
            {
                aux2= novo->dado;
                aux3= aux->dado;
                if(strcmp(aux2->nome, aux3->nome)>= 0 && aux->encontros == novo->encontros)
                    break;
                aux= aux->pont[ANT];
            }

            novo= tira_lista_r(novo, *P_R);
            novo= insere_pre_aux_r(novo, aux, *P_R);

            return 1;
        }
    }
    return 0;
}


relacionadas *tira_lista_r(relacionadas *novo, relacionadas **P_R)
{
    relacionadas *aux;
    if(novo == P_R[FIM])
    {
        aux=novo->pont[ANT];
        aux->pont[PROX] = NULL;

        P_R[FIM] = novo->pont[ANT];
        novo->pont[ANT]= NULL;
    }
    else
    {
        aux=novo->pont[ANT];
        aux->pont[PROX]= novo->pont[PROX];

        aux = novo->pont[PROX];
        aux->pont[ANT]= novo->pont[ANT];

        novo->pont[ANT]=NULL;
        novo->pont[PROX]=NULL;
    }
    return novo;

}

relacionadas *atualiza_arvore_r(relacionadas *filho,relacionadas *pai, relacionadas **P_L)
{
    if(filho->encontros > pai->encontros)
    {
        int j, k;    //k=!j

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

        pai->pont[j] = filho->pont[k];
        filho->pont[k] = pai;

        return filho;
    }
    return pai;
}


void leparametros(FILE *arquivo, ops *op) 	//recebe ponteiro para estrutura com operacoes
{
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

void escrevearquivo(FILE *arq, usuario **P_U_AeL, hashtag **P_H_AeL, tweet **P_T_L, ops op, clock_t comeco)
{
    clock_t fim;
    float tempo;
    int cont;

    fprintf(arq,"--- OP A\n");
    cont=0;
    hashtag *aux_hash = P_H_AeL[INI];
    if(op.a == 0)
    {
        while(aux_hash!=NULL)
        {
            fprintf(arq,"#%s, %d\n", aux_hash->nome, aux_hash->usos);
            aux_hash=aux_hash->pont[PROX];
        }
    }
    else
    {
        while(cont<op.a&&aux_hash!=NULL)
        {
            fprintf(arq,"#%s, %d\n", aux_hash->nome, aux_hash->usos);
            aux_hash=aux_hash->pont[PROX];
            cont++;
        }
    }
    fprintf(arq,"--- OP B\n");
    cont=0;
    usuario *aux_user = P_U_AeL[POST*3+INI];
    if(op.b == 0)
    {
        while(aux_user!=NULL)
        {
            fprintf(arq,"@%s, %d\n", aux_user->nickname, aux_user->contador[POST]);
            aux_user=aux_user->pont[POST*4+PROX];
        }
    }
    else
    {
        while(cont<op.b&&aux_user!=NULL)
        {
            fprintf(arq,"@%s, %d\n", aux_user->nickname, aux_user->contador[POST]);
            aux_user=aux_user->pont[POST*4+PROX];
            cont++;
        }
    }
    fprintf(arq,"--- OP C\n");
    cont = 0;
    tweet *aux_tweet = P_T_L[INI];
    if(op.c == 0)
    {
        while(aux_tweet!=NULL)
        {
            fprintf(arq,"%s, %d\n", aux_tweet->texto, aux_tweet->curtidas);
            aux_tweet=aux_tweet->pont[0];
        }
    }
    else
    {
        while(cont<op.c&&aux_tweet!=NULL)
        {
            fprintf(arq,"%s, %d\n", aux_tweet->texto, aux_tweet->curtidas);
            aux_tweet=aux_tweet->pont[0];
            cont++;
        }
    }
    fprintf(arq,"--- OP D\n");
    cont = 0;
    aux_user = P_U_AeL[MENC*3+INI];
    if(op.d == 0)
    {
        while(aux_user!=NULL)
        {
            fprintf(arq,"@%s, %d\n", aux_user->nickname, aux_user->contador[MENC]);
            aux_user=aux_user->pont[MENC*4+PROX];
        }
    }
    else
    {
        while(cont<op.d&&aux_user!=NULL)
        {
            fprintf(arq,"@%s, %d\n", aux_user->nickname, aux_user->contador[MENC]);
            aux_user=aux_user->pont[MENC*4+PROX];
            cont++;
        }
    }
    fprintf(arq,"--- OP E\n");
    cont = 0;
    aux_user = P_U_AeL[RTS*3+INI];
    if(op.e == 0)
    {
        while(aux_user!=NULL)
        {
            fprintf(arq,"@%s, %d\n", aux_user->nickname, aux_user->contador[RTS]);
            aux_user=aux_user->pont[RTS*4+PROX];
        }
    }
    else
    {
        while(cont<op.e&&aux_user!=NULL)
        {
            fprintf(arq,"@%s, %d\n", aux_user->nickname, aux_user->contador[RTS]);
            aux_user=aux_user->pont[RTS*4+PROX];
            cont++;
        }
    }
    fprinf(arq,"--- OP F\n");
    cont=0;
    aux_user = P_U_AeL[MENC*3+INI];
    if(op.f == 0)
    {
        while(aux_user!=NULL)
        {
            fprintf(arq,"@%s, %d\n", aux_user->nickname, aux_user->contador[MENC]);
            aux_user=aux_user->pont[MENC*4+PROX];
        }
    }
    else
    {
        while(cont<op.f&&aux_user!=NULL)
        {
            fprintf(arq,"@%s, %d\n", aux_user->nickname, aux_user->contador[MENC]);
            aux_user=aux_user->pont[MENC*4+PROX];
            cont++;
        }
    }
    fprinf(arq,"--- OP G\n");
    cont=0;
    relacionadas *aux_rel = cadehashtag(op.hash, P_H_AeL[RAIZ]);
    if(aux_rel==NULL)
    {
        fprintf(arq,"Hashtag nao encontrada.\n");
    }
    else
    {
        hashtag *aux;
        if(op.g == 0)
        {
            while(aux_user!=NULL)
            {
                aux = aux_rel->dado;
                fprintf(arq,"#%s, %d\n", aux->nome, aux_rel->encontros);
                aux_rel=aux_rel->pont[PROX];
            }
        }
        else
        {
            while(cont<op.g&&aux_user!=NULL)
            {
                aux = aux_rel->dado;
                fprintf(arq,"#%s, %d\n", aux->nome, aux_rel->encontros);
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

relacionadas* cadehashtag(char nome[], hashtag *raiz)
{
    if(raiz==NULL)
        return NULL;

    hashtag *aux_hash = raiz;
    int i;
    i=strcmp(nome,aux_hash->nome);
    if(i==0)
        return aux_hash->associadas;
    else if(i<0)
        return cadehashtag(nome,aux_hash->pont[ESQ]);
    else if(i>0)
        return cadehashtag(nome,aux_hash->pont[DIR]);

}

usuario *cria_u(usuario **P_U_AeL)
{
    int i, j;
    *P_U_AeL=malloc(12*sizeof(usuario*));
    for(i=0; i<3; i++)
        for(j=0; j<4; j++)
            P_U_AeL[j*3+i]=NULL;

    return *P_U_AeL;
}

hashtag *cria_h (hashtag **P_H_AeL)
{
    int i;
    *P_H_AeL=malloc(3*sizeof(hashtag*));
    for(i=0; i<3; i++)
        P_H_AeL[i]=NULL;

    return *P_H_AeL;

}

tweet *cria_t (tweet **P_T_L)
{
    int i;
    *P_T_L=malloc(3*sizeof(tweet*));
    for(i=0; i<3; i++)
        P_T_L[i]=NULL;

    return *P_T_L;
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
    while(lixo[POST*3+INI]!=NULL)
    {
        aux= lixo[POST*3+INI];
        lixo[POST*3+INI] = lixo[POST*3+INI]->pont[PROX];
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
    while(lixo[INI]!=NULL)
    {
        aux= lixo[INI];
        lixo[INI] = lixo[INI]->pont[PROX];
        destroi_t_pont(aux->pont);
        free(aux);
    }
}


void destroi_t_pont(tweet **lixo)
{
    tweet *aux;
    int i;
    for(i=0; i<4; i++)
    {
        aux= lixo[i];
        free(aux);
    }
}


void destroi_h(hashtag **lixo)
{
    hashtag *aux;
    while(lixo[INI]!=NULL)
    {
        aux= lixo[INI];
        lixo[INI] = lixo[INI]->pont[PROX];
        destroi_r(aux->associadas);
        free(aux);
    }
}


void destroi_r(relacionadas **lixo)
{
    relacionadas *aux;
    while(lixo[INI]!=NULL)
    {
        aux= lixo[INI];
        lixo[INI] = aux->pont[PROX];
        free(aux);
    }
}

void destroi(l_hash **lixo)
{
    l_hash *aux;
    while(lixo[INI]!=NULL)
    {
        aux= lixo[INI];
        lixo[INI] = aux->prox;
        free(aux);
    }
}


