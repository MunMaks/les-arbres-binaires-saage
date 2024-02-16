#include "../include/greffe.h"


int copie(Arbre *dest, Arbre source)
{
    if (!source) { *dest = NULL; return 1; }  /* Source est vide */

    *dest = alloue_noeud(source->val);

    if (*dest) { return 0; }  /* allocation mal passe */
      
    if (!copie(&((*dest)->left), source->left)) {
        liberer_arbre(dest); /* en cas d'échec */
        return 0;
    }

    // Copie récursive du sous-arbre droit
    if (!copie(&((*dest)->right), source->right)) {
        liberer_arbre(dest); /* en cas d'échec */
        return 0;
    }

    return 1;
}


int expansion(Arbre * A, Arbre B)
{
    /* TO DO */
}

