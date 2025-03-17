#include "lexical.h"

int analyse_lex(typejeton T[], char str[]){
    int i = 0;
    while(str[i]!='\0'){
        switch(str[i]){
            case '(' :
                T[i].lexem = PAR_OUV;
                break;
            case ')' :
                T[i].lexem = PAR_FERM;
                break;
            case '+' :
                T[i].lexem = OPERATEUR;
                T[i].valeur.operateur = PLUS;
                break;
            case '-' :
                T[i].lexem = OPERATEUR;
                T[i].valeur.operateur = MOINS;
                break;
            case '/' :
                T[i].lexem = OPERATEUR;
                T[i].valeur.operateur = DIV;
                break;
            case '*' :
                T[i].lexem = OPERATEUR;
                T[i].valeur.operateur = FOIS;
                break;
            case 'x' :
            case'X' :
                T[i].lexem = OPERATEUR;
                T[i].valeur.operateur = FOIS;
                break;
            
        }
        i++;
    }
}