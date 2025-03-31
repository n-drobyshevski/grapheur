#include "../lexical/jeton.h"
#include "../lexical/lexical.h"
#include <stdlib.h>
#include <stdio.h>

// Fonction pour créer un nouveau nœud
Node* creerNoeud(typejeton jeton) {
    Node* nouveau = (Node*)malloc(sizeof(Node));
    if (!nouveau) {
        printf("Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    nouveau->jeton = jeton;
    nouveau->pjeton_preced = NULL;
    nouveau->pjeton_suiv = NULL;
    return nouveau;
}

// Fonction de parsing récursive pour analyser une expression
Node* analyserExpression(typejeton T[], int* index);
Node* analyserFacteur(typejeton T[], int* index);
Node* analyserTerme(typejeton T[], int* index);

// Analyse un facteur (nombre, variable, parenthèses ou fonction)
Node* analyserFacteur(typejeton T[], int* index) {
    typejeton jeton = T[*index];
    (*index)++;

    if (jeton.lexem == REEL || jeton.lexem == VARIABLE) {
        return creerNoeud(jeton);
    }
    else if (jeton.lexem == FONCTION) {
        Node* noeud = creerNoeud(jeton);
        noeud->pjeton_suiv = analyserFacteur(T, index);
        return noeud;
    }
    else if (jeton.lexem == PAR_OUV) {
        Node* noeud = analyserExpression(T, index);
        if (T[*index].lexem == PAR_FERM) {
            (*index)++;
        } else {
            printf("Erreur : Parenthèse non fermée\n");
            exit(EXIT_FAILURE);
        }
        return noeud;
    }
    printf("Erreur de syntaxe\n");
    exit(EXIT_FAILURE);
}

// Analyse un terme (multiplication et division ont priorité)
Node* analyserTerme(typejeton T[], int* index) {
    Node* noeud = analyserFacteur(T, index);
    
    while (T[*index].lexem == OPERATEUR && 
           (T[*index].valeur.operateur == FOIS || T[*index].valeur.operateur == DIV)) {
        typejeton op = T[*index];
        (*index)++;
        Node* nouveau = creerNoeud(op);
        nouveau->pjeton_preced = noeud;
        nouveau->pjeton_suiv = analyserFacteur(T, index);
        noeud = nouveau;
    }
    return noeud;
}

// Analyse une expression complète
Node* analyserExpression(typejeton T[], int* index) {
    Node* noeud = analyserTerme(T, index);
    
    while (T[*index].lexem == OPERATEUR && 
           (T[*index].valeur.operateur == PLUS || T[*index].valeur.operateur == MOINS)) {
        typejeton op = T[*index];
        (*index)++;
        Node* nouveau = creerNoeud(op);
        nouveau->pjeton_preced = noeud;
        nouveau->pjeton_suiv = analyserTerme(T, index);
        noeud = nouveau;
    }
    return noeud;
}

// Fonction principale d'analyse syntaxique
Node* analyserSyntaxe(typejeton T[]) {
    int index = 0;
    return analyserExpression(T, &index);
}

// Fonction pour afficher l'arbre syntaxique
void afficherArbre(Node* racine, int profondeur) {
  if (racine == NULL) return;
  afficherArbre(racine->pjeton_suiv, profondeur + 1);
  for (int i = 0; i < profondeur; i++) printf("  ");
  if (racine->jeton.lexem == REEL) {
      printf("%f\n", racine->jeton.valeur.reel);
  } else if (racine->jeton.lexem == VARIABLE) {
      printf("x\n");
  } else if (racine->jeton.lexem == OPERATEUR) {
      switch (racine->jeton.valeur.operateur) {
          case PLUS: printf("+\n"); break;
          case MOINS: printf("-\n"); break;
          case FOIS: printf("*\n"); break;
          case DIV: printf("/\n"); break;
          case PUIS: printf("^\n"); break;
      }
  } else if (racine->jeton.lexem == FONCTION) {
      switch (racine->jeton.valeur.fonction) {
          case SIN: printf("SIN\n"); break;
          case COS: printf("COS\n"); break;
          case TAN: printf("TAN\n"); break;
          case LOG: printf("LOG\n"); break;
          case SQRT: printf("SQRT\n"); break;
          case EXP: printf("EXP\n"); break;
          default: printf("f\n");
      }
  }
  afficherArbre(racine->pjeton_preced, profondeur + 1);
}

// Fonction pour libérer l'arbre
void libererArbre(Node* racine) {
    if (!racine) return;
    libererArbre(racine->pjeton_preced);
    libererArbre(racine->pjeton_suiv);
    free(racine);
}