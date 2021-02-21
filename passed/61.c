//
// Created by zhuoran liu on 2021/1/24.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* rotateRight(struct ListNode* head, int k){
    if(head == NULL|| head->next == NULL){
        return head;
    }
    int len = 0;
    struct ListNode* temp = head;
    while(temp != NULL){
        len++;
        temp = temp->next;
    }
    k = k % len;
    if (k == 0){
        return head;
    }
    int count = 1;
    struct ListNode* cur = head, *next, *ori_head;
    while(count <= len){
        next = cur->next;
        if (count == len - k){
            ori_head = head;
            head = next;
            cur->next = NULL;
        }
        if (count == len){
            cur->next = ori_head;
        }
        cur = next;
        count++;
    }
    return head;
}

int main(){
    struct ListNode* input1 = (struct ListNode*)malloc (6 * sizeof (struct ListNode));
    input1->val = 1;
    input1->next = input1 + 1;

    input1->next->val = 2;
    input1->next->next = input1 + 2;

    input1->next->next->val = 3;
    input1->next->next->next = input1 + 3;

    input1->next->next->next->val = 4;
    input1->next->next->next->next = input1 + 4;

    input1->next->next->next->next->val = 5;
    input1->next->next->next->next->next = NULL;

    struct ListNode* output = rotateRight(input1, 1);

    printf("%d\n", output[0].val);
    printf("%d\n", output[1].val);
    printf("%d\n", output[2].val);
    printf("%d\n", output[3].val);
    printf("%d\n", output[4].val);
    return 0;
}