#include "../include/saage.h"


void ajout_tabulation(FILE *fptr, uint count_tab)
{
    uint i;
    for (i = 0; i < count_tab; ++i) fprintf(fptr, "    ");
}


void ecrire_fichier_saage(FILE *fptr, Arbre arbre, uint count_tab)
{
    if ( !arbre ) { return; }

    /* les valeurs */
    ajout_tabulation(fptr, count_tab);
    fprintf(fptr, "Valeur : %s\n", arbre->nom);

    /* les sous-arbres gauches */
    ajout_tabulation(fptr, count_tab);
    fprintf(fptr, (arbre->left) ? ("Gauche : \n") : ("Gauche : NULL\n"));
    ecrire_fichier_saage(fptr, arbre->left, count_tab + 1);

    /* les sous-arbres droites */
    ajout_tabulation(fptr, count_tab);
    fprintf(fptr, (arbre->right) ? ("Droite : \n") : ("Droite : NULL\n"));
    ecrire_fichier_saage(fptr, arbre->right, count_tab + 1);
}


/* la fonction creer_fichier_saage() est plus parlante */
int serialise(char *path_create, Arbre arbre)
{
    FILE *fptr_res = NULL;
    uint count_tab = 0;
    if ( !arbre ) { return 0; }   /* Arbre est NULL, rien a faire*/

    fptr_res = fopen(path_create, "w");
    if ( !fptr_res ) {
        fprintf(stderr, "Erreur d'ouverture du %s: %s\n", path_create, strerror(errno));
        return 0;
    }

    ecrire_fichier_saage(fptr_res, arbre, count_tab);
    fclose(fptr_res);
    return 1;
}


int deserialise(char *path, Arbre *arbre)
{
    if (!path) { return 0; }

    *arbre = arbre_de_fichier(path);

    return (*arbre) ? (1) : (0);
}
