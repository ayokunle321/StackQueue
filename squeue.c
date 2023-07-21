#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "squeue.h"
#include <assert.h>


void initSqueue (Squeue **squeue){
    *squeue = (Squeue*) malloc(sizeof(Squeue));
    (*squeue)->first = NULL;
    (*squeue)->last = NULL;

}

bool isEmpty (const Squeue *squeue){
    return squeue->first == NULL;

}

void addFront (Squeue *squeue, char* val) {
    struct Node* new = (struct Node*) malloc(sizeof(struct Node));
    if (new == NULL) {
        printf("Could not allocate memory\n");
        exit(EXIT_FAILURE);
    }
    char* newVal = (char*) malloc((strlen(val) + 1) * sizeof(char));
    if (newVal == NULL) {
        printf("Could not allocate memory\n");
        free(new);
        exit(EXIT_FAILURE);
    }
    strcpy(newVal, val);
    new->val = newVal;

    new->prev = NULL;
    new->next = squeue->first;
    if (isEmpty(squeue)) {
        squeue->last = new;
    } else {
        squeue->first->prev = new;
    }
    squeue->first = new;

}


void addBack(Squeue *squeue, char* val) {
    struct Node* new = (struct Node*) malloc(sizeof(struct Node));
    if (new == NULL) {
        printf("Could not allocate memory\n");
        exit(EXIT_FAILURE);
    }
    char* newVal = (char*) malloc((strlen(val) + 1) * sizeof(char));
    if (newVal == NULL) {
        printf("Could not allocate memory\n");
        free(new);
        exit(EXIT_FAILURE);
    }
    strcpy(newVal, val);
    new->val = newVal;

    new->next = NULL;
    new->prev = squeue->last;
    if (isEmpty(squeue)) {
        squeue->first = new;
    } else {
        squeue->last->next = new;
    }
    squeue->last = new;
}



void leaveFront(Squeue* squeue) {
    assert(!isEmpty(squeue));

    struct Node* temp = squeue->first;
    char* val = temp->val;

    squeue->first = temp->next;

    if (squeue->first != NULL) {
        squeue->first->prev = NULL;
    }

    free(val);
    free(temp);

    if (isEmpty(squeue)) {
        squeue->last = NULL;
    }
}



void leaveBack(Squeue* squeue) {
    assert(!isEmpty(squeue));

    struct Node* temp = squeue->last;
    char* val = temp->val;

    squeue->last = temp->prev;

    if (squeue->last != NULL) {
        squeue->last->next = NULL;
    }

    free(val);
    free(temp);

    if (isEmpty(squeue)) {
        squeue->first = NULL;
    }
}



char* peekFront(const Squeue* squeue) {
    assert(!isEmpty(squeue));
    return squeue->first->val;
}

char* peekBack(const Squeue* squeue) {
    assert(!isEmpty(squeue));
    return squeue->last->val;
}




void print (const Squeue *squeue, char direction) {
    if (direction != 'f' && direction != 'r') {
        fprintf(stderr, "Error, illegal direction %c\n", direction);
        return;
    }

    printf("squeue is:\n");

    struct Node* curr;
    if (direction == 'f') {
        curr = squeue->first;
        while (curr != NULL) {
            printf("\t%s\n", curr->val);
            curr = curr->next;
        }
    } else {
        curr = squeue->last;
        while (curr != NULL) {
            printf("\t%s\n", curr->val);
            curr = curr->prev;
        }
    }
}




void nuke(Squeue *squeue) {
    while (!isEmpty(squeue)) {
        struct Node* curr = squeue->first;
        squeue->first = curr->next;
        if (squeue->first != NULL) {
            squeue->first->prev = NULL;
        } else {
            squeue->last = NULL;
        }
        free(curr->val);
        curr->val = NULL;
        free(curr);
        curr = NULL;
    }
}


void mergeFront(Squeue* squeue, char direction) {
    assert(squeue->first != NULL && squeue->first->next != NULL); 

    if (direction != 'f' && direction != 'r') {
        fprintf(stderr, "Error, illegal direction %c\n", direction);
        return;
    }

    struct Node* first = squeue->first;
    struct Node* second = first->next;
    int first_len = strlen(first->val);
    int second_len = strlen(second->val);

    char* new_val = (char*) malloc(sizeof(char) * (first_len + second_len + 1));
    if (direction == 'f') {
        strcpy(new_val, first->val);
        strcat(new_val, second->val);
    } else {
        strcpy(new_val, second->val);
        strcat(new_val, first->val);
    }

    free(first->val); 
    first->val = new_val;
    first->next = second->next;

    if (second->next != NULL) {
        second->next->prev = first;
    } else {
        squeue->last = first;
    }


    free(second->val);
    free(second);
}



void mergeBack(Squeue* squeue, char direction){
    assert(squeue->first != NULL && squeue->first->next != NULL);

    char* str1 = squeue->last->val;
    char* str2 = squeue->last->prev->val;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int len = len1 + len2;

    char* result = malloc(len + 1);
    if (result == NULL) {
        fprintf(stderr, "Error: unable to allocate memory for merged string.\n");
        return;
    }

    if (direction == 'f') {
        strcpy(result, str2);
        strcat(result, str1);
        free(squeue->last->val);
        squeue->last->val = result;
        struct Node* temp = squeue->last->prev;
        squeue->last->prev = temp->prev;
        if (temp->prev != NULL) {
            temp->prev->next = squeue->last;
        } else {
            squeue->first = squeue->last;
        }
        free(temp->val);
        free(temp);


    } else if (direction == 'r') {
        strcpy(result, str1);
        strcat(result, str2);
        free(squeue->last->val);
        squeue->last->val = result;
        struct Node* temp = squeue->last->prev;
        squeue->last->prev = temp->prev;
        if (temp->prev != NULL) {
            temp->prev->next = squeue->last;
        } else {
            squeue->first = squeue->last;
        }
        free(temp->val);
        free(temp);

    } else {
        fprintf(stderr, "Error, illegal direction %c.\n", direction);
    }
}

void reverse(Squeue* squeue){
    if(squeue == NULL || squeue->first == NULL){
        return;
    }
    struct Node* curr = squeue->first;
    squeue->first = squeue->last;
    squeue->last = curr;
    while (curr != NULL) {
        struct Node* temp = curr->next;
        curr->next = curr->prev;
        curr->prev = temp;
        curr = temp;
    }
}

void destroySqueue(Squeue **squeue){
    nuke(*squeue);
    free(*squeue);
    *squeue = NULL;
}




