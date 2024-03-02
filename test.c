#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <assert.h>
#include <stdarg.h>

/* Macros de comparaisons 
#define MAX(x, y) (( (x) > (y) ) ? (x) : (y) )
#define MIN(x, y) (( (x) < (y) ) ? (x) : (y) )
*/

#define MAX_SIZE 4096
#define CHAR_SIZE 256
typedef unsigned int uint; 


typedef struct _noeud {
    char *nom;
    struct _noeud *left, *right;
} Noeud, *Arbre;



/* DOT fonctions */
void ecrire_debut(FILE *fptr)
{
    fprintf(fptr, "digraph arbre{\n\tnode [ shape = record, height = .1]\n\tedge [ tailclip = false , arrowtail = dot, dir = both];\n\n");
}


void ecrire_arbre(FILE *fptr, Arbre arbre)
{   
    if (!arbre) { return; }

    fprintf(fptr,"\tn%p [label=\"<gauche> | <valeur> %s | <droit>\"];\n", (void *) arbre, arbre->nom);

    if (arbre->left) {
        fprintf(fptr, "\tn%p:gauche:c -> n%p:valeur;\n", (void *) arbre, (void *) arbre->left);
        ecrire_arbre(fptr, arbre->left);
    }

    if (arbre->right) {
        fprintf(fptr, "\tn%p:droit:c -> n%p:valeur;\n", (void *) arbre, (void *) arbre->right);
        ecrire_arbre(fptr, arbre->right);
    }
}

void ecrire_fin(FILE *fptr) { fprintf(fptr, "}"); }


void dessine(FILE *fptr, Arbre arbre)
{
    ecrire_debut(fptr);
    ecrire_arbre(fptr, arbre);
    ecrire_fin(fptr);
}



void visualisation_dot(Arbre arbre)
{
    FILE *fptr = NULL;
    if (!arbre) { return; }

    fptr = fopen("exemples/visualise.dot", "w");

    if (!fptr) { printf("Erreur à l'ouverture du fichier visualise.dot"); return; }

    else { dessine(fptr, arbre); }

    fclose(fptr);
    system("dot -Tpdf exemples/visualise.dot -o exemples/visualise.pdf");
    system("evince exemples/visualise.pdf &");
}



void affiche_sur_stdout(char *path_create)
{
    FILE *fptr = NULL;
    char buffer[MAX_SIZE];
    fptr = fopen(path_create, "r");

    if (!fptr) { 
        fprintf(stderr, "Erreur d'ouverture du %s: %s\n", path_create, strerror(errno));
        return;
    }

    while (fgets(buffer, MAX_SIZE, fptr)) { fputs(buffer, stdout); }

    fclose(fptr);
}



uint len_string(char *mot)
{
    uint i = 0;
    while (*(mot + i)) ++i;
    return i; 
}


/*  cette fonction recherche la premiere occurrence du caractere passe
    similaire a strchr() de <string.h> */
char *recherche_lettre(char *source, char lettre)
{
    while (*source) {
        if (*source == lettre) { return source; }
        ++source;
    }
    return NULL;
}


/*  cette fonction recherche la premiere occurrence du substring passe
    similaire a strstr() de <string.h> */
