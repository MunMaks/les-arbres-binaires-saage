#ifndef __GREFFE_H__
#define __GREFFE_H__

#include "arbres_binaires.h"


extern void ajout_feuilles(Arbre *arbre, Noeud *left, Noeud *right);
extern int copie(Arbre *dest, Arbre source);
extern int expansion(Arbre *dest, Arbre source);
extern Arbre faire_greffe(const char *path_un, const char *path_deux);
extern Arbre arbre_de_fichier(const char *path);




#endif
