#ifndef SYNTAX_H
#define SYNTAX_H

#include "../lexical/jeton.h"
#include "../lexical/lexical.h"

// Définition des fonctions de l'analyseur syntaxique
Node* creerNoeud(typejeton jeton);
Node* analyserExpression(typejeton T[], int* index);
Node* analyserFacteur(typejeton T[], int* index);
Node* analyserTerme(typejeton T[], int* index);
Node* analyserSyntaxe(typejeton T[]);
void afficherArbre(Node* racine, int profondeur);
void libererArbre(Node* racine);

#endif // SYNTAX_H