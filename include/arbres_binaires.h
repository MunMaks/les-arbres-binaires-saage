#ifndef __ARBRES_BINAIRES_H__
#define __ARBRES_BINAIRES_H__

/*#define _POSIX_C_SOURCE 200809L*/
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <assert.h>
#include <stdarg.h>

/* Macros de comparaisons 
#define MAX(x, y) (( (x) > (y) ) ? (x) : (y) )
#define MIN(x, y) (( (x) < (y) ) ? (x) : (y) )
*/

#define MAX_SIZE 4096
#define CHAR_SIZE 256
typedef unsigned int uint; 


typedef struct _noeud {
    char *nom;
    struct _noeud *left, *right;
} Noeud, *Arbre;



/********************************************************/
/*                                                      */
/*                       STRINGS                        */
/*                                                      */
/********************************************************/

extern uint len_string(char *mot);

extern char *recherche_lettre(char *source, char lettre);

extern char *recherche_substring(char* nom_complet, char* substring);

extern uint comparer_chaines(char *chaine_un, char *chaine_deux);

extern char *dupliquer_nom(char *source);

/* cette fonction copie source dans dest */
extern void copie_chaine(char* dest, char* source);

/* cette fonction concatene destination et source */
extern void concatenantion(char* dest, char* source);

/*  
    Cette fonction copie l'adresse de path 
    et ajoute "exemples/" au debut de buffer
    si cela n'existe pas deja la bas
*/
extern void path_exemples(char *buffer, char *path);



/********************************************************/
/*                                                      */
/*                        ARBRES                        */
/*                                                      */
/********************************************************/


extern Noeud *alloue_noeud(char *chaine);

extern void liberer_arbre(Arbre *arbre);

extern int construire_arbre(FILE *fptr, Arbre *arbre);

extern Arbre arbre_de_fichier(char *path);

extern uint est_meme_arbre(Arbre arbre_un, Arbre arbre_deux);


extern uint creer_arbre_stdin(Arbre *arbre);
extern void affiche_sur_stdout(char *path_create);


/* Des exemples */
extern Arbre cree_A_1(void);
extern Arbre cree_A_2(void);
extern Arbre cree_A_3(void);


#endif
