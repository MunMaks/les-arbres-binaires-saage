#include "../include/option.h"

/*
clang -std=c17 -pedantic exemples/tests_prof.o build/option.o build/arbres_binaires.o build/saage.o build/greffe.o -o tests_prof
valgrind ./tests_prof
*/

int main(int argc, char *argv[])
{
    int i = 0;
    char *path_create = NULL;
    if (argc < 2) {
        fprintf(stderr, "Pas assez de parametres dans main, veuillez reessayez avec options: G, E, DOT, BIG\n");
        return EXIT_SUCCESS;
    }
    for (i = 1; i < argc; ++i) {
        if ( comparer_chaines( *(argv + i), "-G") ) {
            if (i + 2 < argc) 
                option_G_main( *(argv + 1 + i), *(argv + 2 + i) );
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
