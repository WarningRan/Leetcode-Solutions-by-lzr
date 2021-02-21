//
// Created by zhuoran liu on 2021/2/20.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
};

bool tempPathSum (struct TreeNode* root, int targetSum, int temp_sum){
    if (root == NULL){
        return false;
    }
    temp_sum += root->val;
    if (root->left == NULL && root->right == NULL){
        if(temp_sum == targetSum){
            return true;
        }else {
            return false;
        }
    }
    return tempPathSum(root->left, targetSum, temp_sum) || tempPathSum(root->right, targetSum, temp_sum);

}

bool hasPathSum(struct TreeNode* root, int targetSum){

    return tempPathSum(root, targetSum, 0);
}

//bool hasPathSum(struct TreeNode* root, int targetSum){
//    if (root == NULL){
//        return false;
//    }
//    if (root->left == NULL && root->right == NULL){
//        return targetSum == root->val;
//    }
//    return hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val);
//}