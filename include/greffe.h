#ifndef __GREFFE_H__
#define __GREFFE_H__

#include "arbres_binaires.h"

/* Cette fonction ajoute left et right pour chaque feuilles de l'arbre */
extern void ajoute_sous_arbres(Arbre *arbre, Noeud *left, Noeud *right);

/* copie de source a *dest */
extern int copie(Arbre *dest, Arbre source);

/* effectue la greffe */
extern int expansion(Arbre *dest, Arbre source);


#endif
