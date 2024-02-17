#ifndef __ARBRES_BINAIRES_H__
#define __ARBRES_BINAIRES_H__

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include <stdarg.h>
#include <ctype.h>
#include <stdint.h>
#include <errno.h>

/* Macros de comparaisons */
#define MAX(x, y) (( (x) > (y) ) ? (x) : (y) )
#define MIN(x, y) (( (x) < (y) ) ? (x) : (y) )


#define MAX_SIZE 2048


typedef struct _noeud{
    char *nom;
    struct _noeud *left, *right;
} Noeud, *Arbre;

/* Fonction pour dot*/
extern void ecrire_debut(FILE *fptr);
extern void ecrire_arbre(FILE *fptr, Arbre arbre);
extern void ecrire_fin(FILE *fptr);
extern void dessin(FILE *fptr, Arbre arbre);


/* Les fonctions pour les arbres */
extern int len(char *mot);
extern Arbre alloue(const char *chaine);
extern void liberer_arbre(Arbre *arbre);
extern int hauteur(Arbre arbre);

/* Les fonction pour travailler avec les fichiers*/
extern int creer_arbre(FILE *fptr, Arbre *arbre);
extern int SAAGE_creer_arbre(FILE *fptr, Arbre *arbre);


/* Des exemples */
extern Arbre cree_A_1(void);
extern Arbre cree_A_2(void);
extern Arbre cree_A_3(void);





#endif
