#ifndef JETON_H
#define JETON_H
typedef enum
{
    REEL,OPERATEUR,FONCTION,ERREUR,FIN,PAR_OUV,PAR_FERM,VARIABLE
}typelexem;

typedef enum
{
PLUS,MOINS,FOIS,DIV,PUIS
}typeoperateur;

typedef enum
{
ABS,SIN,SQRT,LOG,COS,TAN,EXP,ENTIER,VAL_NEG,SINC
}typefontion;

typedef enum
{
erreur100,erreur101,erreur200,erreur300,erreur400
}typeerreur;

typedef union
{
    float reel;
    typefontion fonction;
    typeoperateur operateur;
    typeerreur erreur;
}typevaleur;

typedef struct 
{
typelexem lexem;
typevaleur valeur;
}typejeton;

// typedef struct Node
// {
//     typejeton jeton;
//     struct Node *pjeton_preced;
//     struct Node *pjeton_suiv;
// }Node;
// typedef Node *Arbre;
#endif 