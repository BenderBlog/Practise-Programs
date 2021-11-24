/* Binary Sort Tree Demo.
 * Copyright (c) 2021 Chen Songze and Flandre Scarlet
 * Everyone is premitted to use these code in terms of The Unlicense.
 * However, I strongly suggest everyone to translate my comments into Chinese.
 * Warning! Not fully debugged!
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Aha, without comments, how could you write your goddame report in an hour.
// Oh no, she is coming, my neck has just cleaned, NOOOOOOOO...
// Hold on, how cute she is:-)

typedef struct Element{
    char data;
    struct Element *leftChild;
    struct Element *rightChild;
}Element, *binTree;

binTree search(binTree T, char toFind){
    if (T->rightChild == NULL && T->leftChild == NULL && T->data != toFind){
        return NULL;
    } else if (toFind == T->data){
        return T;
    } else if (toFind  > T->data){
        if (T->rightChild == NULL){
            return NULL;
        } else {
            search(T->rightChild, toFind);
        }
    } else if (toFind  < T->data){
        if (T->leftChild == NULL){
            return NULL;
        } else {
            search(T->leftChild, toFind);
        }
    }
}

binTree searchParents(binTree T, char toFind){
    if (T->rightChild == NULL && T->leftChild == NULL){
        return NULL;
    } else if (T->leftChild != NULL && T->leftChild->data == toFind){
        return T;
    } else if (T->rightChild != NULL && T->rightChild->data == toFind){
        return T;
    } else if (toFind  > T->data){
        if (T->rightChild == NULL){
            return NULL;
        } else {
            searchParents(T->rightChild, toFind);
        }
    } else if (toFind  < T->data){
        if (T->leftChild == NULL){
            return NULL;
        } else {
            searchParents(T->leftChild, toFind);
        }
    }
}

binTree insert(binTree T, char toInsert){
    if ( search(T, toInsert) != NULL ){
        printf("%c is inside.\n",toInsert);
        return T;
    } else {
        binTree new = (binTree)malloc(sizeof(Element));
        new->data = toInsert;
        new->leftChild = NULL;
        new->rightChild = NULL;
        // Look for the position and insert.
        if ( T == NULL ){
            T = new;
            return T;
        } else {
            binTree p = T;
            while (p){
                if (toInsert < p->data && p->leftChild != NULL){
                    p = p->leftChild;
                } else if (toInsert > p->data && p->rightChild != NULL){
                    p = p->rightChild;
                } else if (toInsert < p->data && p->leftChild == NULL){
                    p->leftChild = new;
                    return T;
                } else if (toInsert > p->data && p->rightChild == NULL){
                    p->rightChild = new;
                    return T;
                }
            }
        }
    }
}

binTree delete(binTree T, char toDel)
{
    if ( search(T, toDel) == NULL ){
        printf("%c is not here.\n",toDel);
        return T;
    }

    binTree parents = searchParents(T,toDel);
    binTree children = search(T,toDel);

    short isRight = 0;
    if (parents->rightChild != NULL && parents->rightChild->data == children->data){
        isRight = 1;
    } else if (parents->leftChild == NULL){
        isRight = -1;
    }

    if(children == NULL){
        printf("ERROR: NOT FOUND.\n");
    } else {
        //1st:p为叶子结点，则直接删
        if( children->leftChild == NULL && children->rightChild == NULL ) {
            binTree grave = children;
            if (isRight == 1){
                parents->rightChild = NULL;
            } else {
                parents->leftChild = NULL;
            }
            free(grave);
        }
        //2nd:p既有左子树又有右子树，则找到左子树中最大的结点替代p
        else if( children->leftChild != NULL && children->rightChild != NULL ){
            binTree leftBiggest = children->leftChild;
            binTree p = leftBiggest;
            while (p->rightChild != NULL){
                p = p->rightChild;
            }
            binTree biggestParents = searchParents(T,p->data);
            
            binTree grave = biggestParents->rightChild;
            biggestParents->rightChild = NULL;
            children->data = grave->data;
            free(grave);
        }
        //3rd:p只有一个孩子，则孩子给父亲y
        else {
            binTree grave = NULL;
            if (isRight == 1){
                grave = children->rightChild;
                children->rightChild = NULL;
            } else {
                grave = children->leftChild;
                children->leftChild = NULL;
            }
            children->data = grave->data;
            free(grave);
        }
    }
    return T;
}

binTree create(char a[]){
    binTree T = (binTree)malloc(sizeof(Element));
    T->data = a[0];
    T->leftChild = NULL;
    T->rightChild = NULL;
    for (int i = 1; i < strlen(a); ++i){
        T = insert(T,a[i]);
    }
    return T;
}

void midSearch(binTree T){
	if(T){
		midSearch(T->leftChild);
		printf("%c",T->data);
		midSearch(T->rightChild);
	}
}

int main(){
    char a[] = "EDBAGCF";

    binTree T = create(a);
    midSearch(T);
    printf("\n\n");

    T = insert(T,'J');
    midSearch(T);
    printf("\n\n");

    T = insert(T,'A');
    midSearch(T);
    printf("\n\n");

    T = delete(T,'B');
    midSearch(T);
    printf("\n\n");

    T = delete(T,'G');
    midSearch(T);
    printf("\n\n");

    T = delete(T,'B');
    midSearch(T);
    printf("\n\n");

    return 0;

}