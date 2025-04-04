#include <ctype.h> // for isspace
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for memcpy

#include "../lexical/jeton.h"
#include "syntax.h"

/*------------------------------------------------
 *              Global State
 *-----------------------------------------------*/
const char *input;
static int currentIndex = 0;
size_t pos;

static typejeton tokens[256];
static typejeton *currentTokens;
static int parseHasError = 0;

/*------------------------------------------------
 *                Error Handling
 *-----------------------------------------------*/
static void parseError(const char *message) {
  fprintf(stderr, "syntax level Error: %s at token index %d\n", message,
          currentIndex);
  parseHasError = 1;
}

static typejeton getCurrentToken() { return tokens[currentIndex]; }

static typejeton advanceToken() {
  ++currentIndex;
  //   printf("[LOG] Advanced to token lexem: %d\n",
  //   tokens[currentIndex].lexem);
  return tokens[currentIndex];
}

/*------------------------------------------------
 *           Parser based on typejeton
 *-----------------------------------------------*/
static Node *expr(); // Forward

static Node *create_node(typelexem type, float value, Node *left, Node *right) {
  Node *node = (Node *)malloc(sizeof(Node));
  // Map 'typelexem' to Node fields
  node->type = type;
  node->value = value;
  node->left = left;
  node->right = right;
  return node;
}

Node *factor() {
  typejeton tk = getCurrentToken();
  if (tk.lexem == REEL) {
    Node *node = create_node(REEL, tk.valeur.reel, NULL, NULL);
    advanceToken();
    return node;
  } else if (tk.lexem == FONCTION) {
    typefontion func = tk.valeur.fonction;
    advanceToken(); // skip function token
    Node *arg = NULL;
    // Allow functions to either use parentheses
    if (getCurrentToken().lexem == PAR_OUV) {
      advanceToken(); // skip '('
      arg = expr();
      if (getCurrentToken().lexem != PAR_FERM) {
        parseError("Missing closing parenthesis after function");
      }
      advanceToken(); // skip ')'
    } else {
      arg = factor();
    }
    return create_node(FONCTION, func, arg, NULL);
  } else if (tk.lexem == PAR_OUV) {
    advanceToken(); // skip '('
    Node *node = expr();
    if (getCurrentToken().lexem != PAR_FERM) {
      parseError("Missing closing parenthesis");
    }
    advanceToken(); // skip ')'
    return node;
  } else if (tk.lexem == VARIABLE) {
    Node *node = create_node(VARIABLE, 0.0, NULL, NULL);
    advanceToken();
    return node;
  } else {
    parseError("Unexpected token in factor");
    return NULL;
  }
}
static Node *power() {
  Node *node = factor();
  // Handle exponentiation operator (PUIS)
  if (getCurrentToken().lexem == OPERATEUR &&
      getCurrentToken().valeur.operateur == PUIS) {
    advanceToken();
    // Using recursion ensures right-associativity.
    Node *right = power();
    node = create_node(OPERATEUR, PUIS, node, right);
  }
  return node;
}

Node *term() {
  // Change factor() to power() so that exponentiation is parsed correctly.
  Node *node = power();
  while (1) {
    typejeton tk = getCurrentToken();
    if (tk.lexem == OPERATEUR &&
        (tk.valeur.operateur == FOIS || tk.valeur.operateur == DIV)) {
      typeoperateur op = tk.valeur.operateur;
      advanceToken();
      Node *right = power();
      node = create_node(OPERATEUR, op, node, right);
    } else {
      break;
    }
  }
  return node;
}

static Node *expr() {
  //   printf("[LOG] Entering expr() at token index %d\n", currentIndex);
  Node *node = term();
  while (1) {
    typejeton tk = getCurrentToken();
    // printf("[LOG] Current token: lexem=%d, valeur=%d\n", tk.lexem,
    //    tk.valeur.operateur);
    if (tk.lexem == OPERATEUR &&
        (tk.valeur.operateur == PLUS || tk.valeur.operateur == MOINS)) {
      //   printf("[LOG] Found operator (%d) in expr() at token index %d\n",
      //  tk.valeur.operateur, currentIndex);
      typeoperateur op = tk.valeur.operateur;
      advanceToken();
      Node *right = term();
      node = create_node(OPERATEUR, op, node, right);
      //   printf("[LOG] Created operator node (%d) at token index %d\n", op,
      //  currentIndex);
    } else {
      break;
    }
  }
  //   printf("[LOG] Exiting expr() at token index %d\n", currentIndex);
  return node;
}

