//
// Created by zhuoran liu on 2021/2/10.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lzr_stack.h"

typedef struct _list_node {
#ifdef DEBUG
    struct TreeNode* data;
#else
    void * data;
#endif
    struct _list_node* next;
    struct _list_node* last;
} ListNode_t;

typedef struct _stack {
    ListNode_t container;
    ListNode_t* top;
} Stack_t;

void* initStack (){
    Stack_t* stack = (Stack_t*) malloc(sizeof (Stack_t));
    memset(stack, 0, sizeof (Stack_t));
    return (void*)stack;
}

void push(void* stack, void* data){
    if (data == NULL){
        printf("push null\n");
        return;
    }
    ListNode_t* temp = ((Stack_t*)stack)->top;
    if (((Stack_t*)stack)->top == NULL){
        ((Stack_t*)stack)->top = &(((Stack_t*)stack)->container);
    }else {
        ((Stack_t*)stack)->top = ((Stack_t*)stack)->top->next;
    }
    if (((Stack_t*)stack)->top == NULL){
        ((Stack_t*)stack)->top = (ListNode_t*)malloc(sizeof (ListNode_t));
        ((Stack_t*)stack)->top->next = NULL;
        ((Stack_t*)stack)->top->last = temp;
        temp->next = ((Stack_t*)stack)->top;
    }
    ((Stack_t*)stack)->top->data = data;
#ifdef DEBUG
    printf("push %d\n", ((struct TreeNode*)data)->val);
#endif
}

void* pop(void* stack){
    if (((Stack_t*)stack)->top == NULL){
        printf("pop null\n");
        return NULL;
    }
    ListNode_t* temp = ((Stack_t*)stack)->top;
    ((Stack_t*)stack)->top = ((Stack_t*)stack)->top->last;
#ifdef DEBUG
    printf("pop %d", ((struct TreeNode*)temp->data)->val);
#endif
    return temp->data;
}

void freeStack(void* stack){
    ListNode_t* cur_list_node = ((Stack_t*)stack)->container.next;
    while (cur_list_node != NULL){
        ListNode_t* temp = cur_list_node;
        cur_list_node = temp->next;
        free(temp);
    }
    free(stack);
}

int isEmptyStack(void* stack){
    int is_empty = 0;
    if (((Stack_t*)stack)->top == NULL){
        is_empty = 1;
    }
    return is_empty;
}

void* getStackTopData(void* stack){
    if (((Stack_t*)stack)->top == NULL){
        return NULL;
    }
    return ((Stack_t*)stack)->top->data;
}