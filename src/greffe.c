#include "../include/greffe.h"


int copie(Arbre *dest, Arbre source)
{
    if (!source) { *dest = NULL; return 1; }  /* source est vide */

    *dest = alloue(source->nom);

    if (*dest) { return 0; }  /* allocation mal passe */
      
    if (! copie(&(*dest)->left, source->left) ) {
        liberer_arbre(dest);
        return 0;
    }

    // Copie récursive du sous-arbre droit
    if (! copie(&(*dest)->right, source->right) ) {
        liberer_arbre(dest);
        return 0;
    }

    return 1;
}



int expansion(Arbre *A, Arbre B)
{
    /* TO DO */
    return 0;
}

