#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

/*------------------------------------------------
 *               Token Types
 *-----------------------------------------------*/
typedef enum {
  TOKEN_NUMBER,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_MUL,
  TOKEN_DIV,
  TOKEN_LPAREN,
  TOKEN_RPAREN,
  TOKEN_EOF,
  TOKEN_INVALID
} TokenType;

/*------------------------------------------------
 *                Token Struct
 *-----------------------------------------------*/
typedef struct {
  TokenType type;
  int value; // valid only for TOKEN_NUMBER
} Token;

/*------------------------------------------------
 *           AST Node Definition
 *-----------------------------------------------*/
typedef struct Node {
  TokenType type;
  int value;
  struct Node *left;
  struct Node *right;
} Node;

/*------------------------------------------------
 *              Global State
 *-----------------------------------------------*/
const char *input;
size_t pos;
Token current_token;

/*------------------------------------------------
 *                Error Handling
 *-----------------------------------------------*/
void error(const char *message) {
  fprintf(stderr, "Error: %s at position %zu\n", message, pos);
  exit(EXIT_FAILURE);
}

/*================================================
 *            LEXICAL ANALYSIS
 *===============================================*/
static void skip_whitespace() {       //parcourt la chaîne de caractère en sautant les space
  while (input[pos] && isspace(input[pos])) {
    pos++;
  }
}

static Token get_next_token() {
  skip_whitespace();
  char current = input[pos];

  if (current == '\0') {  //End of line
    return (Token){TOKEN_EOF, 0};
  }
  if (isdigit(current)) { //check si c'est un chiffre
    int value = 0;
    while (isdigit(input[pos])) {
      value = value * 10 + (input[pos] - '0');  // traduit le nb en base 10
      pos++;
    }
    return (Token){TOKEN_NUMBER, value};
  }
  if (current == '+') {
    pos++;
    return (Token){TOKEN_PLUS, 0};
  }
  if (current == '-') {
    pos++;
    return (Token){TOKEN_MINUS, 0};
  }
  if (current == '*') {
    pos++;
    return (Token){TOKEN_MUL, 0};
  }
  if (current == '/') {
    pos++;
    return (Token){TOKEN_DIV, 0};
  }
  if (current == '(') {
    pos++;
    return (Token){TOKEN_LPAREN, 0};
  }
  if (current == ')') {
    pos++;
    return (Token){TOKEN_RPAREN, 0};
  }

  // Invalid character
  pos++;
  return (Token){TOKEN_INVALID, 0};
}

void advance() {
  current_token = get_next_token();
  printf("[LOG] Advanced to token type: %d (value: %d)\n",
         current_token.type, current_token.value);
}

/*================================================
 *              SYNTAX ANALYSIS
 *===============================================*/
/* Forward declaration for expression parse */
static Node *expr();

static Node *create_node(TokenType type, int value, Node *left, Node *right) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->type = type;
  node->value = value;
  node->left = left;
  node->right = right;
  return node;
}


Node *factor() {
  printf("[LOG] Enter factor()\n");
  if (current_token.type == TOKEN_NUMBER) {
    printf("[LOG] factor() sees NUMBER: %d\n", current_token.value);
    Node *node = create_node(TOKEN_NUMBER, current_token.value, NULL, NULL);
    advance();
    return node;
  } else if (current_token.type == TOKEN_LPAREN) {
    printf("[LOG] factor() sees LPAREN\n");
    advance(); // skip '('
    Node *node = expr();
    if (current_token.type != TOKEN_RPAREN) {
      error("Missing closing parenthesis");
    }
    printf("[LOG] factor() sees RPAREN\n");
    advance(); // skip ')'
    return node;
  } else {
    error("Unexpected token in factor");
    return NULL; // never reached
  }
}

Node *term() {
  printf("[LOG] Enter term()\n");
  Node *node = factor();
  while (current_token.type == TOKEN_MUL || current_token.type == TOKEN_DIV) {
    TokenType op = current_token.type;
    printf("[LOG] term() sees operator: %d\n", op);
    advance(); // consume * or /
    Node *right = factor();
    node = create_node(op, 0, node, right);
  }
  return node;
}

Node *expr() {
  printf("[LOG] Enter expr()\n");
  Node *node = term();
  while (current_token.type == TOKEN_PLUS || current_token.type == TOKEN_MINUS) {
    TokenType op = current_token.type;
    printf("[LOG] expr() sees operator: %d\n", op);
    advance(); // consume + or -
    Node *right = term();
    node = create_node(op, 0, node, right);
  }
  return node;
}
/*------------------------------------------------
 *      Helper function to convert enum to string
 *-----------------------------------------------*/
