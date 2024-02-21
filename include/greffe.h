#ifndef __GREFFE_H__
#define __GREFFE_H__

#include "arbres_binaires.h"

/* extern int copie(Arbre *dest, Arbre source); */

extern void ajoute_sous_arbres(Arbre *arbre, Noeud *left, Noeud *right);
extern Arbre copie(Arbre source);
extern Arbre arbre_de_fichier(const char *path);
extern uint expansion(Arbre *dest, Arbre source);
extern uint faire_greffe(Arbre *dest, Arbre source);


/* Des exemples */
extern Arbre cree_A_1(void);
extern Arbre cree_A_2(void);
extern Arbre cree_A_3(void);

#endif
