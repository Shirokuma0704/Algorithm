/* LeetCode 206. Reverse Linked List  —  C 버전
 *
 * 단일 연결 리스트의 head 를 받아서, 뒤집은 리스트의 head 를 돌려줘요.
 *
 * 제약:
 *     노드 개수 0 ~ 5000, -5000 <= val <= 5000
 *
 * 컴파일하고 돌리는 법 — 둘 중 편한 쪽으로요.
 *
 *   윈도우 (CLion 번들 MinGW, PATH 에 없어서 절대경로로 불러요)
 *     "C:/Program Files/JetBrains/CLion 2026.2.2/bin/mingw/bin/gcc.exe" \
 *         0206_reverse_linked_list.c -o 0206.exe && ./0206.exe
 *
 *   WSL (이쪽은 valgrind 랑 sanitizer 가 있어서 메모리까지 봐줘요)
 *     wsl.exe -d Ubuntu-22.04 -e bash -lc \
 *         'gcc -g -fsanitize=address 0206_reverse_linked_list.c -o 0206 && ./0206'
 *
 * 구조체 정의랑 도구 함수는 common/llist.h 로 빠졌어요.
 * LeetCode 가 주는 정의와 글자 하나까지 같아서, 아래 함수를 통째로 복사해
 * 붙여넣으면 손 볼 게 없어요 ⸜(๑'ᵕ'๑)⸝
 */

#include "common/llist.h"

#define MAXN 32   /* 로컬 케이스용 상한이에요. 문제의 5000 과는 상관없어요 */


/* ------------------------------------------------------------------ */
/* 여기부터 아래 함수 하나가 LeetCode 에 붙여넣을 전부예요              */
/* ------------------------------------------------------------------ */

/* 새 노드를 만들지 말고, 있는 노드의 next 방향만 뒤집으세요 (추가 공간 O(1)).
 * 돌려주는 건 리스트가 아니라 뒤집힌 리스트의 head 노드예요.
 *
 * 이 함수 안에 malloc 이 등장하면 방향이 틀어진 신호예요.
 * 노드를 새로 안 만드니까 free 할 것도 없고요.
 */
struct ListNode *reverseList(struct ListNode *head)
{
    if (head == NULL)
        return NULL;
    struct ListNode *next, *prev;
    prev = NULL;

    while (head != NULL)
    {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }

    return prev;
}


/* ------------------------------------------------------------------ */
/* 아래는 검산용이에요. 문제 풀이랑은 상관없으니 위만 보시면 돼요       */
/* ------------------------------------------------------------------ */

typedef struct {
    int in[MAXN];       int n_in;
    int expect[MAXN];   int n_expect;
} Case;

/* 앞의 세 개는 문제에 나온 예제예요. 뒤의 두 개는 직접 채우신 거고요. */
static Case CASES[] = {
    /* 입력            개수   기대 출력        개수 */
    { {1, 2, 3, 4, 5},  5,   {5, 4, 3, 2, 1},  5 },
    { {1, 2},           2,   {2, 1},           2 },
    { {0},              0,   {0},              0 },   /* 빈 리스트예요 */
    { {1},              1,   {1},              1 },
    { {-5, 1, -5},      3,   {-5, 1, -5},      3 },
};

int main(void)
{
    int total = (int)(sizeof(CASES) / sizeof(CASES[0]));
    int passed = 0;
    int got[MAXN];

    for (int i = 0; i < total; i++) {
        Case *c = &CASES[i];

        struct ListNode *head = ll_build(c->in, c->n_in);

        /* TODO: 제자리에서 뒤집었는지 확인하는 검사를 채워보세요.
         *
         * 지금 이 검산기는 값만 비교하기 때문에, 노드를 전부 새로 malloc 해서
         * 붙인 풀이도 그대로 통과해버려요. 문제가 요구하는 O(1) 추가 공간
         * 조건이 검산에서 빠져 있는 거죠.
         *
         * 뒤집기 전에 head 주소를 적어두면, 뒤집은 뒤 그 주소가 결과 리스트의
         * 맨 끝 노드여야 해요. 끝 노드를 찾아주는 ll_tail() 은 헤더에 넣어뒀고,
         * 둘을 비교하는 부분이 비어 있어요.
         */

        struct ListNode *out = reverseList(head);
        int n = ll_to_array(out, got, MAXN);

        printf("[%d] ", i + 1);

        if (n < 0) {
            printf("ERROR  입력 ");
            ll_print_array(c->in, c->n_in);
            printf(" -> 순환이 생겼거나 노드가 너무 많아요\n");
            continue;   /* 순환이면 해제도 못 돌려요 */
        }

        int ok = (n == c->n_expect);
        for (int k = 0; ok && k < n; k++)
            if (got[k] != c->expect[k])
                ok = 0;

        if (ok) {
            printf("PASS   입력 ");
            ll_print_array(c->in, c->n_in);
            printf(" -> ");
            ll_print_array(got, n);
            printf("\n");
            passed++;
        } else {
            printf("FAIL   입력 ");
            ll_print_array(c->in, c->n_in);
            printf("\n         기대 ");
            ll_print_array(c->expect, c->n_expect);
            printf("\n         실제 ");
            ll_print_array(got, n);
            printf("\n");
        }

        /* 뒤집힌 리스트를 해제해요. 제자리로 뒤집었다면 이 한 번으로 전부
         * 정리되고, 새 노드를 만들어 붙였다면 원래 노드들이 남아서
         * valgrind 에 누수로 찍혀요.
         */
        ll_free(out);
    }

    printf("\n%d/%d 통과\n", passed, total);
    return 0;
}
