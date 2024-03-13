#ifndef __GREFFE_H__
#define __GREFFE_H__

#include "arbres_binaires.h"


/**
 * @brief copie de source a *dest 
 * @return renverra 1 en cas de succes la copie et 0 sinon 
*/
extern int copie(Arbre * __restrict__ dest, Arbre __restrict__ source);


/**
 * @brief *dest va contenir la greffe de l’arbre source.
 * @return renverra 1 en cas de succes et 0 sinon.
 */
extern int expansion(Arbre * __restrict__ dest, Arbre __restrict__ source);


#endif
