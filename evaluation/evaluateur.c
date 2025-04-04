//Mathias KALISZ PEREIRA

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../syntax/syntax.h"
#include "evaluateur.h"

double evaluate_expression(Node *root, double x_value) {
    if (root == NULL) {
        fprintf(stderr, "Erreur : noeud NULL\n");
        return 0.0;
    }

    switch (root->type) {
        case REEL:
            return root->value;

        case VARIABLE:
            return x_value;

        case OPERATEUR: {
            double gauche = evaluate_expression(root->left, x_value);
            double droite = evaluate_expression(root->right, x_value);

            switch ((int)root->value) {
                case PLUS:
                    return gauche + droite;
                case MOINS:
                    return gauche - droite;
                case FOIS:
                    return gauche * droite;
                case DIV:
                    if (droite == 0.0) {
                        fprintf(stderr, "Erreur : division par zero\n");
                        return 0.0;
                    }
                    return gauche / droite;
                case PUIS:
                    return pow(gauche, droite);
                default:
                    fprintf(stderr, "Erreur : opérateur inconnu (%d)\n", (int)root->value);
                    return 0.0;
            }
        }

        case FONCTION: {
            double arg = evaluate_expression(root->left, x_value);

            switch ((int)root->value) {
                case SIN:
                    return sin(arg);
                case COS:
                    return cos(arg);
                case TAN:
                    return tan(arg);
                case EXP:
                    return exp(arg);
                case LOG:
                    if (arg <= 0.0) {
                        fprintf(stderr, "Erreur : log d'une valeur <= 0\n");
                        return 0.0;
                    }
                    return log(arg);
                default:
                    fprintf(stderr, "Erreur : fonction inconnue (%d)\n", (int)root->value);
                    return 0.0;
            }
        }

        default:
            fprintf(stderr, "Erreur : type de nœud inconnu (%d)\n", root->type);
            return 0.0;
    }
}