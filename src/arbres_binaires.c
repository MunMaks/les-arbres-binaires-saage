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
int comparer_chaines(const char *string_un, const char *string_deux)
{
    while (*string_un && *string_deux) {
        if (*string_un != *string_deux) return 0;
        ++string_un;
        ++string_deux;
    }
    return (!*string_un && !*string_deux) ? (1) : (0);
}



/********************************************************/
/*                                                      */
/*                        ARBRES                        */
/*                                                      */
/********************************************************/



void affiche_arbre(Arbre arbre)
{
    if (!arbre) return;
    printf("%s \n", arbre->nom);
    affiche_arbre(arbre->left);
    affiche_arbre(arbre->right);
}



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



/* l'ajout BFS dans l'arbre binaire */
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




void ajout_tabulation(FILE *fptr, uint count_tab)
{
    uint i;
    for (i = 0; i < count_tab; ++i) fprintf(fptr, "    ");    /* fprintf(fptr, "\t"); */
}



uint est_meme_arbre(Arbre arbre_un, Arbre arbre_deux) {
    if ( !arbre_un && !arbre_deux ) return 1;
    else if ( !arbre_un  || !arbre_deux ) return 0;

    return comparer_chaines(arbre_un->nom, arbre_deux->nom) && 
            (est_meme_arbre(arbre_un->left, arbre_deux->left) && 
             est_meme_arbre(arbre_un->right, arbre_deux->right));
}



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





/* DOT */

void ecrire_debut(FILE *fptr)
{
    fprintf(fptr, 
        "digraph arbre {\n\tnode [ shape = record, height = .1]\n\tedge [ tailclip = false , arrowtail = dot, dir = both];\n\n");
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



void dessine( FILE *fptr , Arbre arbre) {
    ecrire_debut(fptr);
    ecrire_arbre(fptr, arbre);
    ecrire_fin(fptr);
}
