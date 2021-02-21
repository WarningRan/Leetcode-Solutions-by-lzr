//
// Created by zhuoran liu on 2021/2/10.
//

#ifndef LEETCODE_LZR_STACK_H
#define LEETCODE_LZR_STACK_H

void* initStack ();

void push(void* stack, void* data);

void* pop(void* stack);

void freeStack(void* stack);

int isEmptyStack(void* stack);

void* getStackTopData(void* stack);

#endif //LEETCODE_LZR_STACK_H
