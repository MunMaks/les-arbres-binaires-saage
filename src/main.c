#include "../include/option.h"


int main(int argc, char *argv[])
{
    int i;
    if (argc < 2) {
        fprintf(stderr, "Pas assez de parametres dans main, veuillez reessayez\n");
        return EXIT_SUCCESS;
    }

    for (i = 1; i < argc; ++i) {
        /* saage -G s.saage g.saage */
        if ( recherche_substring(*(argv + i), "-G") ) {

            if (i + 2 < argc) {
                char *path_dest = *(argv + 1 + i);
                char *path_greffe = *(argv + 2 + i);
                option_G_main(path_dest, path_greffe);
            }

            return EXIT_SUCCESS;
        }
        /*
        ./main -E new_fichier.saage < from_keyboard.txt
        ./main -E exemples/new_fichier.saage < exemples/from_keyboard.txt
        */
        else if (recherche_substring( *(argv + i), "-E") ||
                 recherche_substring( *(argv + i), "-DOT")) {

            if (i + 1 < argc) {
                char *path_create = *(argv + 1 + i);

                if (recherche_substring( *(argv + i), "-E"))
                    option_E_main(path_create);
                else
                    option_DOT_main(path_create);
            }
            return EXIT_SUCCESS;
        }
        /* IL FAUT TESTER CELA ENCOOOOOOOORE, ne marche pas.... */
        else if (recherche_substring( *(argv + i), "-AM")) {    /* 4 pour grand, 5 pour immense*/
            printf("AMMMMMMMMMMMm\n");
            greffe_dun_arbre( (uint) 2 );    
            return EXIT_SUCCESS;
        }
    }

    return EXIT_SUCCESS;
}
