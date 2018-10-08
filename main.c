#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


typedef struct noeud* nd;
struct noeud{
    nd gauche;
    int *valeur; //TODO generique
    nd droite;
};

typedef struct arbre* arbre;
struct arbre{
    nd tete;
};

typedef struct doublon * doublon;
struct doublon{
   char c;
   int occurance;
};

void _liberer_noeud(nd *val){
    free((*(val))->droite);
    free((*(val))->gauche);
    free((*(val))->valeur);
    *val=NULL;
}

arbre creer_arbre(){
    arbre a = (arbre)malloc(sizeof(arbre));
    a->tete=NULL;
    return a;
}

int est_vide(arbre a){
    return a->tete==NULL;
}

void _copier_int(void* _val, void** ptr) {
    *ptr = (int*)malloc(sizeof(int));
    memcpy(*ptr,_val,sizeof(int));
}

void _copier_doublons(void* _val, void** ptr){
    *ptr = (doublon )malloc(sizeof(doublon));
    memcpy(*ptr,_val,sizeof(doublon));
}

doublon creer_doublon(char c){
    doublon d = malloc(sizeof(doublon));
    d->c=c;
    d->occurance=1;
    return d;
}

void incrementer_doublon(doublon *doublon1){
    (*doublon1)->occurance++;
}

nd creer_noeud(void* _val, void(* _copier)(void*, void**)) {
    nd n = (nd)malloc(sizeof(struct noeud));
    _copier(_val, &(n->valeur));
    n->gauche = NULL;
    n->droite = NULL;
    return n;
}

void add_noeud(arbre a, nd nod, int(compare)(void *, void *)){
    nd it=a->tete;
    if(est_vide(a)){
       a->tete=nod;
    }else{
        while (1){
            int i = compare(it,nod);
             if(i>0){//C'est plus grand
                 if(it->gauche==NULL){
                        it->gauche=nod;
                    return;
                }else{
                    it=it->gauche;
                }
            }
            if(i<0){//C'est plus petit
                if(it->droite==NULL){
                    it->droite=nod;
                    return;
                }else{
                    it=it->droite;
                }
            }
            if(i==0){//C'est egal
                printf("Ca y est deja, je ne fait rien");
                return;
            }
        }
    }

}
/**
void supprimer (arbre a , void* n){
    if(a->tete!=NULL){
        int done =0;
        nd it=a->tete;
        nd leitdavant;
        //int side=compare(it,nod);
        while(done==0){
            if(compare(it,nod)==1){
                    if(it->gauche!=NULL){
                        leitdavant=it;
                        it=it->gauche;

                    }else{
                        printf("not found");
                        done=1;
                    }
            }else if(compare(it,nod)==-1){
                    if(it->droite!=NULL){
                        leitdavant=it;
                        it=it->droite;
                    }else{
                        printf("not found");
                        done=1;
                    }

            }else{
                if((it->gauche==NULL)&&(it->droite==NULL)){
                    free(it->valeur);
                    free(*it);
                    it=NULL;
                }else if(it->gauche!=NULL&&it->droite==NULL){
                    while(it->droite!=NULL){
                        it=it->droite;
                    }
                    leitdavant->valeur=it->valeur;
                    //monter le fils du cote opposé à la place du pere et monter la valeur du pere sur leitdavant
                    //leitdavant->gauche=it->gauche;
                    free(it->valeur);
                    free(*it);
                    it=NULL;
                }else if(it->gauche==NULL&&it->droite!=NULL){
                    while(it->gauche!=NULL){
                        it=it->gauche;
                    }
                    leitdavant->valeur=it->valeur;
                    free(it->valeur);
                    free(*it);
                    it=NULL;
                }else{

                }
                done=1;//break??????????????????????????????????????????????
            }



    }
}

*/

