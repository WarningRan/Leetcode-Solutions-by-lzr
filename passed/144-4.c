//
// Created by zhuoran liu on 2021/2/8.
//

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "lzr_stack.h"

#define MALLOC_CHECK_ 3
#define DEBUG
//Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int* preorderTraversal(struct TreeNode* root, int* returnSize){
    int* result = NULL;
    *returnSize = 0;
    if (root == NULL){
        return result;
    }
    result = (int*)malloc(100 * sizeof (int));
    memset(result, 0, 100 * sizeof (int));
    struct TreeNode* temp_pop = NULL;
    void* stack = initStack();
    push(stack, root);
    while (isEmptyStack(stack) == 0){
        struct TreeNode* node = (struct TreeNode*)getStackTopData(stack);
        if (temp_pop == node->left && node->left != NULL){
            if(node->right == NULL){
                temp_pop = (struct TreeNode*)pop(stack);
            }else {
                push(stack, node->right);
            }
        }else if(temp_pop == node->right && node->right != NULL){
            temp_pop = (struct TreeNode*)pop(stack);
        }else {
            result[*returnSize] = node->val;
            (*returnSize)++;
            if(node->left != NULL){
                push(stack, node->left);
            } else if (node->right != NULL){
                push(stack, node->right);
            } else {
                temp_pop = (struct TreeNode*)pop(stack);
            }
        }
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