#include "../include/option.h"



int main(int argc, char *argv[])
{
    /*
    if (argc != 4) {
        fprintf(stderr, "Usage: %s -G s.saage g.saage\n", argv[0]);
        return 1; } */

    uint i;
    for (i = 0; i < argc; ++i) {
        if ( recherche_substring(*(argv + i), "-G") ) {
            if (recherche_substring(*(argv+1 + i), ".saage") &&
                recherche_substring(*(argv+2 + i), ".saage") ) {
                option_G_main(argv);
            }
            return 0;
        }
        else if ( recherche_substring( *(argv + i), "-E") ) {
            if ( recherche_substring(*(++argv + i), ".saage") ) {
                char *path_create = *(argv + i);
                option_E_main(path_create);
            }
            return 0;
        }
    }


    /* greffe_dun_arbre(5); */

    /*res_attendu = arbre_de_fichier(path_res_att);
    printf("La meme arbre 2: %u\n", est_meme_arbre(arbre_init, res_attendu));*/
    return 0;
}