int compare(void* a , void* b){//Renvoie 1 si a>b, Renvoie -1 si a<b 0 sinon
    //TODO les free
    struct noeud nda = *((nd)a);
    int vala = *nda.valeur;

    struct noeud ndb = *((nd)b);
    int valb = *ndb.valeur;
    if(vala<valb)return 1;
    if(vala>valb)return -1;
    return 0;
}
/*void supprimer (arbre a , void* n) {

    printf("coucou batard ici c'est le supprimer");

    if (a->tete != NULL) {
        int done = 0;
        nd it = a->tete;
        nd leitdavant;
        //int side=compare(it,nod);
        while (done == 0) {
            if (compare(it->valeur, n) == 1) {
                if (it->gauche != NULL) {
                    leitdavant = it;
                    it = it->gauche;

                } else {
                    printf("not found");
                    done = 1;
                }
            } else if (compare(it->valeur, n) == -1) {
                if (it->droite != NULL) {
                    leitdavant = it;
                    it = it->droite;
                } else {
                    printf("not found");
                    done = 1;
                }

            } else {
                if ((it->gauche == NULL) && (it->droite == NULL)) {
                    free(it->valeur);
                    //free(*it);
                    it = NULL;
                } else if (it->gauche != NULL && it->droite == NULL) {
                    while (it->droite != NULL) {
                        it = it->droite;
                    }
                    leitdavant->valeur = it->valeur;
                    nd asuppr = it->gauche;
                    (*it) = (*it->gauche);
                    //monter le fils du cote oppos� � la place du pere et monter la valeur du pere sur leitdavant
                    //leitdavant->gauche=it->gauche;
                    free(asuppr);
                    //free(*it);
                    asuppr = NULL;
                } else //if(it->gauche==NULL&&it->droite!=NULL)
                {
                    while (it->gauche != NULL) {
                        it = it->gauche;
                    }
                    leitdavant->valeur = it->valeur;
                    nd asuppr = it->droite;
                    (*it) = (*it->droite);
                    free(asuppr);
                    //free(*it);
                    it = NULL;
                    done = 1;//break??????????????????????????????????????????????
                    printf("la on sort du supprimer");
                }
            }
        }
    }
}*///Supression

void affich (nd it){// Affiche un noeud, et ses fils
    printf("%d",(*it->valeur));
    printf("{");
    if (it->gauche!=NULL)affich(it->gauche);
    printf(",");
    if (it->droite!=NULL)affich(it->droite);
    printf("}");
}

void affichage (arbre a){//Affiche un arbre
    if(a->tete!=NULL){
        nd it = a->tete;
        affich (it);
    }else{
        printf("Vide");
    }
}

