/* A KMP string match algorithm library interface written by SuperBart.
 * Copyright (c) 2021 Chen Songze
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 */

// Look for "KMP.c" for more details.

#ifndef _KMP_H
#define _KMP_H

#include<stdio.h>
#include<stdlib.h>
#define ERROR 1
#define OK 0

int StrLen(char * toMatch);
int StrCmp_KMP(char * line, char * toMatch, int numberOfLine);

#endif
