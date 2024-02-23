#include "../include/greffe.h"


/* fonction renvoie la copie de l'arbre source */
uint copie(Arbre *dest, Arbre source)
{
    
    if (!source) { *dest = NULL; return 1; }

    
    if ( !(*dest = alloue(source->nom)) ) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la copie de l'arbre.\n");
        return 0;
    }


    if ( !(copie(&((*dest)->left), source->left)) ) { return 0; }

    if ( !(copie(&((*dest)->right), source->right)) ) { return 0; }

    return 1;
}



/* Cette fonction ajoute left et right pour chaque feuilles de l'arbre */
void ajoute_sous_arbres(Arbre *arbre, Noeud *left, Noeud *right)
{
    Arbre left_copie = NULL, right_copie = NULL;

    if (!*arbre) { return; }

    if ((*arbre)->left) { ajoute_sous_arbres(&((*arbre)->left), left, right); }     /* si sous arbre gauche existe */

    if ((*arbre)->right) { ajoute_sous_arbres(&((*arbre)->right), left, right); }   /* si sous arbre droite existe */


    /* inserer les sous arbres */
    if ( !((*arbre)->left) ) { 
        if ( copie(&left_copie, left) ) { (*arbre)->left = left_copie; }
    }

    if ( !((*arbre)->right) ) {
        if ( copie(&right_copie, right) ) { (*arbre)->right = right_copie; }
    }
}



uint expansion(Arbre *dest, Arbre source)
{
    uint left = 0, right = 0;
    Arbre source_copie = NULL;
    if (!source || !*dest) return 0;

    left = ((*dest)->left) ? expansion(&((*dest)->left), source) : 1;

    right = ((*dest)->right) ? expansion(&((*dest)->right), source) : 1;

    if ( comparer_chaines((*dest)->nom, source->nom) ) {
        
        if ( !copie(&source_copie, source) ) { return 0; }

        /* On effectue l'ajout des sous arbres de *dest a copie de source */
        if (!source_copie) {
            fprintf(stderr, "On n'a pas droit d'ajouter, pas assez de memoire\n");
            return 0;
        }
        /* l'ajout des sous arbres de la racine a la copie de source */
        ajoute_sous_arbres(&source_copie, (*dest)->left, (*dest)->right);

        liberer_arbre(dest);    /* liberer toute la memoire de *dest car on va la remplacer */

        *dest = source_copie;
    }
    return left && right;
}

