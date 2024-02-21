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


/* modifier */
/* permet de gerer toute la memoire allouee */

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




Arbre alloue(const char *chaine)
{
    Arbre noeud = malloc(sizeof *noeud);
    if ( !noeud ) return NULL;

    noeud->nom = dupliquer_string(chaine);  /* strdup() */
    if ( !(noeud->nom) ) { free(noeud); return NULL; }

    noeud->left = NULL;
    noeud->right = NULL;
    return noeud;
}




/********************************************************/
/*                                                      */
/*                        ARBRES                        */
/*                                                      */
/********************************************************/


/* modifier */
Arbre construire_arbre(FILE *fichier)
{
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




/* modifier */
Arbre arbre_de_fichier(const char *path)
{
    Arbre arbre = NULL;
    FILE *fptr = fopen(path, "r");
    if (!fptr) {
        fprintf(stderr, "Erreur d'ouverture du fichier.saage: %s\n", strerror(errno));
        return NULL;
    }
    arbre = construire_arbre(fptr);
    fclose(fptr);
    return arbre;
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




void affiche_arbre(Arbre arbre)
{
    if (!arbre) return;
    printf("%s \n", arbre->nom);
    affiche_arbre(arbre->left);
    affiche_arbre(arbre->right);
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



Arbre copie(Arbre source)
{
    Arbre new_node = NULL;
    if (!source) { return NULL; }
    
    if ( !(new_node = alloue(source->nom)) ) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la copie de l'arbre.\n");
        return NULL;
    }

    new_node->left = copie(source->left);
    new_node->right = copie(source->right);

    return new_node;
}



/* modifier */
/* Cette fonction ajoute left et right pour chaque feuilles de l'arbre */
void ajoute_sous_arbres(Arbre *arbre, Noeud *left, Noeud *right)
{
    Arbre left_copie = NULL, right_copie = NULL;

    if (!*arbre) { return; }

    if ((*arbre)->left) { ajoute_sous_arbres(&((*arbre)->left), left, right); }     /* si sous arbre gauche existe */

    if ((*arbre)->right) { ajoute_sous_arbres(&((*arbre)->right), left, right); }   /* si sous arbre droite existe */


    /* inserer les sous arbres */
    if ( !((*arbre)->left) ) { 
        left_copie = copie(left);
        (*arbre)->left = left_copie;
    }

    if ( !((*arbre)->right) ) {
        right_copie = copie(right);
        (*arbre)->right = right_copie;
    }
}





/* modifier */
uint expansion(Arbre *dest, Arbre source)
{
    uint left = 0, right = 0;
    if (!source || !*dest) return 0;

    left = ((*dest)->left) ? expansion(&((*dest)->left), source) : 1;

    right = ((*dest)->right) ? expansion(&((*dest)->right), source) : 1;

    if ( comparer_chaines((*dest)->nom, source->nom) ) {    /*comparer_chaines()*/

        Arbre source_copie = copie(source);

        /* On effectue l'ajout des sous arbres de *dest a copie de source */
        if (!source_copie) {
            fprintf(stderr, "On n'a pas droit d'ajouter, pas assez de memoire\n");
            return 0;
        }
        /* l'ajout des sous arbres de la racine */
        ajoute_sous_arbres(&source_copie, (*dest)->left, (*dest)->right);

        liberer_arbre(dest);    /* liberer toute la memoire alloue par dest */

        *dest = source_copie;
    }
    return left && right;
}






void ajout_tabulation(FILE *fptr, uint count_tab)
{
    uint i;
    for (i = 0; i < count_tab; ++i) fprintf(fptr, "    ");    /* fprintf(fptr, "\t"); */
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
void write_fichier_saage(FILE *fptr, Arbre arbre, uint count_tab)
{
    if (!arbre) { return; }

    /* les valeurs */
    ajout_tabulation(fptr, count_tab);
    fprintf(fptr, "Valeur : %s\n", arbre->nom);

    /* les sous-arbres gauches */
    ajout_tabulation(fptr, count_tab);
    fprintf(fptr, (arbre->left) ? ("Gauche : \n") : ("Gauche : NULL\n"));
    write_fichier_saage(fptr, arbre->left, count_tab + 1);

    /* les sous-arbres droites */
    ajout_tabulation(fptr, count_tab);
    fprintf(fptr, (arbre->right) ? ("Droite : \n") : ("Droite : NULL\n"));
    write_fichier_saage(fptr, arbre->right, count_tab + 1);
}






/* modifie */
uint faire_greffe(Arbre *dest , Arbre source)
{

    if ( expansion(dest, source) ) {
        return 1;
    }

    fprintf(stderr, "expansion a mal passe, la memoire ...\n");
    return 0;
}



/* cree */
uint creer_fichier_saage(Arbre arbre, const char *path_create)
{
    FILE *fptr_res = NULL;
    uint count_tab = 0;
    if (!arbre) { return 0; }   /* Arbre est NULL, rien a faire*/

    fptr_res = fopen(path_create, "w");
    if (!fptr_res) {
        fprintf(stderr, "Erreur d'ouverture du %s: %s\n", path_create, strerror(errno));
        return 0;
    }

    write_fichier_saage(fptr_res, arbre, count_tab);
    fclose(fptr_res);
    return 1;
}





/* gcc -o main -std=c17 -pedantic -Wall -Wfatal-errors -ansi -O3 test.c */
/* valgrind --leak-check=full --show-leak-kinds=all ./main*/

/* 
• saage -E fichier.saage crée une sauvegarde dans le fichier .saage
d’un arbre saisi par l’utilisateur au clavier. (TO DO)
• saage -G s.saage g.saage crée l’arbre où le greffon g.saage
est appliqué à l’arbre source stocké dans s.saage. (TO DO)
Le résultat de la greffe sera fournis sur la sortie standard au format .saage 


Remarques:
1. Aucun autre texte que l’arbre obtenu et affiché au format .saage ne devra être ajouté sur la sortie
standard. (TO DO)
2. Toute la mémoire allouée devra être libérée à l’issue du processus. (fait)

*/


int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Pas assez d'arguments\n");
        return 0;
    }

    while (*++argv) {
        /* saage -E fichier.saage */
        printf("%s\n", *argv);

        /* saage -G s.saage g.saage */
    }



    /*
    Arbre arbre_init = NULL, greffe = NULL, res_attendu = NULL;
    char *path_greffe = NULL, *path_res_att = NULL, *path_create = NULL;

    arbre_init = cree_A_3();
    path_greffe =   "exemples/D.saage";
    path_res_att = "exemples/A_3_apres_greffe_de_D.saage";

    path_create = "exemples/created.saage";

    greffe = arbre_de_fichier(path_greffe); 

    printf("greffe passé: %d\n", faire_greffe(&arbre_init, greffe));

    liberer_arbre(&greffe);


    res_attendu = arbre_de_fichier(path_res_att);

    if (!creer_fichier_saage(arbre_init, path_create)){
        fprintf(stderr, "N'a pas reussi a creer %s\n", path_create);
        return 1;
    }

    printf("La meme arbre 2: %u\n", est_meme_arbre(arbre_init, res_attendu));


    if (arbre_init) { liberer_arbre(&arbre_init); }
    if (res_attendu) { liberer_arbre(&res_attendu); }
    */    /* pour être sur qu'on aura pas de segfault */

    return 0;
}
