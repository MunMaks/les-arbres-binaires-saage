#ifndef __ARBRES_BINAIRES_H__

#define __ARBRES_BINAIRES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include <stdarg.h>
#include <ctype.h>
#include <stdint.h>

/* Macros de comparaisons */
#define MAX(x, y) (( (x) > (y) ) ? (x) : (y) )
#define MIN(x, y) (( (x) < (y) ) ? (x) : (y) )


#define MAX_SIZE 100


typedef struct _noeud{
    char *nom;
    struct _noeud *left, *right;
} Noeud, *Arbre;



#endif
