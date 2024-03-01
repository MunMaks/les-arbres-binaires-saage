#ifndef __SAAGE_H__
#define __SAAGE_H__

#include "greffe.h"

/* Les fonction pour travailler avec les fichiers*/

extern void ajout_tabulation(FILE *fptr, uint count_tab);
extern void ecrire_fichier_saage(FILE *fptr, Arbre arbre, uint count_tab);
extern int serialise(char *path_create, Arbre arbre);
extern int deserialise(char *path, Arbre *arbre);


#endif
