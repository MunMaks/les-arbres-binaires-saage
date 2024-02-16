#include "../include/arbres_binaires.h"


Noeud *alloue_noeud(char *chaine)
{
    Noeud *noued = NULL;
    if (!(noeud = malloc(sizeof *noued) )) { return NULL; }

    strcpy(noeud->nom, chaine);

    noeud->right = noeud->left = NULL;
    return noued;
}



int hauteur (Arbre root)
{
    if (! root) { return -1; }
    else {
        int left = hauteur(root->left);
        int right = hauteur(root->right);
        return MAX(left, right) + 1;
    }
}


int creer_arbre(FILE *fptr, Arbre *root)
{
    int val = 0;
    char buffer[MAX_SIZE];
    // if (!(*root)) { return 0; }

    if ((fscanf(fptr, "%d ", &val)) <= 0) {
        return 0;
    }
    if (val == 0) { return 1; }

    else if (fscanf(fptr, "%s", buffer) <= 0 ) {
        return 0;
    }

    if ( ! (*root = alloue(buffer)) ) {
        return 0;
    }

    return creer_arbre(fptr, &((*root)->left)) &&
           creer_arbre(fptr, &((*root)->right));
}





void ecrireDebut(FILE *fptr)
{
    fprintf(fptr, "digraph arbre{\n    node [ shape = record, height = .1]\n    edge [ tailclip = false , arrowtail = dot, dir = both];\n\n");
}



void ecrireArbre(FILE *fptr, Arbre root)
{   
    if (!root) { return; }     /* rien a faire */

    fprintf(fptr,"    n%p [label=\"<gauche> | <valeur> %d | <droit>\"];\n", (void *) root, root->valeur);

    if (root->left) {
        fprintf(fptr, "    n%p:gauche:c -> n%p:valeur;\n", (void *) root, (void *) root->left);
        ecrireArbre(fptr, root->left);
    }

    if (root->right) {
        fprintf(fptr, "    n%p:droit:c -> n%p:valeur;\n", (void *) root, (void *) root->right);
        ecrireArbre(fptr, root->right);
    }
}



void ecrireFin(FILE *fptr) { fprintf(fptr, "}"); }



void dessine ( FILE *fptr , Arbre root) {
    ecrireDebut (fptr);
    ecrireArbre (fptr, root);
    ecrireFin (fptr);
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



/* example.saage

1 "arbre\n" 1 "binaire\n" 0 0 1 "ternaire\n" 0 0

*/
Arbre cree_A_1(void)
{
    Arbre arbre = NULL;
    
    Arbre arbre_droit = NULL, arbre_gauche = NULL;
    
    if(! (arbre = alloue_noeud("arbre\n")) ) { return NULL; }

    if(! (arbre_gauche = alloue_noeud("binaire\n")) ) { liberer_arbre(&arbre); return NULL; }

    if(! (arbre_droit = alloue_noeud("ternaire\n")) ) { liberer_arbre(&arbre); return NULL; }


    arbre->left = arbre_gauche;
    arbre->right = arbre_droit;

    return arbre;
}


/* TO DO */
Arbre cree_A_2(void)
{

}


/* TO DO */
Arbre cree_A_3(void)
{

}

