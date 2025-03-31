#include "./lexical/lexical.h"
#include "./syntax/syntax.h"

#include <stdio.h>

int main() {
    typejeton T[50]; // Augmentation de la taille pour éviter les débordements

    char expression[50];
    printf("Entrez une expression : ");
    scanf("%49s", expression); // Empêche le dépassement de mémoire

    AnalyseLex(T, expression);
    AfficherLexemes(T);

    Node* arbre = analyserSyntaxe(T);
    printf("\nArbre syntaxique :\n");
    afficherArbre(arbre, 0);
    libererArbre(arbre);
    
    return 0;
}