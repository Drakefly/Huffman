#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


typedef struct noeud* nd;
struct noeud{
    nd gauche;
    void *valeur; //TODO generique
    int type;//TODO
    nd droite;
};

int valeur_int(nd nd1){
    return (int*)nd1->valeur;
}

typedef struct arbre* arbre;
struct arbre{
    nd tete;
    int frequence;
};

typedef struct doublon * doublon;
struct doublon{
   char c;
   int occurance;
};

arbre creer_arbre(){
    arbre a = (arbre)malloc(sizeof(arbre));
    a->tete=NULL;
    a->frequence=0;
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

nd creer_noeud(void* _val, void(* _copier)(void*, void**), int type) {//Type 1 int type  Noeud
    nd n = (nd)malloc(sizeof(struct noeud));
    _copier(_val, &(n->valeur));
    n->gauche = NULL;
    n->droite = NULL;
    if(type==1);
    int *val= (int*)_val;
    printf("%d",*val);
    n->type=type;
    return n;
}

void affich (nd it){// Affiche un noeud, et ses fils
    if((it->type)==1){
        int _val=it->valeur;
        int *val= (int*)_val;
        printf("C'est une valeur %d",*val);
    }


    if((it->type)==0){
       int c = ((doublon)it->valeur)->c;
       char *ca = (char*)c;
       printf ("%c",*ca);

       // printf("c'est un doublon [,%c]",((doublon)it->valeur)->c);
    }
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
    arbre arbre1 = creer_arbre();
    doublon doublon1= creer_doublon('h');
    arbre1->tete=creer_noeud(&doublon1,&(_copier_doublons),0);
    affichage(arbre1);

    return 0;
}
