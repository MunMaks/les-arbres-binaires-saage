#ifndef __OPTION_H__
#define __OPTION_H__

#include "saage.h"


extern void greffe_dun_arbre(uint numero);
extern void option_E_main(char *path_create);
extern uint option_G_main(char *argv[]);
extern void option_DOT_main(char *path_create);


/* Fonctions pour dot*/
extern void ecrire_debut(FILE *fptr);
extern void ecrire_arbre(FILE *fptr, Arbre arbre);
extern void ecrire_fin(FILE *fptr);
extern void dessin(FILE *fptr, Arbre arbre);
extern void visualisation_dot(Arbre arbre);


#endif
