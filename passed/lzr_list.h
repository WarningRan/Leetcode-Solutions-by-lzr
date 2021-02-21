//
// Created by zhuoran liu on 2021/2/19.
//

#ifndef LEETCODE_LZR_LIST_H
#define LEETCODE_LZR_LIST_H

void* initList ();

void pushback(void * list, void* data);

void pushfront (void * list, void* data);

void* popback (void * list);

void* popfront (void * list);

void freeList (void * list);

int isEmptyList(void* list);

void* getListBackData(void* list);

void* getListFrontData(void* list);

void* getDataAtIndex(void* list, int index);

typedef void (*traversal_func_t)(void* cur_traversal_data, void* out_data);

void traversalFromHeadToEnd(void* list, traversal_func_t func, void* out_data);

void printTreeNodeValue(void* tree_node, void* out_data);

#endif //LEETCODE_LZR_LIST_H

