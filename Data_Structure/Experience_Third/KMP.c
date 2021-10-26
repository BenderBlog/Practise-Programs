/* A KMP string match algorithm library implemention written by SuperBart.
 * Copyright (c) 2021 Chen Songze
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 */
#include "KMP.h" 

// Look for the length of string, since no <string.h> is allowed to use.
int StrLen(char * toMatch){
    int length = 0;
    for (length = 0; toMatch[length]!='\0'; length++) 
        continue;
    return length;
}

// Implement of the KMP algorithm.
// Found how many times "toMatch" appears in the "line".
int StrCmp_KMP(char * line, char * toMatch, int numberOfLine){
    int time = 0;
    // Next arrays.
    int *next = (int *)malloc(StrLen(toMatch)*sizeof(int));
    int i = 0, j = -1; next[0] = -1;
    while(i < StrLen(toMatch) - 1){
        if( j == -1 || toMatch[i] == toMatch[j] ){
            ++i;++j;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
    // Seek the same.
    // 'appearence' store the times toMatch appears.
    i = 0; j = 0; int appearence = 0;
    while ( i < StrLen(line) ){
        if ( j == -1 || line[i] == toMatch[j] ){
            ++i;++j;
        } else {
            j = next[j];
        }
        if ( j == StrLen(toMatch) ){
            // If found, print out the position, and look for the next.
            // Since teacher want word match, I have to think about the space...
            if (( line[i] == ' ' && line[i-j-1] == ' ' && i - j != 0 && i != StrLen(line) - 1 ) ||
                ( i - j == 0 && line[i] == ' ' ) ||
                ( i == StrLen(line) && line[i-j-1] == ' ' ) ){
                printf("%s在第%d行%d列出现\n",toMatch,numberOfLine,i-j+1);
                appearence += 1;
            }
            j = next[j-1];
        }
    }
    return appearence;
}
