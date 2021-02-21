//
// Created by zhuoran liu on 2021/2/16.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct TreeNode TreeNode_t;

typedef struct _container_node_t {
    void * data;
    struct _container_node_t* next;
    struct _container_node_t* last;
} container_node_t;

typedef struct _list_t {
    container_node_t* container_list_head;
    container_node_t* head;
    container_node_t* tail;
    int num;
} list_t;

typedef void (*traversal_func_t)(void* cur_traversal_data, void* out_data);

void* initList () {
    list_t* list = (list_t*)malloc(sizeof (list_t));
    memset(list, 0, sizeof (list_t));
    return (void*)list;
}

void pushback(void * list, void* data){
    if (data == NULL){
        printf("pushback null\n");
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

void pushfront (void * list, void* data){
    if (data == NULL){
        printf("pushfront null\n");
        return;
    }
    container_node_t* temp = ((list_t*)list)->head;
    if (temp == NULL){
        if(((list_t*)list)->container_list_head == NULL) {
            ((list_t*)list)->container_list_head = (container_node_t*)malloc(sizeof (container_node_t));
            ((list_t*)list)->container_list_head->next = NULL;
            ((list_t*)list)->container_list_head->last = NULL;
        }
        ((list_t*)list)->tail = ((list_t*)list)->container_list_head;
        ((list_t*)list)->head = ((list_t*)list)->container_list_head;
    } else {
        ((list_t*)list)->head = ((list_t*)list)->head->last;
        if (((list_t*)list)->head == NULL){
            ((list_t*)list)->head = (container_node_t*)malloc(sizeof (container_node_t));
            ((list_t*)list)->head->next = temp;
            ((list_t*)list)->head->last = NULL;
            temp->last = ((list_t*)list)->head;
            ((list_t*)list)->container_list_head = ((list_t*)list)->head;
        }
    }
    ((list_t*)list)->head->data = data;
    ((list_t*)list)->num ++;
}

void* popback (void * list){
    if (((list_t*)list)->tail == NULL){
        printf("popback null\n");
        return NULL;
    }
    container_node_t* temp = ((list_t*)list)->tail;
    ((list_t*)list)->tail = ((list_t*)list)->tail->last;
    ((list_t*)list)->num --;
    if(((list_t*)list)->num == 0){
        ((list_t*)list)->tail = NULL;
        ((list_t*)list)->head = NULL;
    }

    return temp->data;
}

void* popfront (void * list){
    if (((list_t*)list)->head == NULL){
        printf("popfront null\n");
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

int isEmptyList(void* list){
    int is_empty = 0;
    if (((list_t*)list)->tail == NULL){
        is_empty = 1;
    }
    return is_empty;
}

TreeNode_t* transTreeNode(char* input_array, int input_array_length){
    TreeNode_t* root = (TreeNode_t*) malloc (sizeof (TreeNode_t));
    memset(root, 0, 5 * sizeof (TreeNode_t));
    list_t* list = (list_t*)initList();
    root->val = input_array[0];
    pushback(list, root);

    for (int index = 1; index < input_array_length; index++){
        TreeNode_t* cur_root = (TreeNode_t*)popfront(list);
        if(input_array[index] != "NULL"){
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
    char input_array[7] = {3,9,20,NULL,NULL,15,7};
    int input_array_length = 7;
    TreeNode_t* input = transTreeNode(input_array, input_array_length);
    printf("1=%d\n", input->val);
    printf("2=%d\n", input->left->val);
    printf("3=%d\n", input->right->val);
    printf("4=%d\n", input->right->left->val);
    printf("5=%d\n", input->right->right->val);
    return 0;
}