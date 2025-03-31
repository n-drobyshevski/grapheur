#include "./lexical/lexical.h"
#include "./syntax/syntax.h"

#include <stdio.h>

void RelancerProgramme() {
    typejeton T[50]; 
    char expression[50];
    
    while (1) {
        printf("Entrez une expression : ");
        scanf("%49s", expression);
        
        AnalyseLex(T, expression);
        //AfficherLexemes(T);
        
        if (!ContientErreur(T)) {
            break;
        }
        printf("Veuillez reessayer.\n");
    }
}

<<<<<<< HEAD:main.c
    Node* arbre = analyserSyntaxe(T);
    printf("\nArbre syntaxique :\n");
    afficherArbre(arbre, 0);
    libererArbre(arbre);
    
=======
int main() {
    RelancerProgramme();
>>>>>>> 616ffaae83007e8d6b3e1a89feb7c3f115f7b1d7:lexical/main.c
    return 0;
}