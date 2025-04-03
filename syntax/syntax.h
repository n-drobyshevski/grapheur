#ifndef SYNTAX_H
#define SYNTAX_H

#include "../lexical/jeton.h"
#include <stddef.h>
/*------------------------------------------------
 *           AST Node Definition
 *-----------------------------------------------*/
typedef struct Node {
  int type; // use token type (e.g., REEL, OPERATEUR, etc.) from jeton.h
  float value;
  struct Node *left;
  struct Node *right;
} Node;

/*------------------------------------------------
 *           Function Prototypes
 *-----------------------------------------------*/
void error(const char *message);
Node *analyserSyntaxe(typejeton tokens[]);
void afficherArbre(Node *root, int level);
void libererArbre(Node *root);
#endif