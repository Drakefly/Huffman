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
