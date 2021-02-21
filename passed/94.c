//
// Created by zhuoran liu on 2021/2/7.
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

void inorder(struct TreeNode* root, int* index, int* result){
    if (root == NULL){
        return;
    }

    inorder(root->left, index, result);
    result[*index] = root->val;
    //int a = result[*index];
    (*index)++;
    inorder(root->right, index, result);
}

int* inorderTraversal(struct TreeNode* root, int* returnSize){
    int* result = (int*)malloc(100 * sizeof (int));
    memset(result, 0, 100 * sizeof (int));
    *returnSize = 0;
    inorder(root, returnSize, result);
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
    output = inorderTraversal(input, returnSize);
    printf("%d",*returnSize);
    for(int i = 0; i < 3; i++)
    {
        printf("%d\n",output[i]);
    }    return 0;
}