#ifndef __ARBRES_BINAIRES_H__
#define __ARBRES_BINAIRES_H__

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <assert.h>
#include <stdarg.h>


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

/**
 * @brief renvoie la longueur d'une chaine de caractere
 *        similaire a strlen() de <string.h>
 */
extern uint len_string(char *mot);


/**
 * @return 1 si deux chaines sont identiques
 *         0 sinon
*/
extern uint comparer_chaines(char *chaine_un, char *chaine_deux);


/**
 * @brief Cette fonction copie l'adresse de path 
 * et ajoute "exemples/" au debut de buffer
 * si cela n'existe pas deja la bas
*/
extern void path_exemples(char *buffer, char *path);



/********************************************************/
/*                                                      */
/*                        ARBRES                        */
/*                                                      */
/********************************************************/


/**
 * @brief allocation de la memoire pour un noeud
 * 
 * @param chaine 
 * @return Noeud* 
 */
extern Noeud *alloue_noeud(char *chaine);


/**
 * @brief liberation de la memoire allouee par l'arbre
 * 
 * @param arbre 
 */
extern void liberer_arbre(Arbre *arbre);


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


/* Des exemples pour construire A_i.saage  */
extern Arbre cree_A_1(void);
extern Arbre cree_A_2(void);
extern Arbre cree_A_3(void);


#endif
