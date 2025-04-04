#include <stdio.h>
#include <stdlib.h>
#include "../syntax/syntax.h"
#include "../lexical/jeton.h"

//  run each test.
void run_test(const char *desc, typejeton tokens[]) {
    printf("\n =========== Test: %s =====================\n", desc);
    Node *ast = analyserSyntaxe(tokens);
    if (!ast) {
        fprintf(stderr, "Syntax analysis failed for test: %s\n", desc);
    } else {
        printf("AST for %s:\n", desc);
        afficherArbre(ast, 0);
        libererArbre(ast);
    }
    printf("\n ======================================================== \n");
}

int main(void) {
    // Test 1:3.14 + 2.71
    typejeton test1[200] = {
        { REEL, { .reel = 3.14 } },
        { OPERATEUR, { .operateur = PLUS } },
        { REEL, { .reel = 2.71 } },
        { FIN, { 0 } }
    };
    run_test("3.14 + 2.71", test1);

    // Test 2  2.5 * 3.6
    typejeton test2[200] = {
        { REEL, { .reel = 2.5 } },
        { OPERATEUR, { .operateur = FOIS } },
        { REEL, { .reel = 3.6 } },
        { FIN, { 0 } }
    };
    run_test("2.5 * 3.6", test2);

    // Test 3 10.0 / 2.5
    typejeton test3[200] = {
        { REEL, { .reel = 10.0 } },
        { OPERATEUR, { .operateur = DIV } },
        { REEL, { .reel = 2.5 } },
        { FIN, { 0 } }
    };
    run_test("10.0 / 2.5", test3);

    // Test 4: sin(0.785)
    typejeton test4[200] = {
        { FONCTION, { .fonction = SIN } },
        { PAR_OUV, { 0 } },
        { REEL, { .reel = 0.785 } },
        { PAR_FERM, { 0 } },
        { FIN, { 0 } }
    };
    run_test(" sin(0.785)", test4);

    // Test 5: Error case(3 + 4
    typejeton test5[200] = {
        { PAR_OUV, { 0 } },
        { REEL, { .reel = 3.0 } },
        { OPERATEUR, { .operateur = PLUS } },
        { REEL, { .reel = 4.0 } },
        { FIN, { 0 } }
    };
    run_test("Error case - (3 + 4", test5);

    // Test 6: x + 3.0
    typejeton testx[200] = {
        { VARIABLE, { 0 } },
        { OPERATEUR, { .operateur = PLUS } },
        { REEL, { .reel = 3.0 } },
        { FIN, { 0 } }
    };
    run_test("x + 3.0", testx);

    return EXIT_SUCCESS;
}