char *recherche_substring(char* nom_complet, char* substring)
{
    char *f = NULL, *s = NULL;
    if ( !*substring ) /* substring est vide */
        return nom_complet;

    while ( *nom_complet ) {
        f = nom_complet;
        s = substring;

        /* la première occurrence de substring */
        while ( *s && *f == *s ) {
            f++;
            s++;
        }

        if ( !*s ) { return nom_complet; }   /* si le mot est trouve */

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
    return (!*chaine_un && !*chaine_deux) ? (1) : (0);
}



char *dupliquer_nom(char *source)
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


void copie_chaine(char* dest, char* source)
{
    if (!source) { return; }
    while ((*dest++ = *source++)) { ; /* boucle vide */ } 
}


void concatenantion(char* dest, char* source)
{
    if (!source) { return; }
    while (*dest) { dest++; }
    copie_chaine(dest, source);
}


void path_exemples(char *buffer, char *path)
{
    if (!path) return;

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
    if (!*arbre) { return ; }

    if ((*arbre)->left) { liberer_arbre(&((*arbre)->left)); }

    if ((*arbre)->right) { liberer_arbre(&((*arbre)->right)); }

    /* suppression du noeud et son nom */
    if (*arbre) { if ((*arbre)->nom) { free((*arbre)->nom); } free(*arbre); }
}


int construire_arbre(FILE *fptr, Arbre *arbre)
{
    int left = 0, right = 0;
    char buffer[MAX_SIZE];
    char *nom_noeud = NULL, *fin_nom_noeud = NULL;


    /* les valeurs */
    if ( !fgets(buffer, MAX_SIZE, fptr) ) { return 0; }

    nom_noeud = recherche_lettre(buffer, ':');
    if (!nom_noeud) { return 0; }
    nom_noeud += 2;   /* passer ': ' */

    fin_nom_noeud = recherche_lettre(nom_noeud, '\n');
    if (!fin_nom_noeud) { return 0; }
    *fin_nom_noeud = '\0';

    if (!(*arbre = alloue_noeud(nom_noeud))) { return 0; }


    /* les sous-arbres gauches */
    if ( !fgets(buffer, MAX_SIZE, fptr) ) { return 0; }

    if ( recherche_substring(buffer, "Gauche :") ) {

        if ( recherche_substring(buffer, "NULL") ) { (*arbre)->left = NULL; left = 1; }
        else { left = construire_arbre(fptr, &((*arbre)->left)); }
    }


    /* les sous-arbres droites */
    if ( !fgets(buffer, MAX_SIZE, fptr) ) { return 0; }

    if ( recherche_substring(buffer, "Droite :") ) {

        if ( recherche_substring(buffer, "NULL") ) { (*arbre)->right = NULL; right = 1; }
        else { right = construire_arbre(fptr, &((*arbre)->right)); }
    }

    return left && right;
}


Arbre arbre_de_fichier(char *path)
{
    Arbre arbre = NULL;
    FILE *fptr = fopen(path, "r");
    if (!fptr) {
        fprintf(stderr, "Erreur d'ouverture du %s: %s\n", path, strerror(errno));
        return NULL;
    }
    if ( !construire_arbre(fptr, &arbre)) {
        if (arbre) {
            fprintf(stderr, "Construction a mal passe, veuillez reessayer\n");
            liberer_arbre(&arbre);
            arbre = NULL;
        }
    }
    fclose(fptr);
    return arbre;
}


/* la version de la fonction deserialise() mais plus parlante */
int deserialise(char *path, Arbre *arbre)
{
    if (!path) { return 0; }

    *arbre = arbre_de_fichier(path);

    return (*arbre) ? (1) : (0);
}


Arbre cree_A_1(void)
{
    Arbre arbre = NULL;
    char *path = "exemples/A_1.saage";
    arbre = arbre_de_fichier(path);
    return arbre;
}



Arbre cree_A_2(void)
{
    Arbre arbre = NULL;
    char *path = "exemples/A_2.saage";
    arbre = arbre_de_fichier(path);
    return arbre;
}


Arbre cree_A_3(void)
{
    Arbre arbre = NULL;
    char *path = "exemples/A_3.saage";
    arbre = arbre_de_fichier(path);
    return arbre;
}




int copie(Arbre *dest, Arbre source)
{
    if (!source) { *dest = NULL; return 1; }
    
    if ( !(*dest = alloue_noeud(source->nom)) ) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la copie de l'arbre.\n");
        return 0;
    }

    if ( !(copie(&((*dest)->left), source->left)) ) { return 0; }

    if ( !(copie(&((*dest)->right), source->right)) ) { return 0; }

    return 1;
}



/* Cette fonction ajoute left et right pour chaque feuilles de l'arbre */
void ajoute_sous_arbres(Arbre *arbre, Noeud *left, Noeud *right)
{
    Arbre left_copie = NULL, right_copie = NULL;

    if (!*arbre) { return; }

    if ((*arbre)->left) { ajoute_sous_arbres(&((*arbre)->left), left, right); }     /* si sous arbre gauche existe */

    if ((*arbre)->right) { ajoute_sous_arbres(&((*arbre)->right), left, right); }   /* si sous arbre droite existe */

    /* inserer les sous arbres */
    if ( !((*arbre)->left) ) { 
        if ( copie(&left_copie, left) ) { (*arbre)->left = left_copie; }
    }

    if ( !((*arbre)->right) ) {
        if ( copie(&right_copie, right) ) { (*arbre)->right = right_copie; }
    }
}



