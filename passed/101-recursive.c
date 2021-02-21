//
// Created by zhuoran liu on 2021/2/19.
//

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


bool recursive(struct TreeNode* left, struct TreeNode* right){
    if (left == NULL && right == NULL){
        return true;
    }else if (left == NULL || right == NULL){
        return false;
    }
    bool result = (left->val == right->val) && (recursive(left->left, right->right)) && (recursive(left->right, right->left));
    return result;
}

bool isSymmetric(struct TreeNode* root){
    return recursive(root, root);
}