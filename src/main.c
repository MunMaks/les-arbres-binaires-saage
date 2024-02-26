#include "../include/option.h"



int main(int argc, char *argv[])
{
    uint i;
    for (i = 1; i < argc; ++i) {
        /* saage -G s.saage g.saage */
        if ( recherche_substring(*(argv + i), "-G") ) {

            if (recherche_substring(*(argv + 1 + i), ".saage") && 
                recherche_substring(*(argv + 2 + i), ".saage") && 
                i + 2 < argc)
                { option_G_main(argv); }

            return 0;
        }
        /* -E ou -DOT option*/
        else if (recherche_substring( *(argv + i), "-E") ||
                 recherche_substring( *(argv + i), "-DOT")) {

            if (recherche_substring(*(argv + 1 + i), ".saage") &&
                i + 1 < argc) {
                char *path_create = *(argv + 1 + i);
                if (recherche_substring( *(argv + i), "-E"))
                    option_E_main(path_create);
                else
                    option_DOT_main(path_create);

            }
            return 0;
        } else {
            greffe_dun_arbre(5);
        }
    }

    /*res_attendu = arbre_de_fichier(path_res_att);
    printf("La meme arbre 2: %u\n", est_meme_arbre(arbre_init, res_attendu));*/
    return 0;
}

