#include "../include/saage.h"


/**
 * @brief l'ajout des tabulations dans fichier .saage
*/
static __inline__ void ajout_tabulation(FILE * __restrict__ fptr, uint count_tab)
{
    uint i;
    for (i = 0; i < count_tab; ++i) fprintf(fptr, "    ");
}


/**
 * @brief l'ecriture de l'arbre dans un fichier .saage ouvert par serialise()
*/
static __inline__ void ecrire_fichier_saage(FILE * __restrict__ fptr, Arbre arbre, uint count_tab)
{
    if ( !arbre ) { return; }

    /* les valeurs */
    ajout_tabulation(fptr, count_tab);
    fprintf(fptr, "Valeur : %s\n", arbre->val);

    /* les sous-arbres gauches */
    ajout_tabulation(fptr, count_tab);
    fprintf(fptr, (arbre->fg) ? ("Gauche : \n") : ("Gauche : NULL\n"));
    ecrire_fichier_saage(fptr, arbre->fg, count_tab + 1);

    /* les sous-arbres droites */
    ajout_tabulation(fptr, count_tab);
    fprintf(fptr, (arbre->fd) ? ("Droite : \n") : ("Droite : NULL\n"));
    ecrire_fichier_saage(fptr, arbre->fd, count_tab + 1);
}



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
    if ( fclose(fptr_res) ){
        fprintf(stderr, "la fermeture de fichier %s a echoue \n", path_create);
    }
    return 1;
}


int deserialise(char *path, Arbre *arbre)
{
    if (!path) { return 0; }

    *arbre = arbre_de_fichier(path);

    return (*arbre) ? (1) : (0);
}