static const char* token_type_to_str(TokenType t) {
  switch (t) {
  case TOKEN_NUMBER:  return "TOKEN_NUMBER";
  case TOKEN_PLUS:    return "TOKEN_PLUS";
  case TOKEN_MINUS:   return "TOKEN_MINUS";
  case TOKEN_MUL:     return "TOKEN_MUL";
  case TOKEN_DIV:     return "TOKEN_DIV";
  case TOKEN_LPAREN:  return "TOKEN_LPAREN";
  case TOKEN_RPAREN:  return "TOKEN_RPAREN";
  case TOKEN_EOF:     return "TOKEN_EOF";
  case TOKEN_INVALID: return "TOKEN_INVALID";
  default:            return "UNKNOWN_TOKEN";
  }
}
// Print the AST sideways 
void print_ast(Node *root, int level, char branch) {
  if (!root) return;

  // Print the right subtree, marking it with '/'
  print_ast(root->right, level + 1, '/');

  for (int i = 0; i < level; i++) {
    printf("    ");
  }

  // Print the branch marker ( ' ' for root, '/' or '\' for subtrees )
  printf("%c--(%s", branch, token_type_to_str(root->type));
  if (root->type == TOKEN_NUMBER) {
    printf(":%d", root->value);
  }
  printf(")\n");

  // Print the left subtree, marking it with '\'
  print_ast(root->left, level + 1, '\\');
}

/*------------------------------------------------
 *          AST Memory Cleanup
 *-----------------------------------------------*/
static void free_ast(Node *root) {
  if (!root) return;
  free_ast(root->left);
  free_ast(root->right);
  free(root);
}
/*------------------------------------------------
 *          AST Evaluation
 *-----------------------------------------------*/
static int evaluate(Node *root) {
  if (!root) {
    error("Cannot evaluate a NULL node");
    return 0; // Not reached 
  }

  // Log the node type before we evaluate
  printf("[EVAL] Evaluating node type: %s\n", token_type_to_str(root->type));

  switch (root->type) {
    case TOKEN_NUMBER:
      printf("[EVAL] TOKEN_NUMBER value = %d\n", root->value);
      return root->value;

    case TOKEN_PLUS: {
      int left_val = evaluate(root->left);
      int right_val = evaluate(root->right);
      int sum = left_val + right_val;
      printf("[EVAL] TOKEN_PLUS: %d + %d = %d\n", left_val, right_val, sum);
      return sum;
    }

    case TOKEN_MINUS: {
      int left_val = evaluate(root->left);
      int right_val = evaluate(root->right);
      int diff = left_val - right_val;
      printf("[EVAL] TOKEN_MINUS: %d - %d = %d\n", left_val, right_val, diff);
      return diff;
    }

    case TOKEN_MUL: {
      int left_val = evaluate(root->left);
      int right_val = evaluate(root->right);
      int product = left_val * right_val;
      printf("[EVAL] TOKEN_MUL: %d * %d = %d\n", left_val, right_val, product);
      return product;
    }

    case TOKEN_DIV: {
      int left_val = evaluate(root->left);
      int right_val = evaluate(root->right);
      if (right_val == 0) {
        error("Division by zero");
      }
      int quotient = left_val / right_val;
      printf("[EVAL] TOKEN_DIV: %d / %d = %d\n", left_val, right_val, quotient);
      return quotient;
    }

    default:
      // For parentheses and other tokens, either evaluate the subtree or error
      error("Cannot evaluate this node type");
      return 0; 
  }
}


/*================================================
 *                 MAIN FUNCTION
 *===============================================*/
int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s \"expression\"\n", argv[0]);
    return EXIT_FAILURE;
  }

  input = argv[1];
  pos = 0;
  advance();

  Node *root = expr();
  if (current_token.type != TOKEN_EOF) {
    error("Extra characters after valid expression");
  }

  printf("\nSyntax OK - AST built.\n");
  /* Print the graphical tree for debugging */
  printf("\n[LOG] Printing AST:\n");
    print_ast(root, 0, ' ');

  /* Evaluate the expression */
  printf("\n ===============================\n");
  int result = evaluate(root);
  printf("\n[LOG] Evaluation result: %d\n", result);

  free_ast(root);
  return EXIT_SUCCESS;
}

// test