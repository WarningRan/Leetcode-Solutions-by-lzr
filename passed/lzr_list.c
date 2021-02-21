//
// Created by zhuoran liu on 2021/2/19.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lzr_list.h"
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