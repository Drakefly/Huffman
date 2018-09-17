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

void add_nod(arbre a , nd nod){
    nd it=a->tete;


}

int main()
{

    printf("Hello world!\n");
    return 0;
}
