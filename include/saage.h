#ifndef __SAAGE_H__
#define __SAAGE_H__

#include "greffe.h"

/**
 * @brief serialisation d'un arbre pour un chemin: path_create
 * @return renverra 1 en cas de succès et 0 sinon.
*/
extern int serialise(char * __restrict__ path_create, Arbre __restrict__ arbre);


/**
 * @brief deserialise() lit le fichier saage dont le nom (path) est passe en paramètre
 * et cree l’arbre qu’il decrit dans *arbre.
 * @return renverra 1 en cas de succès et 0 sinon.
*/
extern int deserialise(char * __restrict__ path, Arbre * __restrict__ arbre);

#endif
