#include "lexical.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void AfficherLexemes(typejeton T[]) {
    int i = 0;
    while (T[i].lexem != FIN) {
        printf("Lexeme %d : ", i);
        switch (T[i].lexem) {
            case REEL:
                printf("REEL (%f)\n", T[i].valeur.reel);
                break;
            case OPERATEUR:
                printf("OPERATEUR ");
                switch (T[i].valeur.operateur) {
                    case PLUS: printf("(+)\n"); break;
                    case MOINS: printf("(-)\n"); break;
                    case FOIS: printf("(*)\n"); break;
                    case DIV: printf("(/)\n"); break;
                    case PUIS: printf("(^)\n"); break;
                }
                break;
            case VARIABLE:
                printf("VARIABLE (x)\n");
                break;
            case FONCTION:
                printf("FONCTION ");
                switch (T[i].valeur.fonction) {
                    case SIN: printf("(SIN)\n"); break;
                    case COS: printf("(COS)\n"); break;
                    case TAN: printf("(TAN)\n"); break;
                    case LOG: printf("(LOG)\n"); break;
                    case SQRT: printf("(SQRT)\n"); break;
                    case EXP: printf("(EXP)\n"); break;
                    default: printf("(Inconnue)\n");
                }
                break;
            case PAR_OUV:
                printf("PAR_OUV (()\n");
                break;
            case PAR_FERM:
                printf("PAR_FERM ())\n");
                break;
            case ERREUR:
                printf("ERREUR (Code %d)\n", T[i].valeur.erreur);
                break;
            default:
                printf("Autre\n");
        }
        i++;
    }
}


void AnalyseLex(typejeton T[], char str[]) {
    int i = 0, j = 0;
    
    while (str[i] != '\0') {
        if (isspace(str[i])) { // Ignore les espaces
            i++;
            continue;
        }

        switch (str[i]) {
            case '(':
                T[j].lexem = PAR_OUV;
                break;
            case ')':
                T[j].lexem = PAR_FERM;
                break;
            case '+':
                T[j].lexem = OPERATEUR;
                T[j].valeur.operateur = PLUS;
                break;
            case '-':
                T[j].lexem = OPERATEUR;
                T[j].valeur.operateur = MOINS;
                break;
            case '*':
                T[j].lexem = OPERATEUR;
                T[j].valeur.operateur = FOIS;
                break;
            case '/':
                T[j].lexem = OPERATEUR;
                T[j].valeur.operateur = DIV;
                break;
            case '^':
                T[j].lexem = OPERATEUR;
                T[j].valeur.operateur = PUIS;
                break;
            case 'x':
            case 'X':
                T[j].lexem = VARIABLE;
                break;
            default:
                if (isdigit(str[i]) || str[i] == '.') { 
                    T[j].lexem = REEL;
                    T[j].valeur.reel = strtof(&str[i], NULL);
                    while (isdigit(str[i]) || str[i] == '.') i++; // Ignore le nombre déjà traité
                    j++;
                    continue;
                }
                if (isalpha(str[i])) {
                    char buffer[10];
                    int k = 0;
                    while (isalpha(str[i]) && k < 9) { // Récupère le mot
                        buffer[k++] = str[i++];
                    }
                    buffer[k] = '\0';
                    
                    if ((strcmp(buffer, "SIN")) == 0|(strcmp(buffer, "sin"))== 0)
                        T[j].valeur.fonction = SIN;
                    else if (strcmp(buffer, "COS") == 0|(strcmp(buffer, "cos"))== 0)
                        T[j].valeur.fonction = COS;
                    else if (strcmp(buffer, "TAN") == 0|(strcmp(buffer, "tan"))== 0)
                        T[j].valeur.fonction = TAN;
                    else if (strcmp(buffer, "EXP") == 0|(strcmp(buffer, "exp"))== 0)
                        T[j].valeur.fonction = EXP;
                    else {
                        T[j].lexem = ERREUR;
                        T[j].valeur.erreur = erreur100;
                    }
                    
                    T[j].lexem = FONCTION;
                    j++;
                    continue;
                }
                
                T[j].lexem = ERREUR;
                T[j].valeur.erreur = erreur100;
        }
        i++;
        j++;
    }

    T[j].lexem = FIN; // Marque la fin de l'analyse
}