int main() {
    int a =5;
    int b =3;
    int c = 88;
    int d = 12;
    nd nd1= creer_noeud(&a,&_copier_int);
    nd nd2= creer_noeud(&b,&_copier_int);
    nd nd3= creer_noeud(&c,&_copier_int);
    nd nd4= creer_noeud(&d,&_copier_int);
    arbre arbre1 = creer_arbre();
    add_noeud(arbre1, nd1, compare);
    add_noeud(arbre1, nd2, compare);
    add_noeud(arbre1, nd3, compare);
    add_noeud(arbre1, nd4, compare);
    affichage(arbre1);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//PART 2
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>


typedef struct noeud* nd;
struct noeud{
    nd gauche;
    void* valeur; //TODO generique
    nd droite;
};

typedef struct arbre* arbre;
struct arbre{
    nd tete;
};

void _liberer_noeud(nd *val){
    free((*(val))->droite);
    free((*(val))->gauche);
    free((*(val))->valeur);
    *val=NULL;
}
arbre creer_arbre(){
    arbre a = (arbre)malloc(sizeof(arbre));
    a->tete=NULL;
    return a;
}

int estVide (arbre a){
    return a->tete==NULL;
}

void _copier_int(void* _val, void** ptr) {
    *ptr = (int*)malloc(sizeof(int));
    memcpy(*ptr,_val,sizeof(int));
}

nd creer_noeud(void* _val, void(* _copier)(void*, void**)) {
    nd n = (nd)malloc(sizeof(struct noeud));
    _copier(_val, &(n->valeur));
    n->gauche = NULL;
    n->droite = NULL;
    return n;
}

void add_noeud(arbre a, nd nod, int(compare)(void *, void *)){
    nd it=a->tete;
    if(estVide(a)){
       a->tete=nod;
    }else{
        while (1){
            int i = compare(it,nod);
            //printf("%d",i);
             if(i>0){//C'est plus grand
                 if(it->gauche==NULL){
                        it->gauche=nod;
                    return;
                }else{
                    it=it->gauche;
                }
            }
            if(i<0){//C'est plus petit
                if(it->droite==NULL){
                    it->droite=nod;
                    return;
                }else{
                    it=it->droite;
                }
            }
            if(i==0){//C'est egal
                printf("Ca y est deja, je ne fait rien");
                return;
            }
        }
    }

}


int compare(void* a , void* b){//Renvoie 1 si a>b, Renvoie -1 si a<b 0 sinon
    //TODO les free
    struct noeud nda = *((nd)a);
    int vala = *nda.valeur;

    struct noeud ndb = *((nd)b);
    int valb = *ndb.valeur;
    if(vala<valb)return 1;
    if(vala>valb)return -1;
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


nd chercher (arbre a, int osef){
    printf("\nJe cherche");
    if(estVide(a))return NULL;
    printf("je cherche toujours");
    nd it = a->tete;
    while((*(it->valeur)!=osef)&&(it!=NULL)){
        printf("\nwhile");

        /////////////////////////////////////COMPAAAAAAAAAAAAAAAAAAAARE !!!!!!!!!!!!!
        if(*(it->valeur)>osef){
            printf("\ngnagnagna inferieur");
            if (it-> gauche!=NULL)it=it->gauche;
            else it=NULL;
        }else{
            printf("\ngnegnegne supperieur");
            if(it->droite!=NULL)it=it->droite;
            else it=NULL;
            printf("je suis dans %d",(*it->valeur));
        }
    }
    printf("\nj'ai fini e chercher");
    return it;////////////&&&&&&&&&&&&&&&&&&&&&&&????????

}

void supprimer (arbre a , void* n) {

    printf("coucou batard ici c'est le supprimer");

    if (a->tete != NULL) {
        int done = 0;
        nd it = a->tete;
        nd leitdavant;
        //int side=compare(it,nod);
        while (done == 0) {
            if (compare(it->valeur, n) == 1) {
                if (it->gauche != NULL) {
                    leitdavant = it;
                    it = it->gauche;

                } else {
                    printf("not found");
                    done = 1;
                }
            } else if (compare(it->valeur, n) == -1) {
                if (it->droite != NULL) {
                    leitdavant = it;
                    it = it->droite;
                } else {
                    printf("not found");
                    done = 1;
                }

            } else {
                if ((it->gauche == NULL) && (it->droite == NULL)) {
                    free(it->valeur);
                    //free(*it);
                    it = NULL;
                } else if (it->gauche != NULL && it->droite == NULL) {
                    while (it->droite != NULL) {
                        it = it->droite;
                    }
                    leitdavant->valeur = it->valeur;
                    nd asuppr = it->gauche;
                    (*it) = (*it->gauche);
                    //monter le fils du cote oppos? ? la place du pere et monter la valeur du pere sur leitdavant
                    //leitdavant->gauche=it->gauche;
                    free(asuppr);
                    //free(*it);
                    asuppr = NULL;
                } else //if(it->gauche==NULL&&it->droite!=NULL)
                {
                    while (it->gauche != NULL) {
                        it = it->gauche;
                    }
                    leitdavant->valeur = it->valeur;
                    nd asuppr = it->droite;
                    (*it) = (*it->droite);
                    free(asuppr);
                    //free(*it);
                    it = NULL;
                    done = 1;//break??????????????????????????????????????????????
                    printf("la on sort du supprimer");
                }
            }
        }
    }
}

    void destruct (nd it){

        if (it->droite!=NULL) destruct(it->droite);
        if (it->gauche!=NULL) destruct(it->gauche);
        _liberer_noeud(&it);
        //free(it);
        //it=NULL;
    }

    void destruction(arbre* a){
        nd it =(*a)->tete;
        destruct (it);
        //*a->tete=(nd)NULL;
    }

    void affich (nd it){

        printf("\t%d",(*it->valeur));
        printf("\n");
        if (it->gauche!=NULL)affich(it->gauche);
        if (it->droite!=NULL)affich(it->droite);
    }

    void affichage (arbre a){
        if(a->tete!=NULL){
            nd it = a->tete;
            affich (it);
        }else printf("NULL");
    }

    typedef struct doublon* doublon;
    struct doublon{
        int occurance;
        char c;
    };

    typedef struct noeudarbre* noeudarbre;
    struct noeudarbre{
        arbre a;
        //doublon d;
        noeudarbre suivant;
        noeudarbre precedent;
    };

    typedef struct listearbre* listearbre;
    struct listearbre{
        noeudarbre tete;
        noeudarbre queue;
    };

    doublon creer_doublon (char car){
        doublon n = (doublon)malloc(sizeof(doublon));
        n->c=(char)malloc(sizeof(char));
        n->c=car;
        n->occurance=1;
        return n;
    }

    noeudarbre creer_noeudarbre(char car ,noeudarbre prec){
        noeudarbre ndbr=(noeudarbre)malloc(sizeof(noeudarbre));

        doublon dbln=creer_doublon(car);
        ndbr->a->tete=dbln;
        ndbr->suivant=NULL;
        ndbr->precedent=prec;

        return ndbr;

    }

    listearbre creer_listearbre(){
        listearbre l = (listearbre)malloc(sizeof(listearbre));
        return l;
    }

    void lire_string (listearbre* l ,char* str){
        int i = 0 ;
        noeudarbre t=(*l)->tete;
        noeudarbre it=t;
        //noeudarbre tprec=l->suivant;
        if (t==NULL){
            t->a=creer_arbre();
            t->a->tete=creer_doublon(str[i]);
            i++;
        }
        while (strcomp(str[i],"")==0){//TODO retrouver le dernier char d'un fichier
            do{
                if(strcomp(it->a->tete->valeur->c,str[i])==0){
                    it->a->tete->valeur->occurance++;
                    while(it->precedent->a->tete->valeur->occurance<it->a->tete->valeur->occurance){
                        //TODO switch

                    }
                }

                i++;
            }while(it->suivant!=NULL);
        }
    }

    void switchpos (arbre a , noeudarbre/*void**/ neud){
        noeudarbre prec= &(neud->precedent);
        noeudarbre suiv= &(neud->suivant);



    }

    arbre fusion(arbre un, arbre deux){
        arbre a = creer_arbre();
        switch(un->tete->type,deux->tete->type)
        case (/*deux doublons*/){
            if(un->tete->valeur->occurence>deux->tete->valeur->occurence){
                a->tete->droite->valeur=un;
                a->tete->gauche->valeur=deux;
            }else if(un->tete->valeur->occurence<deux->tete->valeur->occurence){
                a->tete->gauche->valeur=un;
                a->tete->droite->valeur=deux;
            }else{
                //TODO modifier une occurence en cas d'egalite
                if(un->tete->valeur->c>deux->tete->valeur->c){
                    a->tete->droite->valeur=un;
                    a->tete->gauche->valeur=deux;
                }else{
                    a->tete->gauche->valeur=un;
                    a->tete->droite->valeur=deux;
                }
            }
        break;
        }
        case(/*deux arbres*/){/*
            if(un->tete->valeur->occurence>deux->tete->valeur->occurence){
                a->tete->droite->valeur=un;
                a->tete->gauche->valeur=deux;
            }else if(un->tete->valeur->occurence<deux->tete->valeur->occurence){
                a->tete->gauche->valeur=un;
                a->tete->droite->valeur=deux;*/
            }
        return a;
        }



    arbre fusioner(listearbre lista){
        while(&(lista->queue)!=&(lista->tete)){
            arbre a =fusion(lista->queue,lista->queue->precedent);
            inserer (lista ,a);
        }
    }

    //lire à l'aide d'une suite de 1 et de 0 l'abre pour décoder
    char* decoder(char* listeunzeros, arbre a){
        int i = 0;
        it=a->tete;
        char* aretourner = "";
        if(it!=NULL){
            while(char[i]!="\0"){
                if (char[i]=="0"){
                    if(a->gauche->gauche!=NULL){//} || a->gauche->droite!=NULL){
                        it=it->gauche
                    }else{
                        strcat(aretourner,it->valeur->c);
                        it=a->tete;
                    }
                }else{
                    if(a->droite->droite!=NULL){//} || a->droite->gauche!=NULL){
                        it=it->droite
                    }else{
                        strcat(aretourner,it->valeur->c);
                        it=a->tete;
                    }
                }
                i++;
            }
        }
        return aretourner;

    }

    /*
    codage parcours -> tableau
    decodage parcours arbre
    binaire -> int
    int->binaire
    */

    int binarytoint(char* bin){
        int somme=0;
        int degre=strlen(bin)-1;
        while(degre>=0){
            if(atoi(char(bin[degre]))==1){
                    somme=somme+pow(2,degre);
            }
            degre--;
        }
        return somme;
    }

    char* inttobinary(int i){
        int degre=0;
        char* bin=(char*)malloc(sizeof(char*));
        while (i>pow(2,degre)){
            degre++;
        }
        while(i!=0){
            if (pow(2,degre)>i){
                degre--;
                strcat(bin,"0");
            }else{
                strcat(bin,"1");
                i=i-pow(2,degre);
                degre--;
            }
        }
        return bin;
    }
//TODO TODO DO TODODODO !
    //arbre->tableaur
    char* tableau (arbre a){
        char* arb =(char*)malloc(char*);
        arbre it = a->tete;
        char* str="";
        //condition de parcours de l'arbre
            arb[i]=it->c;
            arb[i+1]=it->
    }




int main() {




    FILE* fichier=NULL;
    fichier = fopen("test.txt","r");
    char* str=(char*)malloc(250*sizeof(char));
    fgets(str,250,fichier);

    printf("%s\n",str);
    fclose(fichier);
//test listearbre
    listearbre l =creer_listearbre();
    char* s="abcdefgeggfad";
    lire_string(l,s);



    int a =5;
    int b =3;
    int c = 88;
    int d = 12;
    nd nd1= creer_noeud(&a,&_copier_int);
    nd nd2= creer_noeud(&b,&_copier_int);
    nd nd3= creer_noeud(&c,&_copier_int);
    nd nd4= creer_noeud(&d,&_copier_int);
    arbre arbre1 = creer_arbre();
    add_noeud(arbre1, nd1, compare);
    add_noeud(arbre1, nd2, compare);
    add_noeud(arbre1, nd3, compare);
    add_noeud(arbre1, nd4, compare);
    /*nd n=chercher(arbre1,12);
    if (n==NULL){
        printf("n'est pas dans l'arbre");
    } else{
        printf("Clairement y'a un souci");
    }
    n=chercher(arbre1,88);
    printf(" a été trouvé");*/
    printf("affichage");
    affichage(arbre1);
    //printf("%d\n",*(arbre1->tete->droite->valeur));
    //printf("%d\n",compare(nd1,nd2));
    printf("supprimons 3");
    int i =3;
    int* j=&i;
    supprimer(arbre1,j);
    affichage(arbre1);
    destruction(&arbre1);
    if (arbre1->tete==NULL)printf("c'est null");
    if (arbre1->tete->gauche==NULL)printf("c'est null a gauche");
    if (arbre1->tete->droite==NULL)printf("c'est null a droite");
    //affichage(arbre1);

    return 0;
}
