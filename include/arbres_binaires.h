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

/**
 * @brief Cherche une lettre dans source
 * @return le pointeur sur ce lettre dans source (NULL sinon)
 * static function
static char *recherche_lettre(char *source, char lettre);
*/


/**
 * @brief Cherche une chaine de caractere dans source
 * @return le pointeur sur la premier occurrence dans source (NULL sinon)
 */
extern char *recherche_substring(char* nom_complet, char* substring);

/**
 * @return 1 si deux chaines sont identiques et 0 sinon
*/
extern uint comparer_chaines(char *chaine_un, char *chaine_deux);

/**
 * @return renvoie la copie de la source (en utilisant malloc)
 * static function
static char *dupliquer_nom(char *source);
*/

/**
 * @brief cette fonction copie source dans dest 
 * static function
static void copie_chaine(char* dest, char* source);
*/

/**
 * @brief cette fonction concatene destination et source
 * static function
static void concatenantion(char* dest, char* source);
*/


/**
 * @brief Cette fonction copie l'adresse de path 
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

/**
 * @brief constuire arbre d'apres le fichier .saage
 * @return 1 si tout va bien et 0 sinon 
 * static function
static int arbre_de_fichier_aux(FILE *fptr, Arbre *arbre);
*/

/**
 * @brief renvoie l'arbre deja construit d'apres le chemin pour fichier .saage 
 * @return le pointeur Arbre si tout va bien et NULL sinon 
*/
extern Arbre arbre_de_fichier(char *path);

/**
 * @brief verifie si deux arbres sont identiques 
 * @return 1 si tout va bien et 0 sinon  
*/
extern uint est_meme_arbre(Arbre arbre_un, Arbre arbre_deux);

/*static uint creer_arbre_stdin(Arbre *arbre);*/

/*static void affiche_sur_stdout(char *path_create);*/


/* Des exemples pour construire A_i.saage  */
extern Arbre cree_A_1(void);
extern Arbre cree_A_2(void);
extern Arbre cree_A_3(void);


#endif
