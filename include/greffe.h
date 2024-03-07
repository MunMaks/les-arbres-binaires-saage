#ifndef __GREFFE_H__
#define __GREFFE_H__

#include "arbres_binaires.h"


/**
 * @brief copie de source a *dest 
 * @return renverra 1 en cas de succès la copie et 0 sinon 
*/
extern int copie(Arbre *dest, Arbre source);


/**
 * @brief *dest contienne la greffe de l’arbre source sur *dest.
 * @return renverra 1 en cas de succès et 0 sinon.
 */
extern int expansion(Arbre *dest, Arbre source);


#endif