/*------------------------------------------------
 *      Helper function to convert enum to string
 *-----------------------------------------------*/
static const char *token_type_to_str(typelexem t) {
  switch (t) {
  case REEL:
    return "REEL";
  case OPERATEUR:
    return "OPERATEUR";
  case FONCTION:
    return "FONCTION";
  case ERREUR:
    return "ERREUR";
  case FIN:
    return "FIN";
  case PAR_OUV:
    return "PAR_OUV";
  case PAR_FERM:
    return "PAR_FERM";
  case VARIABLE:
    return "VARIABLE";
  default:
    return "UNKNOWN_TOKEN";
  }
}
// Print the AST sideways
void print_ast(Node *root, int level, char branch) {
  if (!root)
    return;

  // Print the right subtree, marking it with '/'
  print_ast(root->right, level + 1, '/');

  for (int i = 0; i < level; i++) {
    printf("    ");
  }

  // Print the branch marker ( ' ' for root, '/' or '\' for subtrees )
  printf("%c--(", branch);
  if (root->type == OPERATEUR) {
    // Print the operator symbol using tk.valeur.operateur
    const char *op_str;
    switch ((int)root->value) {
    case PLUS:
      op_str = "+";
      break;
    case MOINS:
      op_str = "-";
      break;
    case FOIS:
      op_str = "*";
      break;
    case DIV:
      op_str = "/";
      break;
    case PUIS:
      op_str = "^";
      break;
    default:
      op_str = "UNKNOWN";
      break;
    }
    printf("OPERATEUR:%s", op_str);
  } else if (root->type == FONCTION) {
    // Print the function name based on function code in root->value
    const char *func_str;
    switch ((int)root->value) {
    case ABS:
      func_str = "ABS";
      break;
    case SIN:
      func_str = "SIN";
      break;
    case SQRT:
      func_str = "SQRT";
      break;
    case LOG:
      func_str = "LOG";
      break;
    case COS:
      func_str = "COS";
      break;
    case TAN:
      func_str = "TAN";
      break;
    case EXP:
      func_str = "EXP";
      break;
    case ENTIER:
      func_str = "ENTIER";
      break;
    case VAL_NEG:
      func_str = "VAL_NEG";
      break;
    case SINC:
      func_str = "SINC";
      break;
    default:
      func_str = "UNKNOWN";
      break;
    }
    printf("FONCTION:%s", func_str);
  } else {
    printf("%s", token_type_to_str(root->type));
    if (root->type == REEL) {
      printf(":%f", root->value);
    }
  }
  printf(")\n");

  // Print the left subtree, marking it with '\'
  print_ast(root->left, level + 1, '\\');
}

/*------------------------------------------------
 *          AST Memory Cleanup
 *-----------------------------------------------*/
static void free_ast(Node *root) {
  if (!root)
    return;
  free_ast(root->left);
  free_ast(root->right);
  free(root);
}

/*------------------------------------------------
 *      Public API for syntax parsing & AST management
 *-----------------------------------------------*/
Node *analyserSyntaxe(typejeton tokens_array[]) {
  parseHasError = 0;

  memcpy(tokens, tokens_array, sizeof(tokens));
  currentIndex = 0;
  Node *root = expr();
  if (parseHasError) {
    fprintf(stderr, "Recoverable syntax error encountered.\n");
    return NULL;
  }
  if (tokens[currentIndex].lexem != FIN) {
    parseError("Extra characters after valid expression");
  }
  printf("\nSyntax OK - AST built.\n");
  fflush(stdout);
  return root;
}

void afficherArbre(Node *root, int level) { print_ast(root, level, ' '); }

void libererArbre(Node *root) { free_ast(root); }