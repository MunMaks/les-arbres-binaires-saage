#include "../include/saage.h"



int main(int argc, char *argv[])
{
    char *path_un =     "exemples/A_3.saage";
    char *path_deux =   "exemples/D.saage";
    char *path_create = "exemples/created.saage";

    char *path_greffe = "exemples/A_3_apres_greffe_de_D.saage";

    // Arbre res = faire_greffe(path_un, path_deux);
    Arbre A = arbre_de_fichier(path_un);
    Arbre B = arbre_de_fichier(path_deux);
    Arbre res = arbre_de_fichier(path_greffe);

    printf("expansion est: %d\n", expansion(&A, B));

    printf("est meme arbre : %d\n", est_meme_arbre(A, res));

    /* SEG FAULT FROM HERE */
    /* À GERER PLUS TARD */



    // expansion(&res, res2);
    // FILE *fptr_res = fopen(path_create, "w");
    // if (!fptr_res) {
    //     fprintf(stderr, "Erreur d'ouverture du fichier\n");
    //     return 1;
    // }

    // uint count_tab = 0;
    // creer_file_saage(fptr_res, res, count_tab);
    // fclose(fptr_res);
    // affiche(res);
    // affiche(apres_greffe);

    // valgrind: total heap usage: 207 allocs, 199 frees, 30,738 bytes allocated

    liberer_arbre(&A);
    liberer_arbre(&B);
    liberer_arbre(&res);
    // liberer_arbre(&apres_greffe);
    return 0;
}
