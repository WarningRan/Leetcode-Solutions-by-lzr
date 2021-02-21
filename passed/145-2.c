//
// Created by zhuoran liu on 2021/2/10.
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
#ifdef DEBUG
    printf("push %d\n", ((struct TreeNode*)data)->val);
#endif
}

void* pop(Stack_t* stack){
    if (stack->top == NULL){
        printf("pop null\n");
        return NULL;
    }
    ListNode1_t* temp = stack->top;
    stack->top = stack->top->last;
#ifdef DEBUG
    printf("pop %d\n", ((struct TreeNode*)temp->data)->val);
#endif
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


int* postorderTraversal(struct TreeNode* root, int* returnSize){
    int* result = NULL;
    *returnSize = 0;
    if (root == NULL){
        return result;
    }
    result = (int*)malloc(100 * sizeof (int));
    memset(result, 0, 100 * sizeof (int));
    struct TreeNode* temp_pop = NULL;
    Stack_t* stack = initStack();
    push(stack, root);
    while (isEmptyStack(stack) == 0){
        struct TreeNode* node = (struct TreeNode*)getStackTopData(stack);
        if (temp_pop == node->left && node->left != NULL){
            if (node->right == NULL){
                result[*returnSize] = node->val;
                (*returnSize)++;
                temp_pop = (struct TreeNode*)pop(stack);
                continue;
            }
            push(stack, node->right);
        }else if(temp_pop == node->right && node->right != NULL){
            result[*returnSize] = node->val;
            (*returnSize)++;
            temp_pop = (struct TreeNode*)pop(stack);
        }else {
            if(node->left != NULL){
                push(stack, node->left);
            }else if (node->right != NULL){
                push(stack, node->right);
            }else {
                result[*returnSize] = node->val;
                (*returnSize)++;
                temp_pop = (struct TreeNode*)pop(stack);
            }
        }
    }
    freeStack(stack);
    return result;
}

int main() {
    struct TreeNode *input = (struct TreeNode *) malloc(3 * sizeof(struct TreeNode));
    input =NULL;
//    input->val = 1;
//    input->left = NULL;
//    input->left->val = 2;
//    input->right = input + 2;
//    input->right->val = 2;
//    input->right->left = input + 3;
//    input->right->left->val = 3;
//    input->right->right = NULL;
    int a = 0;
    int *returnSize = &a;
    int *output = postorderTraversal(input, returnSize);
    printf("returnSize = %d\n", *returnSize);
//    for (int i = 0; i < 2; i++) {
//        printf("%d\n", output[i]);
//    }
    free(output);
    free(input);
    return 0;
}