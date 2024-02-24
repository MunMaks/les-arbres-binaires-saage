#include "../include/option.h"


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



void dessine(FILE *fptr, Arbre arbre) {
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




void greffe_dun_arbre(uint numero)
{
    Arbre arbre_init = NULL, greffe = NULL, res_attendu = NULL;
    char *path_greffe = NULL, *path_res_att = NULL, *path_create = NULL;

    switch (numero) {
        case 1:
            arbre_init = cree_A_1();
            path_greffe = "exemples/B.saage";
            path_res_att = "exemples/A_1_apres_greffe_de_B.saage";

            path_create = "exemples/created.saage";
            greffe = arbre_de_fichier(path_greffe); 
            res_attendu = arbre_de_fichier(path_res_att);
            break;

        case 2:
            arbre_init = cree_A_2();
            path_greffe = "exemples/C.saage";
            path_res_att = "exemples/A_2_apres_greffe_de_C.saage";

            path_create = "exemples/created.saage";
            greffe = arbre_de_fichier(path_greffe); 
            res_attendu = arbre_de_fichier(path_res_att);
            break;

        case 3:
            arbre_init = cree_A_3();
            path_greffe = "exemples/D.saage";
            path_res_att = "exemples/A_3_apres_greffe_de_D.saage";

            path_create = "exemples/created.saage";
            greffe = arbre_de_fichier(path_greffe); 
            res_attendu = arbre_de_fichier(path_res_att);
            break;

        case 4:
            arbre_init = arbre_de_fichier("exemples/hard.saage");
            path_greffe = "exemples/greffe_hard.saage";

            path_create = "exemples/created.saage";
            greffe = arbre_de_fichier(path_greffe); 
            break;
        case 5:
            arbre_init = arbre_de_fichier("exemples/ultra.saage");
            path_greffe = "exemples/greffe_hard.saage";

            path_create = "exemples/created.saage";
            greffe = arbre_de_fichier(path_greffe); 
            break;
        default:
            return;
    }

    if ( !expansion(&arbre_init, greffe) )
        fprintf(stderr, "Expansion a rate \n");

    if ( !creer_fichier_saage(arbre_init, path_create) ) {
        remove(path_create);
        fprintf(stderr, "N'a pas reussi a creer %s\n", path_create);
    }

    /* Pour visualise l'arbre apres la greffe*/
    visualisation_dot(arbre_init);

    if (greffe) { liberer_arbre(&greffe); }
    if (arbre_init) { liberer_arbre(&arbre_init); }
    if (res_attendu) { liberer_arbre(&res_attendu); }
}


uint option_G_main(char *argv[])
{
    Arbre arbre_init = NULL, greffe = NULL;
    char *path_create = NULL;
    char path_init[CHAR_SIZE];
    char path_greffe[CHAR_SIZE];


    copie_chaine(path_init, "exemples/");
    concatenantion(path_init, *(argv + 2));
    
    copie_chaine(path_greffe, "exemples/");
    concatenantion(path_greffe, *(argv + 3));

    arbre_init = arbre_de_fichier(path_init); 
    if (!arbre_init) { return 0; }

    greffe = arbre_de_fichier(path_greffe);
    if (!greffe) { liberer_arbre(&arbre_init); return 0; }


    if ( !expansion(&arbre_init, greffe) ) {
        if (arbre_init) { liberer_arbre(&arbre_init); }
        if (greffe) { liberer_arbre(&greffe); }
        return 0;
    }
    liberer_arbre(&greffe);

    path_create = "exemples/new_fichier.saage"; 
    if (!creer_fichier_saage(arbre_init, path_create)) {
        remove(path_create);
        if (arbre_init) { liberer_arbre(&arbre_init); }
        return 0;
    }

    affiche_sur_stdout(path_create);

    if (arbre_init) { liberer_arbre(&arbre_init); }
    return 1;
}

void option_DOT_main(char *path_create)
{
    Arbre arbre = NULL;
    char buffer[MAX_SIZE];

    /* exemples/path_create */
    if (recherche_substring(path_create, "exemples/")) {    
        copie_chaine(buffer, path_create);
    } else {  /* path_create */
        copie_chaine(buffer, "exemples/");
        concatenantion(buffer, path_create);
    }

    arbre = arbre_de_fichier(buffer);

    /* si le buffer contient un chemin invalid, alors rien se passe...*/
    if (arbre) {
        visualisation_dot(arbre);
        liberer_arbre(&arbre);
    }
}



/* la fonction pour option -E d'abord avec le fichier.saage et new.saage (pour créer) */
void option_E_main(char *path_create)
{
    Arbre arbre_cree = NULL;
    char path_init[CHAR_SIZE];
    FILE *fptr = NULL;

    fptr = fopen("exemples/clavier.saage", "r");

    if (!fptr) { 
        fprintf(stderr, "l'ouverture du fichier clavier.saage mal passe\n");
        return;
    }

    if ( !creer_arbre(fptr, &arbre_cree) ) {
        fprintf(stderr, "la creation d'un arbre mal passe\n"); 
        if (arbre_cree) { liberer_arbre(&arbre_cree); }
        fclose(fptr);
        return;
    }
    fclose(fptr);
    copie_chaine(path_init, "exemples/");
    concatenantion(path_init, path_create);

    if ( !creer_fichier_saage(arbre_cree, path_init) ){
        remove(path_init);
        if (arbre_cree) { liberer_arbre(&arbre_cree); return; }
    }

    if (arbre_cree) { liberer_arbre(&arbre_cree); }
}
