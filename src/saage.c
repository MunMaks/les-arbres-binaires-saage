#include "../include/saage.h"



void ajout_tabulation(FILE *fptr, uint count_tab)
{
    uint i;
    for (i = 0; i < count_tab; ++i) fprintf(fptr, "    ");    /* fprintf(fptr, "\t"); */
}



void write_fichier_saage(FILE *fptr, Arbre arbre, uint count_tab)
{
    if (!arbre) { return; }

    /* les valeurs */
    ajout_tabulation(fptr, count_tab);
    fprintf(fptr, "Valeur : %s\n", arbre->nom);

    /* les sous-arbres gauches */
    ajout_tabulation(fptr, count_tab);
    fprintf(fptr, (arbre->left) ? ("Gauche : \n") : ("Gauche : NULL\n"));
    write_fichier_saage(fptr, arbre->left, count_tab + 1);

    /* les sous-arbres droites */
    ajout_tabulation(fptr, count_tab);
    fprintf(fptr, (arbre->right) ? ("Droite : \n") : ("Droite : NULL\n"));
    write_fichier_saage(fptr, arbre->right, count_tab + 1);
}



/* la version de la fonction serialise() mais plus parlante */
uint creer_fichier_saage(Arbre arbre, const char *path_create)
{
    FILE *fptr_res = NULL;
    uint count_tab = 0;
    if (!arbre) { return 0; }   /* Arbre est NULL, rien a faire*/

    fptr_res = fopen(path_create, "w");
    if (!fptr_res) {
        fprintf(stderr, "Erreur d'ouverture du %s: %s\n", path_create, strerror(errno));
        return 0;
    }

    write_fichier_saage(fptr_res, arbre, count_tab);
    fclose(fptr_res);
    return 1;
}

/*
int serialise(char *nom_de_fichier, Arbre arbre)
{
    FILE *fptr_res = NULL;
    uint count_tab = 0;
    if (!arbre) { return 0; }

    fptr_res = fopen(nom_de_fichier, "w");
    if (!fptr_res) {
        fprintf(stderr, "Erreur d'ouverture du %s: %s\n", nom_de_fichier, strerror(errno));
        return 0;
    }

    write_fichier_saage(fptr_res, arbre, count_tab);
    fclose(fptr_res);
    return 1;
}
*/


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

/*
int deserialise(char *nom_de_fichier, Arbre *A) 
{
    FILE *fptr = fopen(nom_de_fichier, "r");
    if (!fptr) {
        fprintf(stderr, "Erreur d'ouverture du fichier.saage: %s\n", strerror(errno));
        return 0;
    }
    *A = construire_arbre(fptr);
    fclose(fptr);
    return 1;
}
*/



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


