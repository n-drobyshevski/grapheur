#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../evaluation/evaluateur.h"
#include "../syntax/syntax.h"
#include "../lexical/jeton.h"

Node* createReel(double value) {
    Node* n = (Node*) malloc(sizeof(Node));
    n->type = REEL;
    n->value = value;
    n->left = n->right = NULL;
    return n;
}
Node* createOperator(int op, Node* left, Node* right) {
    Node* n = (Node*) malloc(sizeof(Node));
    n->type = OPERATEUR;
    n->value = op;
    n->left = left;
    n->right = right;
    return n;
}
Node* createFunction(int func, Node* child) {
    Node* n = (Node*) malloc(sizeof(Node));
    n->type = FONCTION;
    n->value = func;
    n->left = child;
    n->right = NULL;
    return n;
}
void freeNode(Node* node) {
    if (!node) return;
    freeNode(node->left);
    freeNode(node->right);
    free(node);
}

int main(void) {
    // Test 1: 3.0 + 4.0, expected 7.0
    Node* test1 = createOperator(PLUS, createReel(3.0), createReel(4.0));
    double res1 = evaluate_expression(test1, 0.0);
    printf("Test 3+4: expected 7.0, got %f\n", res1);
    freeNode(test1);

    // Test 2: 5.0 * 2.0
    Node* test2 = createOperator(FOIS, createReel(5.0), createReel(2.0));
    double res2 = evaluate_expression(test2, 0.0);
    printf("Test 5.0 * 2.0 : expected 10.0, got %f\n", res2);
    freeNode(test2);

    // Test 3: Sin sin(0.785), expected 0.707
    Node* test3 = createFunction(SIN, createReel(0.785));
    double res3 = evaluate_expression(test3, 0.0);
    printf("Test Sin(0,785): expected approx 0.707, got %f\n", res3);
    freeNode(test3);

    // Test 4: Variable substitution: returns given x_value (42.0)
    Node* test4 = (Node*) malloc(sizeof(Node));
    test4->type = VARIABLE;
    test4->value = 0; // unused
    test4->left = test4->right = NULL;
    double res4 = evaluate_expression(test4, 42.0);
    printf("Test Variable: expected 42.0, got %f\n", res4);
    free(test4);

    return EXIT_SUCCESS;
}
