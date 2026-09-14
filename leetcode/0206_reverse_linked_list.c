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
 * 파이썬 버전이 옆에 나란히 있으니 (0206_reverse_linked_list.py)
 * 다 짜고 나서 두 파일을 같이 열어보시면 재밌을 거예요 ( ˶ˆ ᗜ ˆ˵ )
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXN 32   /* 로컬 케이스용 상한이에요. 문제의 5000 과는 상관없어요 */

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;   /* LeetCode 가 주는 정의 그대로예요 */


/* ------------------------------------------------------------------ */
/* 여기만 채우면 돼요                                                   */
/* ------------------------------------------------------------------ */

/* 새 노드를 만들지 말고, 있는 노드의 next 방향만 뒤집으세요 (추가 공간 O(1)).
 * 돌려주는 건 리스트가 아니라 뒤집힌 리스트의 head 노드예요.
 *
 * 이 함수 안에 malloc 이 등장하면 방향이 틀어진 신호예요.
 * 노드를 새로 안 만드니까 free 할 것도 없고요.
 */
ListNode *reverseList(ListNode *head)
{
    if (head == NULL)
        return NULL;
    ListNode *next, *prev;
    prev = NULL;

    while (head != NULL)
    {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }

    return prev;   /* <- 다 짜면 이 줄은 없어져요 */
}


/* ------------------------------------------------------------------ */
/* 아래는 검산용 도구예요. 문제 풀이랑은 상관없으니 위만 채우면 돼요     */
/* ------------------------------------------------------------------ */

/* [1,2,3] -> 1 -> 2 -> 3 -> NULL */
static ListNode *build(const int *values, int n)
{
    ListNode *head = NULL;
    for (int i = n - 1; i >= 0; i--) {
        ListNode *node = malloc(sizeof(ListNode));
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

/* 리스트를 배열로 옮겨 담아요. 돌려주는 값은 옮긴 개수고요.
 * 순환이 생기면 무한 루프 대신 -1 을 돌려줍니다.
 */
static int to_array(ListNode *head, int *out, int cap)
{
    int n = 0;
    ListNode *node = head;
    while (node != NULL) {
        if (n >= cap)
            return -1;          /* 담을 자리를 넘었어요. 거의 순환이에요 */
        out[n++] = node->val;
        node = node->next;
    }
    return n;
}

static void destroy(ListNode *head)
{
    ListNode *node = head;
    while (node != NULL) {
        ListNode *next = node->next;
        free(node);
        node = next;
    }
}

static void print_array(const int *a, int n)
{
    printf("[");
    for (int i = 0; i < n; i++)
        printf(i == 0 ? "%d" : ", %d", a[i]);
    printf("]");
}


typedef struct {
    int in[MAXN];       int n_in;
    int expect[MAXN];   int n_expect;
} Case;

/* 앞의 세 개는 문제에 나온 예제예요.
 * 나머지 두 줄은 비워뒀어요 — 어떤 입력에서 깨질지 직접 정해서 채워주세요.
 * (기대값도 손으로 먼저 계산해서 적어둔 다음에 돌리는 거예요)
 */
static Case CASES[] = {
    /* 입력            개수   기대 출력        개수 */
    { {1, 2, 3, 4, 5},  5,   {5, 4, 3, 2, 1},  5 },
    { {1, 2},           2,   {2, 1},           2 },
    { {0},              0,   {0},              0 },   /* 빈 리스트예요 */
    { {1}, 1,   {1},1},
    { {-5, 1, -5},3 ,   { -5,1,-5  }, 3 }
};

int main(void)
{
    int total = (int)(sizeof(CASES) / sizeof(CASES[0]));
    int passed = 0;
    int got[MAXN];

    for (int i = 0; i < total; i++) {
        Case *c = &CASES[i];

        ListNode *head = build(c->in, c->n_in);

        /* TODO: 제자리에서 뒤집었는지 확인하는 검사를 채워보세요.
         *
         * 지금 이 검산기는 값만 비교하기 때문에, 노드를 전부 새로 malloc 해서
         * 붙인 풀이도 그대로 통과해버려요. 문제가 요구하는 O(1) 추가 공간
         * 조건이 검산에서 빠져 있는 거죠.
         *
         * 뒤집기 전에 head 주소를 따로 적어두면, 뒤집은 뒤 그 주소가 결과
         * 리스트의 맨 끝 노드여야 해요. 그 한 줄을 확인하는 부분이 비어 있어요.
         *
         * (WSL 에서 valgrind 나 -fsanitize=address 로 돌리면 같은 실수가
         *  메모리 누수로도 잡혀요. 두 방향 다 해보시면 좋아요)
         */

        ListNode *out = reverseList(head);
        int n = to_array(out, got, MAXN);

        printf("[%d] ", i + 1);

        if (n < 0) {
            printf("ERROR  입력 ");
            print_array(c->in, c->n_in);
            printf(" -> 순환이 생겼거나 노드가 너무 많아요\n");
            continue;   /* 순환이면 destroy 도 못 돌려요 */
        }

        int ok = (n == c->n_expect);
        for (int k = 0; ok && k < n; k++)
            if (got[k] != c->expect[k])
                ok = 0;

        if (ok) {
            printf("PASS   입력 ");
            print_array(c->in, c->n_in);
            printf(" -> ");
            print_array(got, n);
            printf("\n");
            passed++;
        } else {
            printf("FAIL   입력 ");
            print_array(c->in, c->n_in);
            printf("\n         기대 ");
            print_array(c->expect, c->n_expect);
            printf("\n         실제 ");
            print_array(got, n);
            printf("\n");
        }

        /* 뒤집힌 리스트를 해제해요. 제자리로 뒤집었다면 이 한 번으로 전부
         * 정리되고, 새 노드를 만들어 붙였다면 원래 노드들이 남아서
         * valgrind 에 누수로 찍혀요.
         */
        destroy(out);
    }

    printf("\n%d/%d 통과\n", passed, total);
    return 0;
}
