/* Arbre binaires */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>



typedef struct _noeud{
    char *val;  // discutable
    struct _noeud *left, *right;
} Noeud, *Arbre;



Noeud *alloue_noeud(char *s)
{
    Noeud *noued = malloc(sizeof *noued);
    if (!noeud) { return NULL; }

    strcpy(noeud->val, s);
    noeud->right = noeud->left = NULL;
    return noued;
}



void liberer_arbre(Arbre *arbre)
{
    if (*arbre){
        liberer_arbre(&(*arbre)->left);
        liberer_arbre(&(*arbre)->right);
        free(*arbre);
        *arbre = NULL;
    }
}



/* TO DO */
Arbre cree_A_1(void)
{

}


/* TO DO */
Arbre cree_A_2(void)
{

}


/* TO DO */
Arbre cree_A_3(void)
{

}


