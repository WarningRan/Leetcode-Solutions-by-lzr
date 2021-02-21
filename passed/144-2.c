//
// Created by zhuoran liu on 2021/2/8.
//

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define MALLOC_CHECK_ 3
#define DEBUG
//Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct ListNode1 {
#ifdef DEBUG
    struct TreeNode* data;
#else
    void * data;
#endif
    struct ListNode1* next;
    struct ListNode1* last;
};

struct Stack {
    struct ListNode1 container;
    struct ListNode1* top;
};

typedef struct ListNode1 ListNode1_t;
typedef struct Stack Stack_t;

Stack_t* initStack (){
    Stack_t* stack = (Stack_t*) malloc(sizeof (Stack_t));
    memset(stack, 0, sizeof (Stack_t));
    return stack;
}

void push(Stack_t* stack, void* data){
    if (data == NULL){
        printf("push null\n");
        return;
    }
    ListNode1_t* temp = stack->top;
    if (stack->top == NULL){
        stack->top = &(stack->container);
    }else {
        stack->top = stack->top->next;
    }
    if (stack->top == NULL){
        stack->top = (ListNode1_t*)malloc(sizeof (ListNode1_t));
        stack->top->next = NULL;
        stack->top->last = temp;
        temp->next = stack->top;
    }
    stack->top->data = data;
    printf("push %d\n", ((struct TreeNode*)data)->val);
}

void* pop(Stack_t* stack){
    if (stack->top == NULL){
        printf("pop null\n");
        return NULL;
    }
    ListNode1_t* temp = stack->top;
    stack->top = stack->top->last;
    printf("pop %d", ((struct TreeNode*)temp->data)->val);
    return temp->data;
}

void freeStack(Stack_t * stack){
    ListNode1_t* cur_list_node = stack->container.next;
    while (cur_list_node != NULL){
        ListNode1_t* temp = cur_list_node;
        cur_list_node = temp->next;
        free(temp);
    }
    free(stack);
}

int isEmptyStack(Stack_t* stack){
    int is_empty = 0;
    if (stack->top == NULL){
        is_empty = 1;
    }
    return is_empty;
}

void* getStackTopData(Stack_t* stack){
    if (stack->top == NULL){
        return NULL;
    }
    return stack->top->data;
}

int* preorderTraversal(struct TreeNode* root, int* returnSize){
    int* result = NULL;
    *returnSize = 0;
    if (root == NULL){
        return result;
    }
    result = (int*)malloc(100 * sizeof (int));
    memset(result, 0, 100 * sizeof (int));

    Stack_t* stack = initStack();
    push(stack, root);
    while (isEmptyStack(stack) == 0){
        struct TreeNode* node = (struct TreeNode*)pop(stack);
        result[*returnSize] = node->val;
        (*returnSize)++;
        push(stack, node->right);
        push(stack, node->left);
    }
    freeStack(stack);
    return result;
}

int main(){

    struct TreeNode* input = (struct TreeNode*)malloc(3 * sizeof (struct TreeNode));
    input->val = 3;
    input->left = input + 1;
    input->left->val = 1;
    input->left->left = NULL;
    input->left->right = NULL;
    input->right = input + 2;
    input->right->val = 2;
    input->right->left = NULL;
    input->right->right = NULL;
    int a = 0;
    int* returnSize = &a;
    int* output = preorderTraversal(input, returnSize);
    printf("%d\n",*returnSize);
    for(int i = 0; i < 3; i++)
    {
        printf("%d\n",output[i]);
    }
    free(output);
    free(input);
    return 0;
}