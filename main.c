#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


typedef struct noeud* nd;
struct noeud{
    nd gauche;
    int *valeur;
    nd droite;
};

typedef struct arbre* arbre;
struct arbre{
    nd tete;
};

arbre creer_arbre(){
    arbre a = (arbre)malloc(sizeof(arbre));
    a->tete=NULL;
    return a;
}

void switch_val(){
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



void add_nod(arbre a , nd nod ,int(compare)(void*,void*)){
    nd it=a->tete;
    int done=0;
    if(estVide(a)){
       a->tete=nod;
    }else{
        while (1){
            printf("J'essaye de rajouter %d \n", *(nod->valeur));
            int i = compare(it,nod);
            printf("%d",i);
             if(i>0){//C'est plus grand
                if(it->gauche==NULL){
                        it->gauche=nod;
                    return;
                }else{
                    it=it->gauche;
                }
            }
            if(i<0){//C'est plus petit
                printf("J'ai detecte que c'etais plus petit");
                if(it->droite==NULL){
                    printf("ouiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii");

                    it->droite=nod;
                    return;
                }else{
                    it=it->droite;
                }
            }
            if(i==0){//C'est egal
                printf("dude what?");
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
void liberer(void** val){
    free(*val);
    *val=NULL;
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


int main() {
    int a =5;
    int b =3;
    nd nd1= creer_noeud(&a,&_copier_int);
    nd nd2= creer_noeud(&b,&_copier_int);
    arbre arbre1 = creer_arbre();
    //add_nod(arbre1,nd1,compare);
    //add_nod(arbre1,nd2,compare);
    printf("%d", *nd1->valeur);
    //printf("%d\n",*(arbre1->tete->valeur));
    //printf("%d\n",compare(nd1,nd2));
    return 0;
}
