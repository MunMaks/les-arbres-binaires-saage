#include "../include/greffe.h"


/* Cette fonction ajoute left et right pour chaque feuilles de l'arbre */
void ajoute_sous_arbres(Arbre *arbre, Noeud *left, Noeud *right)
{
    Arbre left_copie = NULL, right_copie = NULL;

    if (!*arbre) { return; }

    if ((*arbre)->left) { ajoute_sous_arbres(&((*arbre)->left), left, right); }     /* si sous arbre gauche existe */

    if ((*arbre)->right) { ajoute_sous_arbres(&((*arbre)->right), left, right); }   /* si sous arbre droite existe */


    /* inserer les sous arbres */
    if ( !((*arbre)->left) ) { 
        left_copie = copie(left);
        (*arbre)->left = left_copie;
    }

    if ( !((*arbre)->right) ) {
        right_copie = copie(right);
        (*arbre)->right = right_copie;
    }
}




/* fonction renvoie la copie de l'arbre source */
Arbre copie(Arbre source)
{
    Arbre new_node = NULL;
    if (!source) { return NULL; }
    
    if ( !(new_node = alloue(source->nom)) ) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la copie de l'arbre.\n");
        return NULL;
    }

    new_node->left = copie(source->left);
    new_node->right = copie(source->right);

    return new_node;
}


/* charger un arbre de type .saage d'apres son chemin*/
Arbre arbre_de_fichier(const char *path)
{
    Arbre arbre = NULL;
    FILE *fptr = fopen(path, "r");
    if (!fptr) {
        fprintf(stderr, "Erreur d'ouverture du fichier.saage: %s\n", strerror(errno));
        return NULL; }

    arbre = construire_arbre(fptr);
    fclose(fptr);
    return arbre;
}



uint expansion(Arbre *dest, Arbre source)
{
    uint left = 0, right = 0;
    if (!source || !*dest) return 0;

    left = ((*dest)->left) ? expansion(&((*dest)->left), source) : 1;

    right = ((*dest)->right) ? expansion(&((*dest)->right), source) : 1;

    if ( comparer_chaines((*dest)->nom, source->nom) ) {    /*comparer_chaines()*/

        Arbre source_copie = copie(source);

        /* On effectue l'ajout des sous arbres de *dest a copie de source */
        if (!source_copie) {
            fprintf(stderr, "On n'a pas droit d'ajouter, pas assez de memoire\n");
            return 0;
        }
        /* l'ajout des sous arbres de la racine */
        ajoute_sous_arbres(&source_copie, (*dest)->left, (*dest)->right);

        liberer_arbre(dest);    /* liberer toute la memoire alloue par dest */

        *dest = source_copie;
    }
    return left && right;
}



uint faire_greffe(Arbre *dest, Arbre source)
{

    if ( expansion(dest, source) ) {
        return 1;
    }

    fprintf(stderr, "expansion a mal passe, la memoire ...\n");
    return 0;
}



Arbre cree_A_1(void)
{
    Arbre arbre = NULL;
    char *path = "exemples/A_1.saage";
    arbre = arbre_de_fichier(path);
    return arbre;
}



Arbre cree_A_2(void)
{
    Arbre arbre = NULL;
    char *path = "exemples/A_2.saage";
    arbre = arbre_de_fichier(path);
    return arbre;
}


Arbre cree_A_3(void)
{
    Arbre arbre = NULL;
    char *path = "exemples/A_3.saage";
    arbre = arbre_de_fichier(path);
    return arbre;
}