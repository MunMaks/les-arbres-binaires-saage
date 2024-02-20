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


int len_string(const char *mot)
{
    int i = 0;
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


int hauteur(const Arbre arbre)
{
    if (! arbre) return -1;
    return 1 + MAX( hauteur(arbre->left), 
                    hauteur(arbre->right) );
}


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


/* modifier */
/* permet de gerer toute la memoire allouee */
void liberer_arbre(Arbre *arbre)
{
    if (!*arbre) { return; }
    liberer_arbre(&((*arbre)->left));
    liberer_arbre(&((*arbre)->right));
    free((*arbre)->nom);    /* la memeoire de char * */
    free(*arbre);           /* la memeoire de Noeud * */
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



/********************************************************/
/*                                                      */
/*                        ARBRES                        */
/*                                                      */
/********************************************************/
/* modifier */
Arbre construire_arbre(FILE *fichier) {
    Arbre noeud = NULL;
    char buffer[MAX_SIZE];
    char *nom_noeud = NULL, *fin_nom_noeud = NULL;

    /* les valeurs */
    if ( !fgets(buffer, MAX_SIZE, fichier) ) { return NULL; }

    nom_noeud = recherche_lettre(buffer, ':');
    if (!nom_noeud) { return NULL; }
    nom_noeud += 2;   /* passer ': ' */

    fin_nom_noeud = recherche_lettre(nom_noeud, '\n');
    if (!fin_nom_noeud) { return NULL; }
    *fin_nom_noeud = '\0';

    noeud = alloue(nom_noeud);


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

    /* On va entrer dans ce if, ssi allocation mal passe */
    if ( !copie( &(*dest)->left, source->left ) || !copie( &(*dest)->right, source->right ) ) {

        return 0;   /* Il faut pas oublier de liberer la memoire si copie renvoie 0 */
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

/* modifier */
/* Cette fonction ajoute left et right pour chaque feuilles de l'arbre */
void ajout_feuilles(Arbre *arbre, Noeud *left, Noeud *right)
{
    if (!*arbre) { return; }

    ajout_feuilles(&(*arbre)->left, left, right);
    ajout_feuilles(&(*arbre)->right, left, right);

    if ( !(*arbre)->left ) { (*arbre)->left = left; }
    if ( !(*arbre)->right ) { (*arbre)->right = right; }
}


/* modifier */
int expansion(Arbre *dest, Arbre source)
{
    int left = 0, right = 0;
    if (!dest) { return 1; }
    if (!source || !*dest) return 1;

    left = expansion(&((*dest)->left), source);
    right = expansion(&((*dest)->right), source);

    if ( comparer_chaines((*dest)->nom, source->nom) == 1 ) {

        Arbre source_copie = NULL, sous_arbre_gauche = NULL, sous_arbre_droite = NULL;

        /* si n'a pas reussi de copier la greffe de source sur source_copie*/
        if ( !copie(&source_copie, source) ) {
            fprintf(stderr, "Pas reussi de copier arbre source");
            if (source_copie) { liberer_arbre(&source_copie); }
            return 0;
        }

        /* si n'a pas reussi de copier des sous arbres de *dest (s'ils existent) */
        if ( !copie(&sous_arbre_gauche, (*dest)->left) ) {
            fprintf(stderr, "Pas reussi de copier des sous arbres de *dest");
            if (source_copie) { liberer_arbre(&source_copie); }
            if (sous_arbre_gauche) { liberer_arbre(&sous_arbre_gauche); }
            return 0;
        }

        /* si n'a pas reussi de copier des sous arbres de *dest (s'ils existent) */
        if ( !copie(&sous_arbre_droite, (*dest)->right) ) {
            fprintf(stderr, "Pas reussi de copier des sous arbres de *dest");
            if (source_copie) { liberer_arbre(&source_copie); }
            if (sous_arbre_gauche) { liberer_arbre(&sous_arbre_gauche); }
            if (sous_arbre_droite) { liberer_arbre(&sous_arbre_droite); }
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



uint est_meme_arbre(Arbre arbre_un, Arbre arbre_deux) {
    if ( !arbre_un && !arbre_deux ) return 1;
    else if ( !arbre_un  || !arbre_deux ) return 0;

    return comparer_chaines(arbre_un->nom, arbre_deux->nom) && 
            (est_meme_arbre(arbre_un->left, arbre_deux->left) && 
             est_meme_arbre(arbre_un->right, arbre_deux->right));
}


/* modifie */
void write_file_saage(FILE *fptr, Arbre arbre, uint count_tab)
{
    if (!arbre) { return; }

    /* les valeurs */
    ajout_tabulation(fptr, count_tab);
    fprintf(fptr, "Valeur : %s\n", arbre->nom);

    /* les sous-arbres gauches */
    ajout_tabulation(fptr, count_tab);
    fprintf(fptr, (arbre->left) ? ("Gauche : \n") : ("Gauche : NULL\n"));
    write_file_saage(fptr, arbre->left, count_tab + 1);

    /* les sous-arbres droites */
    ajout_tabulation(fptr, count_tab);
    fprintf(fptr, (arbre->right) ? ("Droite : \n") : ("Droite : NULL\n"));
    write_file_saage(fptr, arbre->right, count_tab + 1);
}

/* modifier */
Arbre arbre_de_fichier(const char *path)
{
    Arbre arbre = NULL;
    FILE *fptr = fopen(path, "r");
    if (!fptr) {
        fprintf(stderr, "Erreur d'ouverture du fichier.saage: %s\n", strerror(errno));
        return NULL; }

    arbre = construire_arbre(fptr);
    fclose(fptr);
    return arbre;
}

/* modifie */
Arbre faire_greffe(const char *path_un , const char *path_deux)
{
    Arbre dest = arbre_de_fichier(path_un); 
    Arbre source = arbre_de_fichier(path_deux);

    if ( expansion(&dest, source) ) {
        liberer_arbre(&source);
        return dest;
    }

    fprintf(stderr, "Expansion a mal passe, la memoire ...\n");
    return NULL;
}



/* cree */
uint creer_file_saage(Arbre arbre, const char *path_create)
{
    FILE *fptr_res = NULL;
    uint count_tab = 0;
    if (!arbre) { return 0; }   /* Arbre est NULL, rien a faire*/

    fptr_res = fopen(path_create, "w");
    if (!fptr_res) {
        fprintf(stderr, "Erreur d'ouverture du %s: %s\n", path_create,strerror(errno));
        return 1;
    }

    write_file_saage(fptr_res, arbre, count_tab);
    fclose(fptr_res);

    return 1;
}





/* gcc -o main -std=c17 -pedantic -Wall -Wfatal-errors -O3 test.c */
/* gcc -o main -std=c17 -pedantic -Wall -Wfatal-errors -ansi -O3 test.c */
int main(int argc, char *argv[])
{
    Arbre res = NULL, apres_greffe;
    char *path_un =     "exemples/A_3.saage";                       /* source_un */
    char *path_deux =   "exemples/D.saage";                         /* source_deux */
    char *path_create = "exemples/created.saage";                   /* notre resultat */
    char *path_greffe = "exemples/A_3_apres_greffe_de_D.saage";     /* resultat attendu */

    res = faire_greffe(path_un, path_deux);
    if (!res) { return 1; } /* car greffe a rate */

    apres_greffe = arbre_de_fichier(path_greffe);

    if (!creer_file_saage(res, path_create)){
        fprintf(stderr, "N'a pas reussi a creer %s\n", path_create);
        return 1;
    }

    printf("La meme arbre: %u\n", est_meme_arbre(res, apres_greffe));

    /*
    affiche(res);
    affiche(apres_greffe);
    */
    liberer_arbre(&res);
    liberer_arbre(&apres_greffe);
    return 0;
}
