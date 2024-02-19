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
typedef unsigned int uint;

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
extern Arbre alloue(const char *chaine);
extern void liberer_arbre(Arbre *arbre);

extern void BFS_ajoute_arbre(Arbre *arbre, char *chaine);  /* complementaire */
extern Arbre construire_arbre(FILE *fichier);
extern void affiche_tree(Arbre arbre);
extern uint est_meme_arbre(Arbre arbre_un, Arbre arbre_deux);



/* les fonction pour les strings */
extern int len_string(const char *mot);
extern char *dupliquer_string(const char *source);
extern char *recherche_lettre(const char *source, char lettre);
extern char *recherche_substring(const char *fullString, const char *substring);
extern int comparer_chaines(const char *string_un, const char *string_deux);




/* Les fonction pour travailler avec les fichiers*/
extern void ajout_tabulation(FILE *fptr, uint count_tab);
extern void creer_file_saage(FILE *fptr, Arbre arbre, uint count_tab);




/* Des exemples */
extern Arbre cree_A_1(void);
extern Arbre cree_A_2(void);
extern Arbre cree_A_3(void);





#endif
