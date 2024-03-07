#ifndef __SAAGE_H__
#define __SAAGE_H__

#include "greffe.h"

/**
 * @brief serialisation d'un arbre pour un chemin: path_create
 * @return renverra 1 en cas de succès et 0 sinon.
*/
extern int serialise(char *path_create, Arbre arbre);


/**
 * @brief deserialise() lit le fichier saage dont le nom (path) est passe en paramètre
 * et cree l’arbre qu’il decrit dans *arbre.
 * @return renverra 1 en cas de succès et 0 sinon.
*/
extern int deserialise(char *path, Arbre *arbre);

#endif
