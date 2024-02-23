#include "../include/arbres_binaires.h"



void detruire_noeud(Noeud *noeud)
{
    if (noeud) {
        if (noeud->nom) { free(noeud->nom); }
        free(noeud);
    }
}


void liberer_arbre(Arbre *arbre)
{
    if (!*arbre) { return ; }

    if ((*arbre)->left) { liberer_arbre(&((*arbre)->left)); }

    if ((*arbre)->right) { liberer_arbre(&((*arbre)->right)); }

    detruire_noeud(*arbre);
}


/********************************************************/
/*                                                      */
/*                       STRINGS                        */
/*                                                      */
/********************************************************/


/* la longuer d'une chaine de caracteres*/
uint len_string(const char *mot)
{
    uint i = 0;
    while (*(mot + i)) ++i;
    return i; 
}



/*  cette fonction recherche la premiere occurrence du caractere passe
    similaire a strchr() de <string.h> */
char *recherche_lettre(const char *source, char lettre)
{
    while (*source) {
        if (*source == lettre) { return (char *) source; }
        ++source;
    }
    return NULL;
}



/*  cette fonction recherche la premiere occurrence du substring passe
    similaire a strstr() de <string.h> */
char* recherche_substring(const char* fullString, const char* substring)
{
    if ( !*substring ) /* substring est vide */
        return (char*) fullString;

    while ( *fullString ) {
        const char *f = fullString;
        const char *s = substring;

        /* la première occurrence de substring */
        while ( *s && *f == *s ) {
            f++;
            s++;
        }

        /* si le mot est trouve */
        if ( !*s ) { return (char*) fullString; }

        ++fullString; /* iteration */
    }
    return NULL;
}


/*  cette fonction alloue dynamiquement la memoire pour une chaine
    similaire a strdup() de <string.h> */
char* dupliquer_string(const char *source)
{
    char *destination = NULL, *temp_dest = NULL;
    const char *temp_src = NULL;

    if ( !source ) return NULL;     /* source est vide */

    /* pas de memoire... */
    if ( !(destination = malloc((len_string(source) + 1) * sizeof *destination)) ) return NULL;

    temp_dest = destination;
    temp_src = source;

    while (*temp_src) { *temp_dest++ = *temp_src++; }

    *temp_dest = '\0';

    return destination;
}



/*  1 si deux chaînes sont identiques
    0 sinon */
uint comparer_chaines(const char *string_un, const char *string_deux)
{
    while (*string_un && *string_deux) {
        if (*string_un != *string_deux) return 0;
        ++string_un;
        ++string_deux;
    }
    return (!*string_un && !*string_deux) ? (1) : (0);
}


/* cette fonction copie source dans dest */
void copie_chaine(char* dest, const char* source)
{
    while ((*dest++ = *source++)) { ; /* boucle vide */ } 
}



/* cette fonction concatene destination et source */
void concatenantion(char* dest, char* source)
{
    while (*dest) { dest++; }

    while ((*dest++ = *source++)) { ; /* boucle vide */ }
}


/********************************************************/
/*                                                      */
/*                        ARBRES                        */
/*                                                      */
/********************************************************/


Arbre alloue(const char *chaine)
{
    Arbre noeud = malloc(sizeof *noeud);
    if ( !noeud ) return NULL;

    noeud->nom = dupliquer_string(chaine);
    if ( !(noeud->nom) ) { free(noeud); return NULL; }

    noeud->left = NULL;
    noeud->right = NULL;
    return noeud;
}



Arbre construire_arbre(FILE *fptr)
{
    Arbre noeud = NULL;
    char buffer[MAX_SIZE];
    char *nom_noeud = NULL, *fin_nom_noeud = NULL;

    /* les valeurs */
    if ( !fgets(buffer, MAX_SIZE, fptr) ) { return NULL; }

    nom_noeud = recherche_lettre(buffer, ':');
    if (!nom_noeud) { return NULL; }
    nom_noeud += 2;   /* passer ': ' */

    fin_nom_noeud = recherche_lettre(nom_noeud, '\n');
    if (!fin_nom_noeud) { return NULL; }
    *fin_nom_noeud = '\0';

    noeud = alloue(nom_noeud);


    /* les sous-arbres gauches */
    if ( !fgets(buffer, MAX_SIZE, fptr) ) { return NULL; }

    if ( recherche_substring(buffer, "Gauche :") ) {

        if ( recherche_substring(buffer, "NULL") ) noeud->left = NULL;
        else noeud->left = construire_arbre(fptr);
    }


    /* les sous-arbres droites */
    if ( !fgets(buffer, MAX_SIZE, fptr) ) { return NULL; }

    if ( recherche_substring(buffer, "Droite :") ) {

        if ( recherche_substring(buffer, "NULL") ) noeud->right = NULL;
        else noeud->right = construire_arbre(fptr);
    }

    return noeud;
}


uint est_meme_arbre(Arbre arbre_un, Arbre arbre_deux) {
    if ( !arbre_un && !arbre_deux ) return 1;
    else if ( !arbre_un  || !arbre_deux ) return 0;

    return comparer_chaines(arbre_un->nom, arbre_deux->nom) && 
            (est_meme_arbre(arbre_un->left, arbre_deux->left) && 
             est_meme_arbre(arbre_un->right, arbre_deux->right));
}


uint creer_arbre(FILE *fptr, Arbre *arbre)
{
    char buffer[MAX_SIZE];
    char buffer_tmp[CHAR_SIZE];
    char *fin_nom = NULL;
    uint val = 0;
    uint first_time = 1;

    if ((fscanf(fptr, "%u", &val)) <= 0) { return 0; }

    if (!val) { *arbre = NULL; return 1; }

    /* prendre le nom de l'arbre */
    while (1) {
        if ((fscanf(fptr, "%s", buffer_tmp)) <= 0) { return 0; }

        if ((fin_nom = recherche_substring(buffer_tmp, "\\n"))) {  /* pour supprimer \n avec guillemet (") */
            *fin_nom = '\0';
            if (first_time) {
                copie_chaine(buffer, buffer_tmp + 1);
                --first_time;
            } else {
                concatenantion(buffer, buffer_tmp);
            }
            break;
        }
        if (first_time) {
            copie_chaine(buffer, buffer_tmp + 1);   /* pour passer le premier guillemet (") */
            --first_time; } 
        else {
            concatenantion(buffer, buffer_tmp);
        }
        concatenantion(buffer, " ");
    }


    if ( !(*arbre = alloue(buffer)) ) { return 0; }

    return creer_arbre(fptr, &((*arbre)->left)) &&
           creer_arbre(fptr, &((*arbre)->right));
}




void affiche_sur_stdout(const char *path_create)
{
    FILE *fptr_create = NULL;
    char ch;

    fptr_create = fopen(path_create, "r");

    if (!fptr_create) { return; }

    while ((ch = fgetc(fptr_create)) != EOF) { putchar(ch); }

    fclose(fptr_create);
    remove(path_create);
}
