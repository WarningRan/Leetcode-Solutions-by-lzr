//
// Created by zhuoran liu on 2021/1/23.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#define OUT

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* reverseBetween(struct ListNode* head, int m, int n){
    if (m == n || head == NULL || head->next == NULL){
        return head;
    }
    struct ListNode* cur = head, *pre = NULL, *next = NULL, *m_pre = NULL, *m_cur = NULL;
    int count = 1;
    while (cur != NULL && count <= n){

        next = cur->next;
        if (count == m){
            m_pre = pre;
            m_cur = cur;
        }
        if (count >= m){
            cur->next = pre;
        }
        if (count == n){
            if (m_pre != NULL){
                m_pre->next = cur;
            }
            m_cur->next = next;
            if (m == 1){
                head = cur;
            }
        }
        pre = cur;
        cur = next;
        count++;
    }
    return head;
}

//struct ListNode* reverseBetween(struct ListNode* head, int m, int n)
//{
//    if (m == n)
//        return head;
//
//    struct ListNode *prev = NULL, *next = NULL, *p = head;
//    // left is the m point left point, right is the m point
//    // left->next should be the n point, right->next should be the n->next point
//    struct ListNode *left = NULL, *right = NULL;
//    int count = 1;
//    while (p != NULL && count <= n)
//    {
//        next = p->next;
//
//        if (count == m)
//        {
//            left = prev;
//            right = p;
//        }
//
//        if (count >= m)
//            p->next = prev;
//
//        if (count == n)
//        {
//            if (left != NULL)
//                left->next = p;
//            right->next = next;
//
//            // if reverse from the original head, the new head should locate on the n point
//            // otherwise the head should be the original head
//            if (m == 1)
//                head = p;
//        }
//
//        prev = p;
//        p = next;
//        count++;
//    }
//    return head;
//}

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

    struct ListNode* output = reverseBetween(input1, 1, 5);
    printf("%d\n", output[0].val);
    printf("%d\n", output[1].val);
    printf("%d\n", output[2].val);
    printf("%d\n", output[3].val);
    printf("%d\n", output[4].val);
    return 0;
}