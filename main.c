#include <stdio.h>
#include <stdlib.h>


typedef struct noeud* nd;
struct noeud{
    nd gauche;
    void* valeur;
    nd droite;
};

typedef struct arbre* arbre;
struct arbre{
    nd tete;
};

arbre creer_arbre(){
    arbre a = (arbre)malloc(sizeof(arbre));
    return a;
}

void switch_val(){

}

int estVide (arbre a){
    return a->tete==NULL;
}

void add_nod(arbre a , nd nod ,int(compare)(void*,void*)){
    nd it=a->tete;
    int done=0;
    if(estVide(a)){
       a->tete=nod;
    }else{
        while(done==0){
            if(compare(it,nod)==1){
                if(it->gauche==NULL){
                        it->gauche=nod;
                        done=1;
                }else{
                    it=it->gauche;
                }


            }if(compare(it,nod)==-1){
                if(it->droite==NULL){
                        it->droite=nod;
                        done=1;
                }else{
                    it=it->droite;
                }
            }else{
                printf("dude what");
                done=1;//break??????????????????????????????????????????????
            }

        }
    }



}

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
void liberer(void** val){
    free(*val);
    *val=NULL;
}

int compare(void* a , void* b){
    if(a->valeur>b->valeur)return 1;
    if(a->valeur<b->valeur)return -1;
    if(a->valeur==b->valeur)return 0;
}


int main()
{

    printf("Hello world!\n");
    return 0;
}
