#ifndef __ARBRES_BINAIRES_H__
#define __ARBRES_BINAIRES_H__

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdint.h>

#include <stdarg.h>
#include <ctype.h>
#include <stdint.h>
#include <errno.h>

/* Macros de comparaisons */
#define MAX(x, y) (( (x) > (y) ) ? (x) : (y) )
#define MIN(x, y) (( (x) < (y) ) ? (x) : (y) )

#define MAX_SIZE 4096
#define CHAR_SIZE 256
typedef unsigned int uint; 


typedef struct _noeud{
    char *nom;
    struct _noeud *left, *right;
} Noeud, *Arbre;




/* Les fonctions pour les arbres */
extern Arbre alloue(const char *chaine);
extern void detruire_noeud(Noeud *noeud);
extern void liberer_arbre(Arbre *arbre);
extern Arbre construire_arbre(FILE *fptr);


extern uint est_meme_arbre(Arbre arbre_un, Arbre arbre_deux);
extern uint creer_arbre(FILE *fptr, Arbre *arbre);


/* les fonctions pour les strings */
extern uint len_string(const char *mot);
extern char *dupliquer_string(const char *source);
extern char *recherche_lettre(const char *source, char lettre);
extern char *recherche_substring(const char *fullString, const char *substring);
extern uint comparer_chaines(const char *string_un, const char *string_deux);
extern void copie_chaine(char* dest, const char* source);
extern void concatenantion(char* dest, char* source);



extern void affiche_sur_stdout(const char *path_create);


#endif
