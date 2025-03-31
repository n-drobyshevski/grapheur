#ifndef LEXICAL_H
#define LEXICAL_H

#include "jeton.h"
#include <stdio.h>

void AnalyseLex(typejeton T[], char str[]);
void AfficherLexemes(typejeton T[]);
int ContientErreur(typejeton T[]);

#endif