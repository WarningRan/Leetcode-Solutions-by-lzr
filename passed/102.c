//
// Created by zhuoran liu on 2021/2/13.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

//Definition for a binary tree node.
struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
};

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

void* getListBackData(void* list){
    if (((list_t*)list)->tail == NULL){
        return NULL;
    }
    return ((list_t*)list)->tail->data;
}

void* getListFrontData(void* list){
    if (((list_t*)list)->head == NULL){
        return NULL;
    }
    return ((list_t*)list)->head->data;
}

void* getDataAtIndex(void* list, int index) {
    if (index >= ((list_t*)list)->num){
        printf("index is beyond the total num!\n");
        return NULL;
    }
    container_node_t* cur_node = ((list_t*)list)->head;
    for (int i = 0; i < index; i++) {
        cur_node = cur_node->next;
    }
    return cur_node->data;
}

void traversalFromHeadToEnd(void* list, traversal_func_t func, void* out_data) {
    if(func==NULL){
        return;
    }
    container_node_t* cur_container_node = ((list_t*)list)->head;
    while (cur_container_node){
        (*func)(cur_container_node->data, out_data);
        if(cur_container_node == ((list_t*)list)->tail) {
            break;
        }
        cur_container_node = cur_container_node->next;
    }
}

void printTreeNodeValue(void* tree_node, void* out_data) {
    printf("%d %d\n",((struct TreeNode*)tree_node)->val, *(int*)out_data);
    (*(int*)out_data) ++;
}

int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    *returnSize = 0;
    *returnColumnSizes = NULL;
    if (root == NULL){
        return NULL;
    }
    list_t* pop_list =(list_t*)initList ();
    list_t* push_list =(list_t*)initList ();
    list_t* return_array_list = (list_t*)initList ();
    list_t* return_array_size_list = (list_t*)initList ();
//    int length = 0;
    int index = 0;
    pushback(pop_list, root);
    int* length = (int*)malloc(sizeof (int));
    *length = 1;
    pushback(return_array_size_list, length);
    int* array = (int*)malloc(sizeof(int) * (*length));
    pushback(return_array_list, array);
    while (1){
        struct TreeNode* temp_pop = (struct TreeNode*)popfront(pop_list);
        array[index] = temp_pop->val;
        printf("%d \n", array[index]);
        index++;
        if (temp_pop->left){
            pushback(push_list, temp_pop->left);
        }
        if (temp_pop->right){
            pushback(push_list, temp_pop->right);
        }
        if (isEmptyList(pop_list)){
            list_t * temp_list = pop_list;
            pop_list = push_list;
            push_list = temp_list;
            if(pop_list->num > 0) {
                length = (int*)malloc(sizeof (int));
                *length = pop_list->num;
                pushback(return_array_size_list, length);
                array = (int*)malloc(sizeof(int) * (*length));
                pushback(return_array_list, array);
                index = 0;
            } else {
                break;
            }
        }
    }
    *returnSize = return_array_list->num;
    *returnColumnSizes = (int*)malloc(*returnSize * sizeof (int));
    int** result = (int**)malloc(*returnSize * sizeof (int*));
    for (int i = 0; i < (*returnSize); i++){
        (*returnColumnSizes)[i] = *(int*)popfront(return_array_size_list);
        result[i] = (int*)popfront(return_array_list);
    }
    freeList(pop_list);
    freeList(push_list);
    freeList(return_array_list);
    freeList(return_array_size_list);
    return result;
}

int main(){
    struct TreeNode* input = (struct TreeNode*)malloc(5 * sizeof (struct TreeNode));
    memset(input, 0, 5 * sizeof (struct TreeNode));
    input->val = 3;
    input->left = input + 1;
    input->left->val = 9;
//    input->left->left = NULL;
//    input->left->right = NULL;
    input->right = input + 2;
    input->right->val = 20;
    input->right->left = input + 3;
    input->right->left->val = 15;
    input->right->right = input + 4;
    input->right->right->val = 7;
    int a = 0;
    int* returnSize = &a;
    int** returnColumnSizes = (int**)malloc(sizeof (int*));
    int** output = levelOrder(input, returnSize, returnColumnSizes);
    printf("%d\n",*returnSize);
    for(int i = 0; i < *returnSize; i++)
    {
        printf("%d -- [", (*returnColumnSizes)[i]);
        for(int j = 0; j < (*returnColumnSizes)[i]; j++) {
            printf("%d ",output[i][j]);
        }
        printf("]\n");
    }
    free(output);
    free(input);
    return 0;
}