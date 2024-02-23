#ifndef __GREFFE_H__
#define __GREFFE_H__

#include "arbres_binaires.h"


extern void ajoute_sous_arbres(Arbre *arbre, Noeud *left, Noeud *right);
extern uint copie(Arbre *dest, Arbre source);
extern uint expansion(Arbre *dest, Arbre source);


#endif
