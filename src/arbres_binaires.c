#include "../include/arbres_binaires.h"


/********************************************************/
/*                                                      */
/*                       STRINGS                        */
/*                                                      */
/********************************************************/


/* (const char *mot) */
uint len_string(char *mot)
{
    uint i = 0;
    while (*mot++) ++i;     /* (mot[i] != '\0') */
    return i;
}


/*  cette fonction recherche la premiere occurrence du caractere passe
    similaire a strchr() de <string.h> */
static char *recherche_lettre(char *source, char lettre)
{
    while (*source) {
        if (*source == lettre) { return source; }
        ++source;
    }
    return NULL;
}


/*  cette fonction recherche la premiere occurrence du substring passe
    similaire a strstr() de <string.h> */
/* on peut utiliser (static char *) */
char *recherche_substring(char* nom_complet, char* substring)
{
    char *chaine = NULL, *sous_chaine = NULL;
    if ( !*substring ) /* substring est vide */
        return nom_complet;

    while ( *nom_complet ) {
        chaine = nom_complet;
        sous_chaine = substring;

        /* la première occurrence de substring */
        while ( *sous_chaine && (*chaine == *sous_chaine) ) {
            chaine++;
            sous_chaine++;
        }

        if ( !(*sous_chaine) ) { return nom_complet; }   /* si le mot est trouve */

        ++nom_complet;
    }
    return NULL;
}


/*  1 si deux chaînes sont identiques
    0 sinon */
uint comparer_chaines(char *chaine_un, char *chaine_deux)
{
    while (*chaine_un && *chaine_deux) {
        if (*chaine_un != *chaine_deux) return 0;
        ++chaine_un;
        ++chaine_deux;
    }
    return ( !(*chaine_un) && !(*chaine_deux) ) ? (1) : (0);
}



static char *dupliquer_nom(char *source)
{
    char *destination = NULL, *temp_dest = NULL, *temp_source = NULL;

    if ( !source ) return NULL;     /* source est vide */
    
    if ( !(destination = malloc((len_string(source) + 1) * sizeof *destination)) )
        return NULL;    /* pas de memoire... */

    temp_dest = destination;
    temp_source = source;

    while (*temp_source) { *temp_dest++ = *temp_source++; }

    *temp_dest = '\0';

    return destination;
}


static void copie_chaine(char* dest, char* source)
{
    if ( !source ) { return; }
    while ( (*dest++ = *source++) ) { ; /* boucle vide */ } 
}


static void concatenantion(char* dest, char* source)
{
    if ( !source ) { return; }
    while ( *dest ) { dest++; }
    copie_chaine(dest, source);
}


void path_exemples(char *buffer, char *path)
{
    if ( !path ) return;

    if (recherche_substring(path, "exemples/")) {
        copie_chaine(buffer, path);
    } else {
        copie_chaine(buffer, "exemples/");
        concatenantion(buffer, path);
    }
}



/********************************************************/
/*                                                      */
/*                        ARBRES                        */
/*                                                      */
/********************************************************/


Noeud *alloue_noeud(char *chaine)
{
    Noeud *noeud = malloc(sizeof *noeud);
    if ( !noeud ) return NULL;

    noeud->nom = dupliquer_nom(chaine);  /* strdup() */
    if ( !(noeud->nom) ) { free(noeud); return NULL; }

    noeud->left = NULL;
    noeud->right = NULL;
    return noeud;
}


void liberer_arbre(Arbre *arbre)
{
    if ( !*arbre ) { return; }

    if ( (*arbre)->left ) { liberer_arbre(&((*arbre)->left)); }

    if ( (*arbre)->right ) { liberer_arbre(&((*arbre)->right)); }

    /* suppression du noeud et son nom */
    if ( *arbre ) { 
        if ( (*arbre)->nom ) { free((*arbre)->nom); } 
        free(*arbre);
        *arbre = NULL;
    }
}


static int arbre_de_fichier_aux(FILE *fptr, Arbre *arbre)
{
    int left = 0, right = 0;
    char buffer[MAX_SIZE];
    char *nom_noeud = NULL, *fin_nom_noeud = NULL;


    /* les valeurs */
    if ( !fgets(buffer, MAX_SIZE, fptr) ) { return 0; }

    nom_noeud = recherche_lettre(buffer, ':');
    if ( !nom_noeud ) { return 0; }
    nom_noeud += 2;   /* passer ': ' */

    fin_nom_noeud = recherche_lettre(nom_noeud, '\n');
    if ( !fin_nom_noeud ) { return 0; }
    *fin_nom_noeud = '\0';

    if ( !(*arbre = alloue_noeud(nom_noeud)) ) { return 0; }


    /* les sous-arbres gauches */
    if ( !fgets(buffer, MAX_SIZE, fptr) ) { return 0; }

    if ( recherche_substring(buffer, "Gauche :") ) {

        if ( recherche_substring(buffer, "NULL") ) { (*arbre)->left = NULL; left = 1; }
        else { left = arbre_de_fichier_aux(fptr, &((*arbre)->left)); }
    }


    /* les sous-arbres droites */
    if ( !fgets(buffer, MAX_SIZE, fptr) ) { return 0; }

    if ( recherche_substring(buffer, "Droite :") ) {

        if ( recherche_substring(buffer, "NULL") ) { (*arbre)->right = NULL; right = 1; }
        else { right = arbre_de_fichier_aux(fptr, &((*arbre)->right)); }
    }

    return left && right;
}


Arbre arbre_de_fichier(char *path)
{
    Arbre arbre = NULL;
    FILE *fptr = fopen(path, "r");
    if ( !fptr ) {
        fprintf(stderr, "Erreur d'ouverture de %s: %s\n", path, strerror(errno));
        return NULL;
    }
    if ( !arbre_de_fichier_aux(fptr, &arbre) ) {
        fprintf(stderr, "Construction a mal passe, veuillez reessayer\n");
        if (arbre) {
            liberer_arbre(&arbre);
            arbre = NULL;
        }
    }
    fclose(fptr);
    return arbre;
}


uint est_meme_arbre(Arbre arbre_un, Arbre arbre_deux)
{
    if ( !arbre_un && !arbre_deux ) return 1;
    else if ( !arbre_un  || !arbre_deux ) return 0;

    return comparer_chaines(arbre_un->nom, arbre_deux->nom) && 
            (est_meme_arbre(arbre_un->left, arbre_deux->left) && 
             est_meme_arbre(arbre_un->right, arbre_deux->right));
}





Arbre cree_A_1(void)
{
    Arbre arbre = arbre_de_fichier("exemples/A_1.saage");
    return arbre;
}



Arbre cree_A_2(void)
{
    Arbre arbre = arbre_de_fichier("exemples/A_2.saage");
    return arbre;
}


Arbre cree_A_3(void)
{
    Arbre arbre = arbre_de_fichier("exemples/A_3.saage");;

    return arbre;
}
