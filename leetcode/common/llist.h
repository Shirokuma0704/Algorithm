/* 연결 리스트 문제 공용 도구 모음이에요.
 *
 * 쓰는 법은 문제 파일 맨 위에서 이 한 줄이면 돼요.
 *
 *     #include "common/llist.h"
 *
 * 여기 들어오는 건 "연결 리스트 문제라면 무조건 똑같은 것"들만이에요.
 * 만들고, 배열로 옮기고, 해제하고, 찍어보는 네 가지요.
 * 케이스를 어떻게 비교할지는 문제마다 달라서 각 파일에 남겨뒀어요 ( ˶ˆᗜˆ˵ )
 */

#ifndef LEETCODE_COMMON_LLIST_H
#define LEETCODE_COMMON_LLIST_H

#include <stdio.h>
#include <stdlib.h>

/* LeetCode 가 C 문제에서 주는 정의 그대로예요.
 *
 * typedef 가 없다는 게 핵심입니다. 그래서 이 타입의 이름은
 * `struct ListNode` 두 단어 통째고, `ListNode` 한 단어는 존재하지 않아요.
 * 로컬에서만 typedef 를 달아두면 로컬은 통과하는데 제출하면 컴파일이
 * 깨지니까, 일부러 LeetCode 와 똑같이 맞춰뒀어요.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};


/* [1,2,3] -> 1 -> 2 -> 3 -> NULL */
static inline struct ListNode *ll_build(const int *values, int n)
{
    struct ListNode *head = NULL;
    for (int i = n - 1; i >= 0; i--) {
        struct ListNode *node = malloc(sizeof(struct ListNode));
        if (node == NULL) {
            printf("malloc 실패\n");
            exit(1);
        }
        node->val = values[i];
        node->next = head;
        head = node;
    }
    return head;
}

/* 리스트를 배열로 옮겨 담고, 옮긴 개수를 돌려줘요.
 * 순환이 생기면 무한 루프 대신 -1 을 돌려줍니다.
 */
static inline int ll_to_array(struct ListNode *head, int *out, int cap)
{
    int n = 0;
    struct ListNode *node = head;
    while (node != NULL) {
        if (n >= cap)
            return -1;          /* 담을 자리를 넘었어요. 거의 순환이에요 */
        out[n++] = node->val;
        node = node->next;
    }
    return n;
}

static inline void ll_free(struct ListNode *head)
{
    struct ListNode *node = head;
    while (node != NULL) {
        struct ListNode *next = node->next;
        free(node);
        node = next;
    }
}

/* 리스트의 맨 끝 노드를 돌려줘요. 비어 있으면 NULL 이고요.
 * 제자리에서 뒤집혔는지 같은 걸 확인할 때 쓰라고 넣어뒀어요.
 */
static inline struct ListNode *ll_tail(struct ListNode *head)
{
    if (head == NULL)
        return NULL;
    while (head->next != NULL)
        head = head->next;
    return head;
}

static inline void ll_print_array(const int *a, int n)
{
    printf("[");
    for (int i = 0; i < n; i++)
        printf(i == 0 ? "%d" : ", %d", a[i]);
    printf("]");
}

#endif /* LEETCODE_COMMON_LLIST_H */
