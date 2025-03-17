#ifndef SYNTAX_H
#define SYNTAX_H

#include <stddef.h>

/*--------------------------------------
 *          Token Types
 *-------------------------------------*/
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

/*--------------------------------------
 *           Token Struct
 *-------------------------------------*/
typedef struct {
  TokenType type;
  int value; // valid only for TOKEN_NUMBER
} Token;

/*--------------------------------------
 *         AST Node Definition
 *-------------------------------------*/
typedef struct Node {
  TokenType type;
  int value;
  struct Node *left;
  struct Node *right;
} Node;

/*--------------------------------------
 *        External Declarations
 *-------------------------------------*/
extern const char *input;
extern size_t pos;
extern Token current_token;

/*--------------------------------------
 *       Function Prototypes
 *-------------------------------------*/
void error(const char *message);
void skip_whitespace(void);
Token get_next_token(void);
void advance(void);
Node *expr(void);
Node *term(void);
Node *factor(void);
Node *create_node(TokenType type, int value, Node *left, Node *right);
void print_ast(Node *root, int level, char branch);
void free_ast(Node *root);

#endif // SYNTAX_H