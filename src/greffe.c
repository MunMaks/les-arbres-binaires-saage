#include "../include/greffe.h"


/*
    l'ajoute de sous-arbres gauches: left 
          et de sous-arbres droites: right 
    pour chaques feuilles et noeud interne (avec un enfant)
*/
static __inline__ void ajoute_sous_arbres(Arbre *arbre, Noeud *left, Noeud *right)
{
    Arbre left_copie = NULL, right_copie = NULL;

    if (!*arbre) { return; }

    if ((*arbre)->fg) { ajoute_sous_arbres(&((*arbre)->fg), left, right); }     /* si sous arbre gauche existe */

    if ((*arbre)->fd) { ajoute_sous_arbres(&((*arbre)->fd), left, right); }   /* si sous arbre droite existe */

    /* inserer les sous arbres */
    if ( !((*arbre)->fg) ) { 
        if ( copie(&left_copie, left) ) { (*arbre)->fg = left_copie; }
    }

    if ( !((*arbre)->fd) ) {
        if ( copie(&right_copie, right) ) { (*arbre)->fd = right_copie; }
    }
}


int copie(Arbre *dest, Arbre source)
{
    if (!source) { *dest = NULL; return 1; }
    
    if ( !(*dest = alloue_noeud(source->val)) ) {
        fprintf(stderr, "Erreur d'allocation de memoire pour la copie de l'arbre.\n");
        return 0;
    }

    if ( !(copie(&((*dest)->fg), source->fg)) ) { return 0; }

    if ( !(copie(&((*dest)->fd), source->fd)) ) { return 0; }

    return 1;
}


int expansion(Arbre *dest, Arbre source)
{
    int left = 0, right = 0;
    Arbre source_copie = NULL;
    if (!source || !*dest) return 1;

    left = expansion(&((*dest)->fg), source);

    right = expansion(&((*dest)->fd), source);

    if ( comparer_chaines((*dest)->val, source->val) ) {

        if ( !copie(&source_copie, source) ) { return 0; }

        /* On effectue l'ajout des sous arbres de *dest a copie de source */
        if ( !source_copie ) {
            fprintf(stderr, "On n'a pas droit d'ajouter, pas assez de memoire\n");
            return 0;
        }
        /* l'ajout des sous arbres de la racine a la copie de source */
        ajoute_sous_arbres(&source_copie, (*dest)->fg, (*dest)->fd);

        liberer(dest);    /* liberer toute la memoire de *dest car on va la remplacer */

        *dest = source_copie;
        return 1;
    }
    return left && right;
}
