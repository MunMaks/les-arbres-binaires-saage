#include "../include/saage.h"



int main(int argc, char *argv[])
{
    Arbre arbre_init = NULL, greffe = NULL, res_attendu = NULL;
    char *path_greffe = NULL, *path_res_att = NULL, *path_create = NULL;

    /*arbre_init = arbre_de_fichier("exemples/A_3.saage"); */            /* "exemples/A_3.saage" */
    arbre_init = cree_A_3();
    path_greffe =   "exemples/D.saage";                        /* source_deux */
    path_res_att = "exemples/A_3_apres_greffe_de_D.saage";     /* resultat attendu */

    path_create = "exemples/created.saage";                   /* notre resultat */

    greffe = arbre_de_fichier(path_greffe); 

    printf("greffe passé: %u\n", faire_greffe(&arbre_init, greffe));

    liberer_arbre(&greffe);


    res_attendu = arbre_de_fichier(path_res_att);

    if (!creer_fichier_saage(arbre_init, path_create)){
        fprintf(stderr, "N'a pas reussi a creer %s\n", path_create);
        return 1;
    }


    printf("La meme arbre 2: %u\n", est_meme_arbre(arbre_init, res_attendu));

    /* pour être sur qu'on aura pas de segfault */
    if (arbre_init) { liberer_arbre(&arbre_init); }
    if (res_attendu) { liberer_arbre(&res_attendu); }

    return 0;
}
