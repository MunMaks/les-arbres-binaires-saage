#include "../include/saage.h"


/* n'est pas verifiée */
uint serialise(const char *nom_de_fichier, Arbre A)
{
    /*
    Arbre tmp_arbre = NULL;
    uint count_tab = 0, res;
    FILE *fptr = fopen(nom_de_fichier, "w");
    if (!fptr) {
        fprintf(stderr, "Erreur d'ouverture du fichier\n");
        return 0;
    }

    creer_fichier_saage(fptr, A, count_tab);
    fclose(fptr);

    FILE *fptr_res = fopen(nom_de_fichier, "r");
    if (!fptr) {
        fprintf(stderr, "Erreur d'ouverture du fichier\n");
        return 0;
    }
    tmp_arbre = construire_arbre(fptr_res);
    fclose(fptr_res);

    res = est_meme_arbre(A, tmp_arbre);
    liberer_arbre(&tmp_arbre);
    
    return res;*/
    return 0;
}
