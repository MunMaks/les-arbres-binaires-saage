#include "../include/arbres_binaires.h"


int len(char *mot)
{
    int i = 0;
    while (*(mot + i)) ++i;
    return i; 
}


Arbre alloue(const char *chaine)
{
    Arbre noeud = NULL;
    if (!(noeud = malloc(sizeof *noeud) )) { return NULL; }

    noeud->nom = strdup(chaine);
    if (!noeud->nom) {
        free(noeud);
        return NULL;
    }

    noeud->right = noeud->left = NULL;
    return noeud;
}



int hauteur(Arbre arbre)
{
    if (! arbre) { return -1; }
    else {
        int left = hauteur(arbre->left);
        int right = hauteur(arbre->right);
        return MAX(left, right) + 1;
    }
}



int creer_arbre(FILE *fptr, Arbre *arbre)
{
    int val = 0;
    char buffer[MAX_SIZE];


    if ((fscanf(fptr, "%d ", &val)) <= 0) {
        return 0;
    }

    if (!val) { return 1; }

    else if (fscanf(fptr, "%s", buffer) <= 0 ) {
        return 0;
    }

    if ( ! (*arbre = alloue(buffer)) ) {
        return 0;
    }

    return creer_arbre(fptr, &((*arbre)->left)) &&
           creer_arbre(fptr, &((*arbre)->right));
}






// int SAAGE_creer_arbre(FILE *fptr, Arbre *arbre)
// {
//     char buffer[MAX_SIZE];

//     if (!fptr) { return 0; }

//     if (fscanf(fptr, "Valeur : %s ", buffer) <= 0) {
//         return 0;
//     }

//     fprintf(stderr, "before buffer: %s\n", buffer);

//     if (! (*arbre = alloue(buffer)) ) { 
//         fprintf(stderr, "Problemes d'allocation\n");
//         return 0; }

//     if (strcmp(buffer, "NULL") == 0) { 
//         *arbre = NULL;
//         fprintf(stderr, "Inside strcmp\n");
//         return 1;
    
//     }    /* si le nom de l'arbre n'est pas \0 */




//     fprintf(stderr, "before Gauche: %s\n", buffer);
//     if (fscanf(fptr, "%*s : \n") <= 0){
//         fprintf(stderr, "Gauche... \n");
//         return 0;
//     }

//     fprintf(stderr, "before left: %s\n", buffer);
//     // left
//     if (!creer_arbre(fptr, &(*arbre)->left)) { return 0; }

//     fprintf(stderr, "before Droite: %s\n", buffer);
//     if (fscanf(fptr, "%*s : ") <= 0){
//         fprintf(stderr, "Droite... \n");
//         return 0;
//     }

//     fprintf(stderr, "before right: %s\n", buffer);
//     // right
//     if (!creer_arbre(fptr, &(*arbre)->right)) { return 0; }
//     return 1;
// }



int SAAGE_creer_arbre(FILE *fptr, Arbre *arbre) {
    char buffer[MAX_SIZE];
    char line[MAX_SIZE];

    if (!fptr) {
        return 0; // File pointer is NULL
    }

    // Read a line from the file
    if (!fgets(line, sizeof(line), fptr)) {
        return 0; // Failed to read line
    }

    // Extract value from the line
    if (sscanf(line, "Valeur : %[^\n]", buffer) == EOF) {
        return 0; // Failed to extract value
    }

    if (strcmp(buffer, "NULL") == 0) {
        *arbre = NULL; // Set tree node to NULL
        return 1;
    }

    if (!(*arbre = alloue(buffer))) {
        return 0; // Memory allocation failed
    }

    // Parse left subtree
    if (fgets(line, sizeof(line), fptr) && strstr(line, "Gauche : ")) {
        return SAAGE_creer_arbre(fptr, &((*arbre)->left));
    }

    // Parse right subtree
    if (fgets(line, sizeof(line), fptr) && strstr(line, "Droite : ")) {
        return SAAGE_creer_arbre(fptr, &((*arbre)->right));
    }

    return 1;
}




void ecrire_debut(FILE *fptr)
{
    fprintf(fptr, 
        "digraph arbre {\n\tnode [ shape = record, height = .1]\n\tedge [ tailclip = false , arrowtail = dot, dir = both];\n\n");
}



void ecrire_arbre(FILE *fptr, Arbre arbre)
{   
    if (!arbre) { return; }     /* rien a faire */

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



void liberer_arbre(Arbre *arbre)
{
    if (*arbre){
        liberer_arbre(&(*arbre)->left);
        liberer_arbre(&(*arbre)->right);
        free((*arbre)->nom);    // la memeoire de char *
        free(*arbre);           // la memeoire de Noeud *
        *arbre = NULL;
    }
}



Arbre cree_A_1(void)
{
    Arbre arbre = NULL;
    FILE *fptr = fopen("exemples/A_1.saage", "r");
    if (!fptr) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return NULL;
    }

    fprintf(stderr, "Before SAAGE\n");
    int res = SAAGE_creer_arbre(fptr, &arbre);
    fprintf(stderr, "result: %d\n", res);
    fprintf(stderr, "After SAAGE\n");
    /*
    Arbre arbre_gauche = NULL;
    Arbre arbre_droit = NULL;

    if (! (arbre = alloue("arbre\n")) ) { return NULL; }

    if (! (arbre_gauche = alloue("binaire\n")) ) { liberer_arbre(&arbre); return NULL; }

    if (! (arbre_droit = alloue("ternaire\n")) ) { liberer_arbre(&arbre); return NULL; }


    arbre->left = arbre_gauche;
    arbre->right = arbre_droit;
    */
    fclose(fptr);
    return arbre;
}



Arbre cree_A_2(void)
{
    Arbre arbre = NULL;
    FILE *fptr = fopen("exemples/A_2.saage", "r");
    if (!fptr) {
        fprintf(stderr, "A_2 n'est pas créé\n");
        return NULL;
    }
    fprintf(stderr, "Before SAAGE\n");
    int res = SAAGE_creer_arbre(fptr, &arbre);
    fprintf(stderr, "result: %d\n", res);
    fprintf(stderr, "After SAAGE\n");
    fclose(fptr);
    return arbre;
}



Arbre cree_A_3(void)
{
    Arbre arbre = NULL;
    FILE *fptr = fopen("exemples/A_3.saage", "r");
    if (!fptr) {
        fprintf(stderr, "A_3 n'est pas créé\n");
        return NULL;
    }
    fprintf(stderr, "Before SAAGE\n");
    int res = SAAGE_creer_arbre(fptr, &arbre);
    fprintf(stderr, "result: %d\n", res);
    fprintf(stderr, "After SAAGE\n");
    fclose(fptr);
    return arbre;
}
