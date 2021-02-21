//
// Created by zhuoran liu on 2021/2/19.
//
//Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int maxDepth(struct TreeNode* root){
    if (root == NULL){
        return 0;
    }
    return fmax ((maxDepth (root -> left) + 1), (maxDepth (root -> right) + 1));
}