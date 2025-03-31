#include "lexical.h"
#include <stdio.h>

int main() {
    typejeton T[50]; 

    char expression[50];
    printf("Entrez une expression : ");
    scanf("%49s", expression);

    AnalyseLex(T, expression);
    AfficherLexemes(T); //Affiche l'analyse lexicale
    return 0;
}