int expansion(Arbre *dest, Arbre source)
{
    int left = 0, right = 0;
    Arbre source_copie = NULL;
    if (!source || !*dest) return 1;

    left = expansion(&((*dest)->left), source);

    right = expansion(&((*dest)->right), source);

    if ( comparer_chaines((*dest)->nom, source->nom) ) {

        if ( !copie(&source_copie, source) ) { return 0; }

        /* On effectue l'ajout des sous arbres de *dest a copie de source */
        if ( !source_copie ) {
            fprintf(stderr, "On n'a pas droit d'ajouter, pas assez de memoire\n");
            return 0;
        }
        /* l'ajout des sous arbres de la racine a la copie de source */
        ajoute_sous_arbres(&source_copie, (*dest)->left, (*dest)->right);

        liberer_arbre(dest);    /* liberer toute la memoire de *dest car on va la remplacer */

        *dest = source_copie;
        return 1;
    }
    return left && right;
}



void ajout_tabulation(FILE *fptr, uint count_tab)
{
    uint i;
    for (i = 0; i < count_tab; ++i) fprintf(fptr, "    ");
}



uint est_meme_arbre(Arbre arbre_un, Arbre arbre_deux)
{
    if ( !arbre_un && !arbre_deux ) return 1;
    else if ( !arbre_un  || !arbre_deux ) return 0;

    return comparer_chaines(arbre_un->nom, arbre_deux->nom) && 
            (est_meme_arbre(arbre_un->left, arbre_deux->left) && 
             est_meme_arbre(arbre_un->right, arbre_deux->right));
}


/* modifie */
void ecrire_fichier_saage(FILE *fptr, Arbre arbre, uint count_tab)
{
    if ( !arbre ) { return; }

    /* les valeurs */
    ajout_tabulation(fptr, count_tab);
    fprintf(fptr, "Valeur : %s\n", arbre->nom);

    /* les sous-arbres gauches */
    ajout_tabulation(fptr, count_tab);
    fprintf(fptr, (arbre->left) ? ("Gauche : \n") : ("Gauche : NULL\n"));
    ecrire_fichier_saage(fptr, arbre->left, count_tab + 1);

    /* les sous-arbres droites */
    ajout_tabulation(fptr, count_tab);
    fprintf(fptr, (arbre->right) ? ("Droite : \n") : ("Droite : NULL\n"));
    ecrire_fichier_saage(fptr, arbre->right, count_tab + 1);
}



/* la fonction creer_fichier_saage() est plus parlante */
int serialise(char *path_create, Arbre arbre)
{
    FILE *fptr_res = NULL;
    uint count_tab = 0;
    if ( !arbre ) { return 0; }   /* Arbre est NULL, rien a faire*/

    fptr_res = fopen(path_create, "w");
    if ( !fptr_res ) {
        fprintf(stderr, "Erreur d'ouverture du %s: %s\n", path_create, strerror(errno));
        return 0;
    }

    ecrire_fichier_saage(fptr_res, arbre, count_tab);
    fclose(fptr_res);
    return 1;
}



void greffe_dun_arbre(char *path)
{
    Arbre arbre_init = NULL, greffe = NULL;
    char *path_greffe = NULL, *path_create = NULL;
    char buffer[MAX_SIZE];

    path_exemples(buffer, path);

    arbre_init = arbre_de_fichier(buffer);
    path_greffe = "exemples/greffe_grand.saage";
    path_create = "exemples/resultat_BIG.saage";

    greffe = arbre_de_fichier(path_greffe);
    if ( !expansion(&arbre_init, greffe) )
        fprintf(stderr, "Expansion a rate \n");

    if ( !serialise(path_create, arbre_init) ) {
        remove(path_create);
        fprintf(stderr, "N'a pas reussi a creer %s\n", path_create);
    }

    visualisation_dot(arbre_init);

    if (greffe) { liberer_arbre(&greffe); }
    if (arbre_init) { liberer_arbre(&arbre_init); }
}



