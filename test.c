#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdint.h>

#include <stdarg.h>
#include <ctype.h>
#include <stdint.h>
#include <errno.h>

/* Macros de comparaisons */
#define MAX(x, y) (( (x) > (y) ) ? (x) : (y) )
#define MIN(x, y) (( (x) < (y) ) ? (x) : (y) )

#define MAX_SIZE 4096
typedef unsigned int uint;


typedef struct _noeud {
    char *nom;
    struct _noeud *left, *right;
} Noeud, *Arbre;



int len(const char *mot)
{
    int i = 0;
    while (*(mot + i)) ++i;
    return i; 
}


char* dupliquer_string(const char *source)
{
    char *destination = NULL, *temp_dest = NULL;
    const char *temp_src = NULL;

    if ( !source ) return NULL;     /* source est vide */

    /* pas de memoire... */
    if ( !(destination = malloc((len(source) + 1) * sizeof *destination)) ) return NULL;

    temp_dest = destination;
    temp_src = source;

    while (*temp_src) { *temp_dest++ = *temp_src++; }

    *temp_dest = '\0';

    return destination;
}



Arbre alloue(const char *chaine)
{
    Arbre noeud = NULL;
    if (! (noeud = malloc(sizeof *noeud)) ) return NULL;

    noeud->nom = dupliquer_string(chaine);  /* strdup() */
    if ( !noeud->nom ) { free(noeud); return NULL; }  /* pas de memoire... */

    noeud->right = noeud->left = NULL;
    return noeud;
}



