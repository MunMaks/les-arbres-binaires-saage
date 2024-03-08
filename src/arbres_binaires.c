#include "../include/arbres_binaires.h"


/********************************************************/
/*                                                      */
/*                       STRINGS                        */
/*                                                      */
/********************************************************/


/**
 * @brief recherche la premiere occurrence du caractere passe
 * @return le pointeur sur ce lettre dans source (NULL sinon)
*/
static char *recherche_lettre(char *source, char lettre)
{
    while (*source) {
        if (*source == lettre) { return source; }
        ++source;
    }
    return NULL;
}

/**
 * @brief recherche la premiere occurrence du substring passe, similaire a strstr() de <string.h>
 * @return le pointeur sur la premier occurrence dans source (NULL sinon)
 */
static char *recherche_substring(char* nom_complet, char* substring)
{
    char *chaine = NULL, *sous_chaine = NULL;
    if ( !*substring )      /* substring est vide */
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


/**
 * @brief renvoie la copie de la source (en utilisant malloc)
 * 
 * @param source 
 * @return char* 
 */
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


/**
 * @brief cette fonction copie chaine source dans chaine dest
 * 
 * @param dest 
 * @param source 
 */
static void copie_chaine(char* dest, char* source)
{
    if ( !source ) { return; }
    while ( (*dest++ = *source++) ) { ; /* boucle vide */ } 
}


/**
 * @brief effectue la concatenantion de destination et source
 * 
 * @param dest 
 * @param source 
 */
static void concatenantion(char* dest, char* source)
{
    if ( !source ) { return; }
    while ( *dest ) { dest++; }
    copie_chaine(dest, source);
}



uint len_string(char *mot)
{
    uint i = 0;
    while (*mot++) ++i;
    return i;
}



uint comparer_chaines(char *chaine_un, char *chaine_deux)
{
    while (*chaine_un && *chaine_deux) {
        if (*chaine_un != *chaine_deux) return 0;
        ++chaine_un;
        ++chaine_deux;
    }
    return ( !(*chaine_un) && !(*chaine_deux) ) ? (1) : (0);
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
    Noeud *noeud = NULL;
    if ( !(noeud = malloc(sizeof *noeud)) ) return NULL;

    noeud->val = dupliquer_nom(chaine);
    if ( !(noeud->val) ) { free(noeud); return NULL; }

    noeud->fg = NULL;
    noeud->fd = NULL;
    return noeud;
}


void liberer_arbre(Arbre *arbre)
{
    if ( !*arbre ) { return; }

    if ( (*arbre)->fg ) { liberer_arbre(&((*arbre)->fg)); }

    if ( (*arbre)->fd ) { liberer_arbre(&((*arbre)->fd)); }

    /* suppression du noeud et son nom */
    if ( *arbre ) { 
        if ( (*arbre)->val ) { free((*arbre)->val); } 
        free(*arbre);
        *arbre = NULL;
    }
}


/**
 * @brief constuire arbre d'apres le fichier .saage (la fonciton auxiliaire)
 * @return 1 si tout va bien et 0 sinon 
 */
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

        if ( recherche_substring(buffer, "NULL") ) { (*arbre)->fg = NULL; left = 1; }
        else { left = arbre_de_fichier_aux(fptr, &((*arbre)->fg)); }
    }


    /* les sous-arbres droites */
    if ( !fgets(buffer, MAX_SIZE, fptr) ) { return 0; }

    if ( recherche_substring(buffer, "Droite :") ) {

        if ( recherche_substring(buffer, "NULL") ) { (*arbre)->fd = NULL; right = 1; }
        else { right = arbre_de_fichier_aux(fptr, &((*arbre)->fd)); }
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
    if ( fclose(fptr) ){
        fprintf(stderr, "la fermeture de fichier %s a echoue \n", path);
    }
    return arbre;
}



int construit_arbre(Arbre *arbre)
{
    char buffer[MAX_SIZE];
    uint val = 0, len = 0;

    if ((scanf("%u", &val)) <= 0) { return 0; }

    if ( !val ) { *arbre = NULL; return 1; }

    if ( !fgets(buffer, MAX_SIZE, stdin) ) { return 0; }

    len = len_string(buffer);   /* strlen() */
    if (len > 0 && buffer[len - 1] == '\n') { buffer[len - 1] = '\0'; }

    /* ici buffer+1 car on veut passer premier espace*/
    if ( !(*arbre = alloue_noeud(buffer + 1)) ) { return 0; }   /* allouer la memoire pour l'arbre */

    return construit_arbre(&((*arbre)->fg)) && construit_arbre(&((*arbre)->fd));
}


uint est_meme_arbre(Arbre arbre_un, Arbre arbre_deux)
{
    if ( !arbre_un && !arbre_deux ) return 1;
    else if ( !arbre_un  || !arbre_deux ) return 0;

    return comparer_chaines(arbre_un->val, arbre_deux->val) && 
            (est_meme_arbre(arbre_un->fg, arbre_deux->fg) && 
             est_meme_arbre(arbre_un->fd, arbre_deux->fd));
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
