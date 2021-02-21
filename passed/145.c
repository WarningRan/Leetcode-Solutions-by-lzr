//
// Created by zhuoran liu on 2021/2/8.
//

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
//Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void postorder(struct TreeNode* root, int* index, int* result){
    if (root == NULL){
        return;
    }
    postorder(root->left, index, result);
    postorder(root->right, index, result);
    result[*index] = root->val;
    //int a = result[*index];
    (*index)++;
}

int* postorderTraversal(struct TreeNode* root, int* returnSize){
    int* result = (int*)malloc(100 * sizeof (int));
    memset(result, 0, 100 * sizeof (int));
    *returnSize = 0;
    postorder(root, returnSize, result);
    return result;
}

int main(){

    struct TreeNode* input = (struct TreeNode*)malloc(4 * sizeof (struct TreeNode*));
    input->val = 1;
    input->left = NULL;
    input->right = input + 1;
    input->right->val = 2;
    input->right->left = input + 2;
    input->right->left->val = 3;
    input->right->right = NULL;
    input->right->left->left = NULL;
    input->right->left->right = NULL;
    int a = 0;
    int* returnSize = &a;
    int* output = (int*)malloc(100 * sizeof (int));
    output = postorderTraversal(input, returnSize);
    printf("%d",*returnSize);
    for(int i = 0; i < 3; i++)
    {
        printf("%d\n",output[i]);
    }    return 0;
}