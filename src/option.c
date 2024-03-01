#include "../include/option.h"


/********************************************************/
/*                                                      */
/*                    DOT FONCTIONS                     */
/*                                                      */
/********************************************************/

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


void ecrire_fin(FILE *fptr)
{
    fprintf(fptr, "}");
}


void dessine(FILE *fptr, Arbre arbre)
{
    ecrire_debut(fptr);
    ecrire_arbre(fptr, arbre);
    ecrire_fin(fptr);
}


void visualisation_dot(Arbre arbre)
{
    FILE *fptr = NULL;
    fptr = fopen("exemples/visualise.dot", "w");

    if (!fptr) { printf("Erreur à l'ouverture du fichier visualise.dot"); return; }

    else { dessine(fptr, arbre); }

    fclose(fptr);
    system("dot -Tpdf exemples/visualise.dot -o exemples/visualise.pdf");
    system("evince exemples/visualise.pdf &");
}


/********************************************************/
/*                                                      */
/*                       OPTIONS                        */
/*                                                      */
/********************************************************/


/* la fonction pour option -E d'abord avec le fichier.saage et new.saage (pour créer) */
void option_E_main(char *path_create)
{
    Arbre arbre_cree = NULL;
    char buff_create[CHAR_SIZE];

    if ( !creer_arbre_stdin(&arbre_cree) ) {
        fprintf(stderr, "la creation d'un arbre a partir de usr est mal passe\n"); 
        if (arbre_cree) { liberer_arbre(&arbre_cree); }
        return;
    }

    path_exemples(buff_create, path_create);

    if ( !serialise(buff_create, arbre_cree) ){
        remove(buff_create);
        if (arbre_cree) { liberer_arbre(&arbre_cree); return; }
    }

    if (arbre_cree) { liberer_arbre(&arbre_cree); }
}


void option_G_main(char *path_dest, char *path_greffe)
{
    Arbre arbre_init = NULL, greffe = NULL;
    char *path_create = NULL;
    char buff_dest[CHAR_SIZE];
    char buff_greffe[CHAR_SIZE];

    path_exemples(buff_dest, path_dest);

    path_exemples(buff_greffe, path_greffe);

    arbre_init = arbre_de_fichier(buff_dest); 
    if (!arbre_init) { return; }

    greffe = arbre_de_fichier(buff_greffe);
    if (!greffe) { liberer_arbre(&arbre_init); return; }


    if ( !expansion(&arbre_init, greffe) ) {
        if (arbre_init) { liberer_arbre(&arbre_init); }
        if (greffe) { liberer_arbre(&greffe); }
        return;
    }

    if (greffe) { liberer_arbre(&greffe); }

    path_create = "exemples/fichier_option_G.saage"; 

    if ( !serialise(path_create, arbre_init) ) {
        remove(path_create);
        if (arbre_init) { liberer_arbre(&arbre_init); }
        return;
    }

    affiche_sur_stdout(path_create);

    remove(path_create);
    if (arbre_init) { liberer_arbre(&arbre_init); }
    return;
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


void greffe_dun_arbre(uint numero)
{
    Arbre arbre_init = NULL, greffe = NULL, res_attendu = NULL;
    char *path_greffe = NULL, *path_create = NULL;

    switch (numero) {
        case 1:
            arbre_init = arbre_de_fichier("exemples/grand.saage");
            path_greffe = "exemples/greffe_grand.saage";

            path_create = "exemples/resultat_AM.saage";
            greffe = arbre_de_fichier(path_greffe);
            break;
        case 2:
            arbre_init = arbre_de_fichier("exemples/immense.saage");
            path_greffe = "exemples/greffe_grand.saage";

            path_create = "exemples/resultat_AM.saage";
            greffe = arbre_de_fichier(path_greffe);
            break;
        default:
            return;
    }

    if ( !expansion(&arbre_init, greffe) )
        fprintf(stderr, "Expansion a rate \n");

    if ( !serialise(path_create, arbre_init) ) {
        remove(path_create);
        fprintf(stderr, "N'a pas reussi a creer %s\n", path_create);
    }

    visualisation_dot(arbre_init);

    if (greffe) { liberer_arbre(&greffe); }
    if (arbre_init) { liberer_arbre(&arbre_init); }
    if (res_attendu) { liberer_arbre(&res_attendu); }
}

