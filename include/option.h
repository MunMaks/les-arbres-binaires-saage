#ifndef __OPTION_H__
#define __OPTION_H__

#include "saage.h"


/* Fonctions pour dot*/
extern void ecrire_debut(FILE *fptr);
extern void ecrire_arbre(FILE *fptr, Arbre arbre);
extern void ecrire_fin(FILE *fptr);
extern void dessine(FILE *fptr, Arbre arbre);
extern void visualisation_dot(Arbre arbre);


/* Foncitons principales */
extern void option_E_main(char *path_create);
extern void option_G_main(char *path_dest, char *path_greffe);
extern void option_DOT_main(char *path_create);
extern void greffe_dun_arbre(char *path);



#endif
