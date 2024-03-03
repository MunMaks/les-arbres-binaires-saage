#ifndef __GREFFE_H__
#define __GREFFE_H__

#include "arbres_binaires.h"

/* l'ajoute de sous-arbres gauches - left et sous-arbres droite - right 
pour chaques feuilles / noeuds avec un fils */
extern void ajoute_sous_arbres(Arbre *arbre, Noeud *left, Noeud *right);

/**
 * @brief copie de source a *dest 
 * @return renverra 1 en cas de succès la copie et 0 sinon 
*/
extern int copie(Arbre *dest, Arbre source);


/**
 * @brief *dest contienne la greffe de l’arbre source sur *dest.
 * @return renverra 1 en cas de succès et 0 sinon.
 */
extern int expansion(Arbre *dest, Arbre source);


#endif
