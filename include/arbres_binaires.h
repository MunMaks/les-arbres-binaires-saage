#ifndef __ARBRES_BINAIRES_H__
#define __ARBRES_BINAIRES_H__

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>


#define MAX_SIZE 2048
#define CHAR_SIZE 256
typedef unsigned int uint; 


typedef struct _noeud {
    char *val;
    struct _noeud *fg, *fd;
} Noeud, *Arbre;


/********************************************************/
/*                                                      */
/*                       STRINGS                        */
/*                                                      */
/********************************************************/

/**
 * @brief renvoie la longueur d'une chaine de caractere
 */
extern uint len_string(char * __restrict__ mot);


/**
 * @brief 1 si deux chaines sont identiques
 *         0 sinon
*/
extern uint comparer_chaines(char * __restrict__ chaine_un, char * __restrict__ chaine_deux);


/**
 * @brief Cette fonction copie l'adresse de path 
 * et ajoute "exemples/" au debut de buffer
 * si cela n'existe pas deja la bas
*/
extern void path_exemples(char * __restrict__ buffer, char * __restrict__ path);



/********************************************************/
/*                                                      */
/*                        ARBRES                        */
/*                                                      */
/********************************************************/


/**
 * @brief allocation de la memoire pour un noeud
 * @return le pointeur Noeud *
 */
extern Noeud *alloue_noeud(char * __restrict__ chaine);


/**
 * @brief liberation de la memoire allouee par l'arbre
 */
extern void liberer(Arbre * __restrict__ arbre);


/**
 * @brief renvoie l'arbre deja construit d'apres le chemin pour fichier .saage 
 * @return le pointeur Arbre si tout va bien et NULL sinon 
*/
extern Arbre arbre_de_fichier(char * __restrict__ path);


/**
 * @brief le nom nous dit que c'est la lecture d'un fichier .saage
 *          a partir de l'entree standart (stdin) 
 * @return 1 si tout va bien et 0 sinon  
*/
extern int construit_arbre(Arbre * __restrict__ arbre);


/* Des exemples pour construire A_1, A_2, A_3  */
extern Arbre cree_A_1(void);

extern Arbre cree_A_2(void);

extern Arbre cree_A_3(void);


#endif
