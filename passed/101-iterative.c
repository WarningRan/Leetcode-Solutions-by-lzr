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
//#include "lzr_list.h"
#define DEBUG
typedef struct _container_node_t {
#ifdef DEBUG
    struct TreeNode* data;
#else
    void * data;
#endif
    struct _container_node_t* next;
    struct _container_node_t* last;
} container_node_t;

typedef struct _list_t {
    container_node_t* container_list_head;
    container_node_t* head;
    container_node_t* tail;
    int num;
} list_t;

void* initList () {
    list_t* list = (list_t*)malloc(sizeof (list_t));
    memset(list, 0, sizeof (list_t));
    return (void*)list;
}

void pushback(void * list, void* data){
    if (data == NULL){
        // printf("pushback NULL\n");
        return;
    }
    container_node_t* temp = ((list_t*)list)->tail;
    if (temp == NULL){
        if(((list_t*)list)->container_list_head == NULL) {
            ((list_t*)list)->container_list_head = (container_node_t*)malloc(sizeof (container_node_t));
            ((list_t*)list)->container_list_head->next = NULL;
            ((list_t*)list)->container_list_head->last = NULL;
        }
        ((list_t*)list)->tail = ((list_t*)list)->container_list_head;
        ((list_t*)list)->head = ((list_t*)list)->container_list_head;
    } else {
        ((list_t*)list)->tail = ((list_t*)list)->tail->next;
        if (((list_t*)list)->tail == NULL){
            ((list_t*)list)->tail = (container_node_t*)malloc(sizeof (container_node_t));
            ((list_t*)list)->tail->next = NULL;
            ((list_t*)list)->tail->last = temp;
            temp->next = ((list_t*)list)->tail;
        }
    }
    ((list_t*)list)->tail->data = data;
    ((list_t*)list)->num ++;
}

void* popfront (void * list){
    if (((list_t*)list)->head == NULL){
        // printf("popfront NULL\n");
        return NULL;
    }
    container_node_t* temp = ((list_t*)list)->head;
    ((list_t*)list)->head = ((list_t*)list)->head->next;
    ((list_t*)list)->num --;
    if(((list_t*)list)->num == 0){
        ((list_t*)list)->tail = NULL;
        ((list_t*)list)->head = NULL;
    }
    return temp->data;
}

void freeList (void * list){
    container_node_t* cur_container_node = ((list_t*)list)->container_list_head;
    while (cur_container_node != NULL){
        container_node_t* temp = cur_container_node;
        cur_container_node = temp->next;
        free(temp);
    }
    free(list);
}

bool iterative(struct TreeNode* left, struct TreeNode* right){
    list_t* list = (list_t*)initList();
    pushback(list, left);
    // printf("pushback1\n");
    pushback(list, right);
    // printf("pushback2\n");
    while(list->num != 0){
        left = (struct TreeNode*)popfront(list);
        right = (struct TreeNode*)popfront(list);
        if (left == NULL && right == NULL){
            continue;
        }
        if (left == NULL || right == NULL || (left->val != right->val)){
            return false;
        }

        if(left->left == NULL && right->right == NULL && left->right == NULL && right->left == NULL){
            continue;
        }
        if ((left->left == NULL && right->right != NULL) || (left->left != NULL && right->right == NULL) || (left->right != NULL && right->left == NULL) || (left->right == NULL && right->left != NULL)) {
            return false;
        }
        // && left->right->val ==
        if(left->left == NULL && right->right == NULL){
            pushback(list, left->right);
            // printf("pushback left->right\n");
            pushback(list, right->left);
            // printf("pushback right->left\n");
        }
        if (left->right == NULL && right->left == NULL){
            pushback(list, left->left);
            // printf("pushback left->left\n");
            pushback(list, right->right);
            // printf("pushback right->right\n");
        }
        if (left->left != NULL && right->right != NULL && left->right != NULL && right->left != NULL){
            pushback(list, left->left);
            // printf("pushback left->left\n");
            pushback(list, right->right);
            // printf("pushback right->right\n");
            pushback(list, left->right);
            // printf("pushback left->right\n");
            pushback(list, right->left);
            // printf("pushback right->left\n");
        }
    }
    freeList(list);
    return true;
}

bool isSymmetric(struct TreeNode* root){
    if (root == NULL){
        return true;
    }
    if (root->left == NULL && root->right == NULL){
        return true;
    }
    if (root->left == NULL || root->right == NULL || root->left->val != root->right->val){
        return false;
    }
    return iterative(root->left, root->right);
}

typedef struct TreeNode TreeNode_t;

TreeNode_t* transTreeNode(char* input_array, int input_array_length){
    TreeNode_t* root = (TreeNode_t*) malloc (sizeof (TreeNode_t));
    memset(root, 0, 5 * sizeof (TreeNode_t));
    list_t* list = (list_t*)initList();
    root->val = input_array[0];
    pushback(list, root);
    for (int index = 1; index < input_array_length; index++){
        TreeNode_t* cur_root = (TreeNode_t*)popfront(list);
        if(input_array[index] != NULL){
            cur_root->left = (TreeNode_t*) malloc (sizeof (TreeNode_t));
            cur_root->left->val = input_array[index];
            pushback(list, cur_root->left);
        }
        index++;
        if(input_array[index] != NULL){
            cur_root->right = (TreeNode_t*) malloc (sizeof (TreeNode_t));
            cur_root->right->val = input_array[index];
            pushback(list, cur_root->right);
        }
    }
    return root;
}

int main(){
    char input_array[106] = {6,97,97,NULL,79,79,NULL,NULL,-60,-60,NULL,-30,NULL,NULL,-30,-90,NULL,NULL,-90,NULL,-29,-29,NULL,-73,75,75,-73,-15,NULL,NULL,-36,-36,NULL,NULL,-15,27,NULL,NULL,23,23,NULL,NULL,27,82,NULL,80,NULL,NULL,80,NULL,82,38,NULL,-8,93,93,-8,NULL,38,18,NULL,-15,NULL,NULL,39,39,NULL,NULL,-15,NULL,18,NULL,-17,NULL,95,94,NULL,NULL,94,95,NULL,-17,NULL,51,NULL,88,NULL,95,NULL,NULL,95,NULL,88,NULL,51,NULL,-71,NULL,63,NULL,-62,-62,NULL,63,NULL,-71};
    int input_array_length = 106;
    TreeNode_t* input = transTreeNode(input_array, input_array_length);
    bool result = isSymmetric(input);
    // printf("bool=%d\n",result);
//    // printf("1=%d\n", input->val);
//    // printf("2=%d\n", input->left->val);
//    // printf("3=%d\n", input->right->val);
//    // printf("4=%d\n", input->left->right->val);
//    // printf("5=%d\n", input->right->right->val);
    return 0;
}