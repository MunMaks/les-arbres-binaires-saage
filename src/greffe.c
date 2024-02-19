#include "../include/greffe.h"


void ajout_feuilles(Arbre *arbre, Noeud *left, Noeud *right)
{
    if (!*arbre) { return; }    /* rien a ajouter */

    ajout_feuilles(&((*arbre)->left), left, right);
    ajout_feuilles(&((*arbre)->right), left, right);

    if ( !((*arbre)->left) && !((*arbre)->right) ) {
        (*arbre)->left = left;
        (*arbre)->right = right;
    }
}


/*  fonction copie dans *dest l’arbre stocke dans source.
    1 - succès
    0 - echec */
int copie(Arbre *dest, Arbre source)
{
    if ( !dest ) { return 0; }

    if ( !source ) { *dest = NULL; return 1; }  /* source est vide */

    if ( !(*dest = alloue(source->nom)) ) { return 0; }  /* allocation mal passe */

    if ( !copie(&((*dest)->left), source->left) || !copie(&((*dest)->right), source->right) ) {
        liberer_arbre(dest);
        *dest = NULL;
        return 0;
    }
    return 1;
}


Arbre arbre_de_fichier(const char *path)
{
    FILE *fptr = fopen(path, "r");
    if (!fptr) { return NULL; }

    Arbre arbre = construire_arbre(fptr);
    fclose(fptr);
    return arbre;
}



int expansion(Arbre *dest, Arbre source)
{
    if (!dest) { return 1; }
    if (!source || !*dest) return 1;

    int left = expansion(&((*dest)->left), source);
    int right = expansion(&((*dest)->right), source);

    if ( strcmp((*dest)->nom, source->nom) == 0 ) {

        Arbre source_copie = NULL;
        Arbre sous_arbre_gauche = NULL;
        Arbre sous_arbre_droite = NULL;

        /* si n'a pas reussi de copier la greffe de source sur source_copie*/
        if ( !copie(&source_copie, source) ) { 
            fprintf(stderr, "Pas reussi de copier arbre source");
            return 0;
        }

        /* si n'a pas reussi de copier des sous arbres de A (s'ils existent) */
        if ( !copie(&sous_arbre_gauche, (*dest)->left) ) {
            fprintf(stderr, "Pas reussi de copier des sous arbres de *dest");
            //liberer_arbre(&source_copie);
            return 0;
        }

        if ( !copie(&sous_arbre_droite, (*dest)->right) ) {
            fprintf(stderr, "Pas reussi de copier des sous arbres de *dest");
            //liberer_arbre(&source_copie);
            //liberer_arbre(&sous_arbre_gauche);
            return 0;
        }


        /* On effectue l'ajout des sous arbres de *dest a copie de source */
        ajout_feuilles(&source_copie, sous_arbre_gauche, sous_arbre_droite);
        *dest = source_copie;
        return 1;
    }
    return left && right;
}



Arbre faire_greffe(const char *path_un , const char *path_deux)
{
    Arbre dest = arbre_de_fichier(path_un); 
    Arbre source = arbre_de_fichier(path_deux);

    if (!expansion(&dest, source)) { fprintf(stderr, "La greffe n'est pas reussite\n"); }

    if (source) { liberer_arbre(&source); } /* on n'a plus besoin d'arbre source */

    return dest;
}