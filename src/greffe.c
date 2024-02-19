#include "../include/greffe.h"


int copie(Arbre *dest, Arbre source)
{
    if ( !source ) { *dest = NULL; return 1; }  /* source est vide */

    if ( !(*dest = alloue(source->nom)) ) { return 0; }  /* allocation mal passe */

    if (!copie(&((*dest)->left), source->left) || !copie(&((*dest)->right), source->right)) {
        liberer_arbre(dest);
        return 0;
    }
    return 1;
}



// int expansion(Arbre *A, Arbre B)
// {
//     int left = 0, right = 0;

//     if (!B || !*A) { return 1; }

//     left = expansion(&(*A)->left, B);
//     right = expansion(&(*A)->right, B);

//     if ( comparer_chaines( (*A)->nom, B->nom ) ) {
//         Arbre B_copie = NULL, sous_arbre_gauche = NULL, sous_arbre_droite = NULL;

//         /* si n'a pas reussi de copier arbre-greffe */
//         if ( !copie(&B_copie, B) ) { fprintf(stderr, "Pas reussi de copier arbre B"); return 0; }

//         /* si n'a pas reussi de copier des sous arbres de A (s'ils existent) */
//         if ( !copie(&sous_arbre_gauche, (*A)->left) || 
//              !copie(&sous_arbre_droite, (*A)->right) ) {
//             fprintf(stderr, "Pas reussi de copier des sous arbres de A");
//             liberer_arbre(&B_copie);
//             return 0;
//         }

//         /* On effectue l'ajout des sous arbres de A a copie de B */
//         ajout_feuilles(&B_copie, sous_arbre_gauche, sous_arbre_droite);
//         *A = B_copie;
//         return 1;
//     }
//     return left && right;
// }

