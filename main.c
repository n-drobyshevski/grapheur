#include "./lexical/lexical.h"
#include "./syntax/syntax.h"

#include <stdio.h>

void RelancerProgramme() {
  typejeton T[256];
  char expression[100];

  while (1) {
    printf("Entrez une expression : ");
    scanf("%49s", expression);

    AnalyseLex(T, expression);
    AfficherLexemes(T);

    if (!ContientErreur(T)) {
      printf("Buildn' ast...");
      Node *arbre = analyserSyntaxe(T);
      if (arbre == NULL) {
        printf("Partial or invalid expression. Syntax error.\n");
      } else {
        printf("\nExpression: %s", expression);
        printf("\nArbre syntaxique :\n");
        afficherArbre(arbre, 0);
        libererArbre(arbre);
        break;
      }
    }
    printf("Veuillez reessayer.\n");
  }
}

int main() {
  RelancerProgramme();
  return 0;
}