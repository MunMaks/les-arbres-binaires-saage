#include "../include/saage.h"


void affiche_tree(Arbre root)
{
    if (!root) { return; }

    printf(" %s \n", root->nom);
    affiche_tree(root->left);
    affiche_tree(root->right);
}


int main(int argc, char *argv[]){
    
    Arbre arbre = cree_A_3();
    if (!arbre) { 
        fprintf(stderr, "arbre in main n'existe pas\n");
        return 1; }
    
    //FILE *fptr_un = fopen()
    affiche_tree(arbre);

    liberer_arbre(&arbre);
    return 0;
}