/* MODIFIÉ */
/* valgrind ./main -G hard.saage greffe_hard.saage */
void option_G_main(char *path_dest, char *path_greffe)
{
    Arbre arbre_init = NULL, greffe = NULL;
    char *path_create = NULL;
    char buff_dest[CHAR_SIZE], buff_greffe[CHAR_SIZE];

    path_exemples(buff_dest, path_dest);
    path_exemples(buff_greffe, path_greffe);

    arbre_init = arbre_de_fichier(buff_dest); 
    if ( !arbre_init ) { return; }

    greffe = arbre_de_fichier(buff_greffe);
    if ( !greffe ) { liberer_arbre(&arbre_init); return; }

    if ( !expansion(&arbre_init, greffe) ) {
        if (arbre_init) { liberer_arbre(&arbre_init); }
        if (greffe) { liberer_arbre(&greffe); }
        return;
    }

    if (greffe) { liberer_arbre(&greffe); }

    path_create = "exemples/fichier_option_G.saage"; 

    if ( serialise(path_create, arbre_init) ) {
        affiche_sur_stdout(path_create);
    }

    remove(path_create);
    if (arbre_init) { liberer_arbre(&arbre_init); }
}



/* pour option -E */
uint creer_arbre_stdin(Arbre *arbre)
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

    return creer_arbre_stdin(&((*arbre)->left)) && creer_arbre_stdin(&((*arbre)->right));
}




/* la fonction pour option -E d'abord avec le fichier.saage et new.saage (pour créer) */
void option_E_main(char *path_create)
{
    Arbre arbre_cree = NULL;
    char buff_create[CHAR_SIZE];

    if ( !creer_arbre_stdin(&arbre_cree) ) {
        fprintf(stderr, "la creation d'un arbre a partir de fichier usr est mal passe\n"); 
        if (arbre_cree) { liberer_arbre(&arbre_cree); }
        return;
    }
    path_exemples(buff_create, path_create);

    if ( !serialise(buff_create, arbre_cree) ){ remove(buff_create); }

    if (arbre_cree) { liberer_arbre(&arbre_cree); }
}



void option_DOT_main(char *path_create)
{
    Arbre arbre = NULL;
    char buffer[MAX_SIZE];

    path_exemples(buffer, path_create);

    arbre = arbre_de_fichier(buffer);

    /* si le buffer contient un chemin invalid, alors rien se passe...*/
    if (arbre) {
        visualisation_dot(arbre);
        liberer_arbre(&arbre);
    }
}

/* clang -std=c17 -pedantic -Wall -O2 tests_prof.o build/arbres_binaires.o build/greffe.o build/saage.o build/option.o -o tests_prof */

/* gcc -o main -std=c17 -pedantic -Wall -Wfatal-errors -Werror -Wextra -finline-functions -funroll-loops -ansi -O3 test.c */
/* gcc -o main -std=c17 -pedantic -Wall -O3 test.c */
/* valgrind --leak-check=full --show-leak-kinds=all ./main*/


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
        if (    (i + 2 < argc) &&
                recherche_substring(*(argv + i), "-G") ) {
            option_G_main(*(argv + 1 + i), *(argv + 2 + i));
            return EXIT_SUCCESS;
        }
        else if (   (i + 1 < argc) &&
                    (recherche_substring( *(argv + i), "-E") ||
                    recherche_substring( *(argv + i), "-DOT")) ) {
            path_create = *(argv + 1 + i);

            if (recherche_substring( *(argv + i), "-E"))
                option_E_main(path_create);
            else
                option_DOT_main(path_create);
            return EXIT_SUCCESS;
        }
        else if (   (i + 1 < argc) &&
                    recherche_substring( *(argv + i), "-BIG") ) {
            path_create = *(argv + 1 + i);
            greffe_dun_arbre(path_create);    
            return EXIT_SUCCESS;
        }
    }
    return EXIT_SUCCESS;
}


/* l'ajout BFS dans l'arbre binaire 
void BFS_ajoute_arbre(Arbre *arbre, char *chaine)
{
    Arbre file[MAX_SIZE];
    int debut = 0, fin = 0;
    if (!*arbre) {
        *arbre = alloue_noeud(chaine);
        return;
    }

    file[fin++] = *arbre;

    while (debut != fin) {
        Arbre noeud = file[debut++];
        if (!noeud->left) {
            noeud->left = alloue_noeud(chaine);
            return;
        } else if (!noeud->right) {
            noeud->right = alloue_noeud(chaine);
            return;
        } else {
            file[fin++] = noeud->left;
            file[fin++] = noeud->right;
        }
    }
}
*/
