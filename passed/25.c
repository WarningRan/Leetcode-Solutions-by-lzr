//
// Created by zhuoran liu on 2021/1/31.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* reverseKGroup(struct ListNode* head, int k){
    if(head == NULL|| head->next == NULL || k == 1){
        return head;
    }
    int len = 0;
    struct ListNode* temp = head;
    while(temp != NULL){
        len++;
        temp = temp->next;
    }

    int group_num = len/k;
    int nodes_for_reverse = group_num *k;

    struct ListNode* cur = head, *next = head->next, *pre = NULL;
    struct ListNode* group_head = NULL, *group_pre = NULL, *group_next = NULL;
    struct ListNode* temp_cur = NULL, *temp_pre = NULL, *temp_next = NULL;
    for(int index = 1; index <= nodes_for_reverse; index++){
        next = cur->next;
        if(index%k ==1){
            group_head = cur;
        }
        if(index%k ==0){
            temp_pre = group_pre;
            temp_cur = group_head;
            group_next = cur->next;
            for(int i = index - k + 1; i <= index; i++){
                temp_next = temp_cur->next;
                if(i > index - k + 1){
                    temp_cur->next = temp_pre;
                }

                if(i == index){
                    if(group_pre !=NULL){
                        group_pre->next = temp_cur;
                    }
                    group_head->next = group_next;

                }
                temp_pre = temp_cur;
                temp_cur = temp_next;
            }
            if(index < 2*k){
                head = cur;
            }

            group_pre= group_head;
        }

        pre = cur;
        cur = next;
    }

    return head;
}

int main(){
    struct ListNode* input1 = (struct ListNode*)malloc (7 * sizeof (struct ListNode));
    input1->val = 1;
    input1->next = input1 + 1;

    input1->next->val = 2;
    input1->next->next = input1 + 2;

    input1->next->next->val = 3;
    input1->next->next->next = input1 + 3;

    input1->next->next->next->val = 4;
    input1->next->next->next->next = input1 + 4;

    input1->next->next->next->next->val = 5;
    input1->next->next->next->next->next = input1 + 5;

    input1->next->next->next->next->next->val = 6;
    input1->next->next->next->next->next->next = NULL;

    struct ListNode* output = reverseKGroup(input1, 3);

    printf("%d\n", output[0].val);
    printf("%d\n", output[1].val);
    printf("%d\n", output[2].val);
    printf("%d\n", output[3].val);
    printf("%d\n", output[4].val);

    free(input1);
    return 0;
}