int hauteur(const Arbre arbre)
{
    if (! arbre) return -1;
    return 1 + MAX( hauteur(arbre->left), 
                    hauteur(arbre->right) );
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





Arbre construire_arbre(FILE *fichier) {
    Arbre noeud = NULL;
    char buffer[MAX_SIZE];
    char *debut_valeur = NULL, *fin_valeur = NULL;
    if ( !fgets(buffer, MAX_SIZE, fichier) ) { return NULL; }

    debut_valeur = recherche_lettre(buffer, ':');
    if (!debut_valeur) { return NULL; }
    debut_valeur += 2;   /* passer ': ' */

    fin_valeur = recherche_lettre(debut_valeur, '\n');
    if (!fin_valeur) { return NULL; }
    *fin_valeur = '\0';

    noeud = alloue(debut_valeur);


    /* les sous-arbres gauches */
    if ( !fgets(buffer, MAX_SIZE, fichier) ) { return NULL; }

    if ( recherche_substring(buffer, "Gauche :") ) {

        if ( recherche_substring(buffer, "NULL") ) noeud->left = NULL;
        else noeud->left = construire_arbre(fichier);
    }


    /* les sous-arbres droites */
    if ( !fgets(buffer, MAX_SIZE, fichier) ) { return NULL; }

    if ( recherche_substring(buffer, "Droite :") ) {

        if ( recherche_substring(buffer, "NULL") ) noeud->right = NULL;
        else noeud->right = construire_arbre(fichier);
    }

    return noeud;
}



/* permet de gerer toute la memoire allouee */
void liberer_arbre(Arbre *arbre)
{
    if (*arbre) {
        liberer_arbre(&(*arbre)->left);
        liberer_arbre(&(*arbre)->right);
        free((*arbre)->nom);    /* la memeoire de char * */
        free(*arbre);           /* la memeoire de Noeud * */
        *arbre = NULL;
    }
}



Arbre cree_A_1(void)
{
    Arbre arbre = NULL;
    FILE *fptr = fopen("exemples/A_1.saage", "r");
    if (!fptr) {
        fprintf(stderr, "Error opening file A_1.saage: %s\n", strerror(errno));
        return NULL;
    }

    arbre = construire_arbre(fptr);

    fclose(fptr);
    return arbre;
}



Arbre cree_A_2(void)
{
    Arbre arbre = NULL;
    FILE *fptr = fopen("exemples/A_2.saage", "r");
    if (!fptr) {
        fprintf(stderr, "Error opening file A_2.saage: %s\n", strerror(errno));
        return NULL;
    }
    arbre = construire_arbre(fptr);
    return arbre;
}



Arbre cree_A_3(void)
{
    Arbre arbre = NULL;
    FILE *fptr = fopen("exemples/A_3.saage", "r");
    if (!fptr) {
        fprintf(stderr, "Error opening file A_3.saage: %s\n", strerror(errno));
        return NULL;
    }
    arbre = construire_arbre(fptr);
    return arbre;
}


/* l'Ajout BFS et PAS ABR */
void BFS_ajoute_arbre(Arbre *arbre, char *chaine)
{
    Arbre file[MAX_SIZE];
    int debut = 0, fin = 0;
    if (!*arbre) {
        *arbre = alloue(chaine);
        return;
    }

    file[fin++] = *arbre;   /* Ajoute la racine dans la file */

    while (debut != fin) {
        Arbre noeud = file[debut++];    /* Récupère le premier élément de la file */
        if (!noeud->left) {
            noeud->left = alloue(chaine);
            return;
        } else if (!noeud->right) {
            noeud->right = alloue(chaine);
            return;
        } else {
            file[fin++] = noeud->left;
            file[fin++] = noeud->right;
        }
    }
}



void affiche(Arbre arbre)
{
    if (!arbre) return;
    printf("%s \n", arbre->nom);
    affiche(arbre->left);
    affiche(arbre->right);
}




/*  fonction copie dans *dest l’arbre stocke dans source.
    1 - succès
    0 - echec */
int copie(Arbre *dest, Arbre source)
{
    if ( !source ) { *dest = NULL; return 1; }  /* source est vide */

    if ( !(*dest = alloue(source->nom)) ) { return 0; }  /* allocation mal passe */

    if ( !copie( &(*dest)->left, source->left ) || 
         !copie( &(*dest)->right, source->right ) ) {
        liberer_arbre(dest);
        return 0;
    }
    return 1;
}



/*  1 si deux chaînes sont identiques
    0 sinon */
int comparer_chaines(const char *string_un, const char *string_deux) {
    while (*string_un && *string_deux) {
        if (*string_un != *string_deux) return 0;
        ++string_un;
        ++string_deux;
    }
    return (!*string_un && !*string_deux) ? (1) : (0);
    
}



void ajout_feuilles(Arbre *arbre, Noeud *left, Noeud *right)
{
    if (!*arbre) { return; }

    ajout_feuilles(&(*arbre)->left, left, right);
    ajout_feuilles(&(*arbre)->right, left, right);

    if (!(*arbre)->left && !(*arbre)->right) {
        (*arbre)->left = left;
        (*arbre)->right = right;
    }
}



int expansion(Arbre *dest, Arbre source)
{
    int left = 0, right = 0;

    if (!source || !*dest) return 1;

    left = expansion(&(*dest)->left, source);
    right = expansion(&(*dest)->right, source);

    if ( comparer_chaines((*dest)->nom, source->nom) ) {

        Arbre source_copie = NULL, sous_arbre_gauche = NULL, sous_arbre_droite = NULL;

        /* si n'a pas reussi de copier la greffe de source sur source_copie*/
        if ( !copie(&source_copie, source) ) { fprintf(stderr, "Pas reussi de copier arbre source"); return 0; }

        /* si n'a pas reussi de copier des sous arbres de A (s'ils existent) */
        if ( !copie(&sous_arbre_gauche, (*dest)->left) || 
             !copie(&sous_arbre_droite, (*dest)->right) ) {
            fprintf(stderr, "Pas reussi de copier des sous arbres de *dest");
            liberer_arbre(&source_copie);
            liberer_arbre(&sous_arbre_gauche);
            liberer_arbre(&sous_arbre_droite);
            return 0;
        }

        /* On effectue l'ajout des sous arbres de *dest a copie de source */
        ajout_feuilles(&source_copie, sous_arbre_gauche, sous_arbre_droite);
        *dest = source_copie;
        return 1;
    }
    return left && right;
}



void ajout_tabulation(FILE *fptr, uint count_tab)
{
    uint i;
    /* il faut discuter, soit 4 espaces, soit 1 tabulation */
    for (i = 0; i < count_tab; ++i) fprintf(fptr, "    ");    /* fprintf(fptr, "\t"); */
}




void creer_file_saage(FILE *fptr, Arbre arbre, uint count_tab)
{
    if (!arbre) { return; }

    /* les valeurs */
    ajout_tabulation(fptr, count_tab);
    fprintf(fptr, "Valeur : %s\n", arbre->nom);

    /* les sous-arbres gauches */
    ajout_tabulation(fptr, count_tab);
    fprintf(fptr, (arbre->left) ? ("Gauche : \n") : ("Gauche : NULL\n"));
    creer_file_saage(fptr, arbre->left, count_tab + 1);

    /* les sous-arbres droites */
    ajout_tabulation(fptr, count_tab);
    fprintf(fptr, (arbre->right) ? ("Droite : \n") : ("Droite : NULL\n"));
    creer_file_saage(fptr, arbre->right, count_tab + 1);
}





Arbre faire_greffe(const char *path_un , const char *path_deux)
{
    Arbre dest = NULL, source = NULL;

    FILE *fptr_un = fopen(path_un, "r");
    if (!fptr_un) {
        fprintf(stderr, "Erreur d'ouverture du fichier\n");
        return NULL;
    }
    dest = construire_arbre(fptr_un);
    fclose(fptr_un);


    FILE *fptr_deux = fopen(path_deux, "r");
    if (!fptr_deux) {
        fprintf(stderr, "Erreur d'ouverture du fichier\n");
        return NULL;
    }
    source = construire_arbre(fptr_deux);
    fclose(fptr_deux);


    if (!expansion(&dest, source)) {
        fprintf(stderr, "La greffe n'est pas reussite\n");
        return NULL;
    }
    liberer_arbre(&source);     /* on n'a plus besoin d'arbre source */

    return dest;
}




Arbre test_build(const char *path)
{
    FILE *fptr = fopen(path, "r");
    if (!fptr) { return NULL; }

    Arbre arbre = construire_arbre(fptr);
    fclose(fptr);
    return arbre;
}




/* gcc -o main -std=c17 -pedantic -Wall -Wfatal-errors -ansi -O3 test.c */
int main(int argc, char *argv[])
{
    char *path_un =     "exemples/A_3.saage";
    char *path_deux =   "exemples/D.saage";
    char *path_create = "exemples/created.saage";

    char *path_greffe = "exemples/A_3_apres_greffe_de_D.saage";

    Arbre res = faire_greffe(path_un, path_deux);
    Arbre apres_greffe = test_build(path_greffe);

    FILE *fptr_res = fopen(path_create, "w");
    if (!fptr_res) {
        fprintf(stderr, "Erreur d'ouverture du fichier\n");
        return 1;
    }

    uint count_tab = 0;
    creer_file_saage(fptr_res, res, count_tab);
    fclose(fptr_res);
    // affiche(res);
    // affiche(apres_greffe);
    liberer_arbre(&res);
    liberer_arbre(&apres_greffe);
    return 0;
}
