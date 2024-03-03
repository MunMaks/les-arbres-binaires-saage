#ifndef __OPTION_H__
#define __OPTION_H__

#include "saage.h"


/**
 * @brief  Option -E, l'entree standard de l'utilisateur 
 * d'apres clavier ou d'apres un fichier (non saage)
*/
extern void option_E_main(char *path_create);


/**
 * @brief  Option -G, prends deux chemins valides vers 2 arbres:
 * dest et greffe et cette fonction afficher sur stdout directement
*/
extern void option_G_main(char *path_dest, char *path_greffe);


/**
 * @brief  Option -DOT complementaire
 * prends un chemin valid et l'affiche grâce à DOT
*/
extern void option_DOT_main(char *path_create);


/**
 * @brief  Option -BIG complementaire
 * prends un chemin valid (grand.saage ou immense.saage)
 * et renvoie la greffe d'un arbre et affiche avec DOT
*/
extern void greffe_dun_arbre(char *path);


/* Fonctions pour dot d'apres les cours et TPs */
extern void ecrire_debut(FILE *fptr);
extern void ecrire_arbre(FILE *fptr, Arbre arbre);
extern void ecrire_fin(FILE *fptr);
extern void dessine(FILE *fptr, Arbre arbre);
extern void visualisation_dot(Arbre arbre);

#endif
