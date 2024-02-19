#include "../include/arbres_binaires.h"


int len_string(const char *mot)
{
    int i = 0;
    while (*(mot + i)) ++i;
    return i; 
}


Arbre alloue(const char *chaine)
{
    Arbre noeud = NULL;
    if (!(noeud = malloc(sizeof *noeud) )) { return NULL; }

    noeud->nom = dupliquer_string(chaine);
    if (!noeud->nom) {
        free(noeud);
        return NULL;
    }

    noeud->right = noeud->left = NULL;
    return noeud;
}



void liberer_arbre(Arbre *arbre)
{
    if (!*arbre) { return; }
    liberer_arbre(&(*arbre)->left);
    liberer_arbre(&(*arbre)->right);
    free((*arbre)->nom);    /* la memeoire de char *    */
    free(*arbre);           /* la memeoire de Noeud *   */
}



void affiche_tree(Arbre arbre)
{
    if (!arbre) return;
    printf("%s \n", arbre->nom);
    affiche_tree(arbre->left);
    affiche_tree(arbre->right);
}



char* dupliquer_string(const char *source)
{
    char *destination = NULL, *temp_dest = NULL;
    const char *temp_src = NULL;

    if ( !source ) return NULL;     /* source est vide */

    /* si n'a pas de memoire... */
    if ( !(destination = malloc((len_string(source) + 1) * sizeof *destination)) ) return NULL;

    temp_dest = destination;
    temp_src = source;

    while (*temp_src) { *temp_dest++ = *temp_src++; }

    *temp_dest = '\0';

    return destination;
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
/* 

valgrind --tool=memcheck --leak-check=full --show-reachable=yes -v ./algo

*/
