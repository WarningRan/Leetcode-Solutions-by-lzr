//
// Created by zhuoran liu on 2021/2/22.
//

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

// Definition for a binary tree node.

struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
};

struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize){
    if (!inorder || !postorder){
        return NULL;
    }
    
}