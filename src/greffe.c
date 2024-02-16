/* Greffe */

int copie(Arbre *dest, Arbre source)
{
    if (!source) { *dest = NULL; return 0; }  /* Source est vide */

    *dest = malloc(sizeof *source);

    if (*dest) { return 0; }  /* allocation mal passe */
      
    if (source->left) {
        *(dest)->left = source->left;
        return copie(&(*dest)->left, source->left); 
    }

    if (source->right) {
        *(dest)->right = source->right;
        return copie(&(*dest)->right, source->right); 
    }

    return 1;
}

