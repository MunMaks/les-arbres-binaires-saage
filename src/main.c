#include "../include/option.h"


/*
Soit i = {1, 2, 3}, X = {B, C, D}
Usage d'option -G avec ou sans "exemples/"
valgrind ./algo -G A_i.saage X.saage
valgrind ./algo -G exemples/A_i.saage exemples/X.saage
*/


/*
Soit i = {1, 2, 3}
Usage d'option -E avec ou sans "exemples/"

l'entree stadart de l'utilisateur d'apres exemples/usr_A_i.txt
valgrind ./algo -E exemples/new_fichier.saage < exemples/usr_A_i.txt

l'entree standart de l'utilisateur d'apres clavier:
valgrind ./algo -E new_fichier.saage
*/


/*
Usage d'option -DOT
valgrind ./algo -DOT fichier.saage
valgrind ./algo -DOT exemples/fichier.saage
*/


/*
Usage d'option BIG avec ou sans "exemples/"
valgrind ./algo -BIG exemples/grand.saage
valgrind ./algo -BIG immense.saage 
*/

int main(int argc, char *argv[])
{
    int i = 0;
    char *path_create = NULL;
    if (argc < 2) {
        fprintf(stderr, "Pas assez de parametres dans main, veuillez reessayez\n");
        return EXIT_SUCCESS;
    }
    for (i = 1; i < argc; ++i) {
        if ( comparer_chaines(*(argv + i), "-G") ) {
            if (i + 2 < argc) 
                option_G_main(*(argv + 1 + i), *(argv + 2 + i));
            return EXIT_SUCCESS;
        }

        else if (comparer_chaines( *(argv + i), "-E") ||
                 comparer_chaines( *(argv + i), "-DOT") ) {

            if (i + 1 < argc) {
                path_create = *(argv + 1 + i);
                if (comparer_chaines( *(argv + i), "-E"))
                    option_E_main(path_create);
                else
                    option_DOT_main(path_create);
            }
            return EXIT_SUCCESS;
        }

        else if ( comparer_chaines( *(argv + i), "-BIG") &&  
                  (i + 1 < argc) ) {
            path_create = *(argv + 1 + i);
            greffe_dun_arbre(path_create);
            return EXIT_SUCCESS;
        }
    }
    return EXIT_SUCCESS;
}
