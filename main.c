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
    AfficherLexemes(T);

    if (!ContientErreur(T)) {
      printf("Buildn' ast...");
      Node *arbre = analyserSyntaxe(T);
      printf("\nExpression: %s", expression);
      printf("\nArbre syntaxique :\n");
      afficherArbre(arbre, 0);
      libererArbre(arbre);
      break;
    }
    printf("Veuillez reessayer.\n");
  }
}

int main() {
  RelancerProgramme();
  return 0;
}