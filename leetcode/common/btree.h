/* 이진 트리 문제 공용 도구 모음이에요.
 *
 * 쓰는 법은 문제 파일 맨 위에서 이 한 줄이면 돼요.
 *
 *     #include "common/btree.h"
 *
 * llist.h 와 같은 기준으로 나눠놨어요. "트리 문제라면 무조건 똑같은 것"만
 * 여기 들어옵니다. 만들고, 배열로 옮기고, 해제하고, 찍어보는 네 가지요.
 * 케이스를 어떻게 비교할지는 문제마다 달라서 각 파일에 남겨뒀어요 ( ˶ˆᗜˆ˵ )
 */

#ifndef LEETCODE_COMMON_BTREE_H
#define LEETCODE_COMMON_BTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/* LeetCode 가 C 트리 문제에서 주는 정의 그대로예요.
 *
 * llist.h 와 똑같이 typedef 가 없어요. 그래서 이 타입의 이름은
 * `struct TreeNode` 두 단어 통째고, `TreeNode` 한 단어는 존재하지 않아요.
 * 로컬에서만 typedef 를 달면 여기선 통과하는데 제출하면 컴파일이 깨지니까
 * 일부러 맞춰뒀습니다.
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


/* 문제에 나오는 [1,2,null,3] 의 그 null 자리예요.
 *
 * 값으로 쓸 수 없는 수여야 해서 int 의 최솟값을 빌려 썼어요. 문제의 제약이
 * -10^4 <= val <= 10^4 니까 이 값이 진짜 노드 값으로 들어올 일은 없습니다.
 */
#define BT_NULL INT_MIN


static inline struct TreeNode *bt_new(int val)
{
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    if (node == NULL) {
        printf("malloc 실패\n");
        exit(1);
    }
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}


/* 레벨 순서 배열을 트리로 세워요. LeetCode 입력칸에 적는 그 표기 그대로예요.
 *
 *     {1, 2, 3}                 ->      1          {1, 2, BT_NULL, 3}  ->    1
 *                                      / \                                 /
 *                                     2   3                               2
 *                                                                        /
 *                                                                       3
 *
 * 위에서부터 한 줄씩 채우면서, 꺼낸 노드마다 배열의 다음 두 칸을 왼쪽·오른쪽
 * 자식으로 가져가요. BT_NULL 칸은 자리만 차지하고 노드를 안 만들고요.
 */
static inline struct TreeNode *bt_build(const int *values, int n)
{
    if (n <= 0 || values[0] == BT_NULL)
        return NULL;

    struct TreeNode **queue = malloc(sizeof(struct TreeNode *) * (size_t)n);
    if (queue == NULL) {
        printf("malloc 실패\n");
        exit(1);
    }

    struct TreeNode *root = bt_new(values[0]);
    int head = 0, tail = 0, i = 1;
    queue[tail++] = root;

    while (head < tail && i < n) {
        struct TreeNode *node = queue[head++];

        if (i < n) {
            int v = values[i++];
            if (v != BT_NULL) {
                node->left = bt_new(v);
                queue[tail++] = node->left;
            }
        }
        if (i < n) {
            int v = values[i++];
            if (v != BT_NULL) {
                node->right = bt_new(v);
                queue[tail++] = node->right;
            }
        }
    }

    free(queue);
    return root;
}


/* 트리를 다시 레벨 순서 배열로 옮겨 담고, 옮긴 개수를 돌려줘요.
 * 담을 자리가 모자라면 -1 이고요.
 *
 * 들어간 모양과 나온 모양을 같은 표기로 맞춰주니까, 호출 전후를 비교하는
 * 데 쓸 수 있어요. 끝쪽의 null 은 잘라내서 {1,2} 와 {1,2,null} 이 같은
 * 결과로 나옵니다.
 */
static inline int bt_to_array(struct TreeNode *root, int *out, int cap)
{
    if (root == NULL)
        return 0;

    struct TreeNode **queue = malloc(sizeof(struct TreeNode *) * (size_t)cap);
    if (queue == NULL) {
        printf("malloc 실패\n");
        exit(1);
    }

    int n = 0, head = 0, tail = 0;
    queue[tail++] = root;

    while (head < tail) {
        struct TreeNode *node = queue[head++];

        if (n >= cap) {
            free(queue);
            return -1;
        }
        if (node == NULL) {
            out[n++] = BT_NULL;
            continue;
        }

        out[n++] = node->val;

        if (tail + 2 > cap) {
            free(queue);
            return -1;
        }
        queue[tail++] = node->left;
        queue[tail++] = node->right;
    }

    free(queue);

    while (n > 0 && out[n - 1] == BT_NULL)
        n--;

    return n;
}


static inline void bt_free(struct TreeNode *root)
{
    if (root == NULL)
        return;
    bt_free(root->left);
    bt_free(root->right);
    free(root);
}


/* [1, 2, null] 처럼 찍어줘요. 빈 트리는 [] 고요. */
static inline void bt_print_array(const int *a, int n)
{
    printf("[");
    for (int i = 0; i < n; i++) {
        if (i > 0)
            printf(", ");
        if (a[i] == BT_NULL)
            printf("null");
        else
            printf("%d", a[i]);
    }
    printf("]");
}

#endif /* LEETCODE_COMMON_BTREE_H */
