#ifndef __SAAGE_H__

#define __SAAGE_H__

#include "greffe.h"


/* Les fonction pour travailler avec les fichiers*/
extern void ajout_tabulation(FILE *fptr, uint count_tab);
extern void write_fichier_saage(FILE *fptr, Arbre arbre, uint count_tab);
extern uint creer_fichier_saage(Arbre arbre, const char *path_create);

extern Arbre arbre_de_fichier(const char *path);



/* Des exemples */
extern Arbre cree_A_1(void);
extern Arbre cree_A_2(void);
extern Arbre cree_A_3(void);


#endif
