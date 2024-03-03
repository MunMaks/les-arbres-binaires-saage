#ifndef __SAAGE_H__
#define __SAAGE_H__

#include "greffe.h"

/**
 * @brief l'ajout des tabulations dans fichier .saage
*/
extern void ajout_tabulation(FILE *fptr, uint count_tab);

/**
 * @brief l'ecriture de l'arbre dans un fichier .saage ouvert par serialise()
*/
extern void ecrire_fichier_saage(FILE *fptr, Arbre arbre, uint count_tab);

/**
 * @brief serialisation d'un arbre pour un chemin: path_create
 * @return renverra 1 en cas de succès et 0 sinon.
*/
extern int serialise(char *path_create, Arbre arbre);

/**
 * @brief deserialise() lit le fichier saage dont le nom (path) est passé en paramètre et 
 * cree l’arbre qu’il decrit dans *arbre.
 * @return renverra 1 en cas de succès et 0 sinon.
*/
extern int deserialise(char *path, Arbre *arbre);


#endif
