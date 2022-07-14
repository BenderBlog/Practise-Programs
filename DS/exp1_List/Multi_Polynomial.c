/* Dirty way to add/minus multi polynomial.
 * Copyright (c) 2021 Chen Songze
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 */
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#define ERROR 1
#define OK 0

/* Defination of node of the Polynomial:
 *   Two Parts in the node of the node, the data, and the point to the next node.
 *   Data part store two numbers, coeffient and exponent.
 *   The first node is the head node, stored the number of the node in the coeffient.
 *   Exponent in the head node is set to 0.
 *   The last node's point is set to NULL.
 */
typedef struct Poly{
    int coeffient;
    int exponent;
    struct Poly *next;
}Poly, *Polynomial;

// Add Node Formula.
// Modified version of Linear_List's, written by me.
int AddNode (Polynomial L, int position, int coeffient, int exponent){
    Polynomial p = L; 
    int mark = 0;
    while ( p != NULL && mark < position - 1 ){
        p = p->next; mark++;
    }
    if ( p == NULL || mark > position - 1 ){
        printf("Unable to add!");
        return ERROR;
    }
    Polynomial add = (Polynomial)malloc(sizeof(Poly));
    add->coeffient = coeffient;
    add->exponent = exponent;
    add->next = p->next;
    p->next = add;
    L->coeffient += 1;
    return OK;
}

// Connect two polynomial in a polynomial.
// It's a shame that it breaks the original polynomial:-(
Polynomial ConnectPolynomial (Polynomial L, Polynomial M, int check){
    // Create a new polynomial 'result', store the essential message here.
    Polynomial result = (Polynomial)malloc(sizeof(Polynomial));
    result->coeffient = L->coeffient + M->coeffient;
    result->exponent = 0;
    Polynomial p = result;
    Polynomial q = NULL;
    // Change next point to the proper position.
    result->next = L->next;
    while ( p->next ){
        p = p->next;
    }
    p->next = M->next;
    // Special here, if we need to minus, the second polynomial shall be negative.
    if (check == 2){
        //minus
        while ( p ){
            p->coeffient *= -1;
            p = p->next;
        }
    }
    return result;
}

// Order the new, combined polynomial with exponent. Bigger first.
// Heavy modified version of Linear_Order's, written by me.
void OrderPolynomial (Polynomial L){
    Polynomial p = L->next;
    for ( int i = 0; i < L->coeffient - 1; ++i ){
        Polynomial q = p->next;
        Polynomial max = p;
        for ( int j = i; j < L->coeffient - 1; ++j ){
            if ( max->exponent < q->exponent ){
                max = q;
            }
            q = q->next;
        }
        if ( max->exponent != p->exponent ){
            int temp;
            temp = max->exponent;
            max->exponent = p->exponent;
            p->exponent = temp;

            temp = max->coeffient;
            max->coeffient = p->coeffient;
            p->coeffient = temp;           
        }
        p = p -> next;
    }
}

// List the polynomial.
// Modified version of Linear_List's, written by me.
void ListPolynomial(Polynomial L){
    Polynomial p = L->next;
    int number = L->coeffient;
    if ( number == 0 ){
        printf("empty list!");
    }
    for ( int i = 0; i < number; ++i ){
        printf("%dx^%d", (int)p->coeffient, (int)p->exponent);
        if (i != number - 1){
            printf(" + ");
        }
        p = p->next;
    }
    printf("\n");
}

// Calculate the Polynomials.
Polynomial Calculate (Polynomial L, Polynomial M, int check){
    // Store the length of the polynomials, in order to round.
    int L_Length = L->coeffient;
    int M_Length = M->coeffient;
    Polynomial result = ConnectPolynomial(L,M,check);
    // Order polynomial, make the next progress quicker.
    OrderPolynomial(result);
    /* Time to calculate it.
     * exp_temp: store the first exponent.
     * sum: store the add of the exponent's coeffiect.
     * count: check the step, used in check in the for.
     * all: store the number of the total node in the new, calculated polynomial.
     */
    Polynomial p = result->next;
    Polynomial q = result;
    int exp_temp = 0;
    int sum = 0;
    int count;
    int all = 0;
    // Search for the same exponent, merge the coeffient.
    // Since we ordered them, it should be done in a row.
    for (int i = 1; i < L_Length+M_Length; i += count){
        exp_temp = p->exponent;
        sum = p->coeffient;
        count = 1;
        p = p->next;
        while( p->exponent == exp_temp ){
            sum += p->coeffient;
            count++;
            if ( p->next ){
                p = p->next;
            } else {
                break;
            }
        }
        if ( sum != 0 ){
            q = q->next;
            q->coeffient = sum;
            result->coeffient -= count - 1;
        } else if ( sum == 0 ){
            result->coeffient -= count;
        }
        q->next = p;
        //ListPolynomial(result);
    }
    //result->coeffient = all;
    return result;
}

// Main formula. Mainly create two polynomial, add material to it, and calculate it.
int main() {
    // Create Polynomials 'L' and 'M'
    Polynomial L = (Polynomial)malloc(sizeof(Polynomial));
    Polynomial M = (Polynomial)malloc(sizeof(Polynomial));
    if (!L || !M) {
        printf("Unable to Create L.\n");
        return ERROR;
    } else {
        L->coeffient = 0;
        L->exponent = 0;
        L->next = NULL;
        M->coeffient = 0;
        M->exponent = 0;
        M->next = NULL;
    }
    // Add Material for L and M
    int toAdd;
    printf("==add material for L==\n");
    scanf("%d",&toAdd);
    for ( int i = 0; i < toAdd; ++i){
        int coeffient, exponent;
        scanf("%d%d",&coeffient,&exponent);
        AddNode(L,1,coeffient,exponent);
    }
    printf("==add material for M==\n");
    scanf("%d",&toAdd);
    for ( int i = 0; i < toAdd; ++i){
        int coeffient, exponent;
        scanf("%d%d",&coeffient,&exponent);
        AddNode(M,1,coeffient,exponent);
    }
    // Check whether add or minus, then output the result.
    printf("==Add(1) or Minus(2)==\n");
    int check;
    scanf("%d",&check);
    switch(check){
        case 1: ListPolynomial(Calculate(L,M,1));break;
        case 2: ListPolynomial(Calculate(L,M,2));break;
        default: printf("Invalid input!\n");
    }
    
    return OK;
}
