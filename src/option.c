#include "../include/option.h"


/********************************************************/
/*                                                      */
/*                    FONCTIONS DOT                     */
/*                                                      */
/********************************************************/

static void ecrire_debut(FILE *fptr)
{
    fprintf(fptr, "digraph arbre{\n\tnode [ shape = record, height = .1]\n\tedge [ tailclip = false , arrowtail = dot, dir = both];\n\n");
}


static void ecrire_arbre(FILE *fptr, Arbre arbre)
{   
    if (!arbre) { return; }

    fprintf(fptr,"\tn%p [label=\"<gauche> | <valeur> %s | <droit>\"];\n", (void *) arbre, arbre->val);

    if (arbre->fg) {
        fprintf(fptr, "\tn%p:gauche:c -> n%p:valeur;\n", (void *) arbre, (void *) arbre->fg);
        ecrire_arbre(fptr, arbre->fg);
    }

    if (arbre->fd) {
        fprintf(fptr, "\tn%p:droit:c -> n%p:valeur;\n", (void *) arbre, (void *) arbre->fd);
        ecrire_arbre(fptr, arbre->fd);
    }
}


static void ecrire_fin(FILE *fptr)
{
    fprintf(fptr, "}");
}


static void dessine(FILE *fptr, Arbre arbre)
{
    ecrire_debut(fptr);
    ecrire_arbre(fptr, arbre);
    ecrire_fin(fptr);
}


static void visualisation_dot(Arbre arbre)
{    
    FILE *fptr = NULL;
    int status = 0;
    char *path = NULL;
    if (!arbre) { return; }
    path = "exemples/visualise.dot";
    fptr = fopen(path, "w");

    if (!fptr) { 
        fprintf(stderr, "Erreur à l'ouverture du fichier visualise.dot\n"); 
        return; 
    }

    dessine(fptr, arbre);

    if ( fclose(fptr) ){
        fprintf(stderr, "la fermeture de fichier %s a echoue \n", path);
    }


    status = system("dot -Tpdf exemples/visualise.dot -o exemples/visualise.pdf");

    if (status) {
        fprintf(stderr, "Erreur lors de la generation du fichier PDF\n");
        return;
    }

    status = system("evince exemples/visualise.pdf &");

    if (status) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier PDF\n");
        return;
    }
}



/********************************************************/
/*                                                      */
/*                       OPTIONS                        */
/*                                                      */
/********************************************************/


void option_E_main(char *path_create)
{
    Arbre arbre_cree = NULL;
    char buff_create[CHAR_SIZE];

    if ( !construit_arbre(&arbre_cree) ) {
        fprintf(stderr, "la creation d'un arbre a partir de fichier usr est mal passe\n"); 
        if (arbre_cree) { liberer_arbre(&arbre_cree); }
        return;
    }
    path_exemples(buff_create, path_create);

    if ( !serialise(buff_create, arbre_cree) ){ remove(buff_create); }

    if (arbre_cree) { liberer_arbre(&arbre_cree); }
}



/**
 * @brief affichage sur la sortie standart
 * 
 * @param path_create est un chemin
 */
static void affiche_sur_stdout(char *path_create)
{
    FILE *fptr = NULL;
    char buffer[MAX_SIZE];
    fptr = fopen(path_create, "r");

    if (!fptr) { 
        fprintf(stderr, "Erreur d'ouverture du %s: %s\n", path_create, strerror(errno));
        return;
    }

    while (fgets(buffer, MAX_SIZE, fptr)) { fputs(buffer, stdout); }

    if ( fclose(fptr) ){
        fprintf(stderr, "la fermeture de fichier %s a echoue \n", path_create);
    }
}


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
