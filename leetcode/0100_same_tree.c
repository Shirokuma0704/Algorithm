/* LeetCode 100. Same Tree  —  C 버전
 *
 * 두 이진 트리의 root 를 받아서, 둘이 같은 트리인지 돌려줘요.
 * 여기서 "같다"는 모양도 같고 각 자리의 값도 같다는 뜻이에요.
 *
 * 제약:
 *     각 트리의 노드 개수 0 ~ 100, -10^4 <= val <= 10^4
 *
 * 컴파일하고 돌리는 법 — 둘 중 편한 쪽으로요.
 *
 *   윈도우 (CLion 번들 MinGW, PATH 에 없어서 절대경로로 불러요)
 *     "C:/Program Files/JetBrains/CLion 2026.2.2/bin/mingw/bin/gcc.exe" \
 *         0100_same_tree.c -o 0100.exe && ./0100.exe
 *
 *   WSL (이쪽은 valgrind 랑 sanitizer 가 있어서 메모리까지 봐줘요)
 *     wsl.exe -d Ubuntu-22.04 -e bash -lc \
 *         'gcc -g -fsanitize=address 0100_same_tree.c -o 0100 && ./0100'
 *
 * 구조체 정의랑 도구 함수는 common/btree.h 로 빠졌어요.
 * LeetCode 가 주는 정의와 글자 하나까지 같아서, 아래 함수를 통째로 복사해
 * 붙여넣으면 손 볼 게 없어요 ⸜(๑'ᵕ'๑)⸝
 *
 * 처음 한 번은 컴파일 경고가 뜨는 게 정상이에요. 아래 함수 몸통이 비어 있어서
 * "control reaches end of non-void function" 이 나옵니다. 그 경고가 사라지는
 * 게 첫 번째 목표예요.
 */

#include "common/btree.h"

#define MAXN 64   /* 로컬 케이스용 상한이에요. 문제의 100 과는 상관없어요 */
#define NA BT_NULL   /* 케이스 표에서 문제의 null 자리를 짧게 쓰려고요 */


/* ------------------------------------------------------------------ */
/* 여기부터 아래 함수 하나가 LeetCode 에 붙여넣을 전부예요              */
/* ------------------------------------------------------------------ */

/* 두 트리가 같으면 true, 아니면 false 를 돌려주세요.
 *
 * 받은 트리는 읽기만 하고 바꾸지 마세요. 값을 고치거나 노드를 떼어내면
 * 안 되고, 새 노드를 만들 일도 없어요 (그러니까 malloc 도 free 도 안 나와요).
 *
 * p 나 q 가 NULL 로 들어올 수 있어요. 빈 트리 두 개는 서로 같은 트리예요.
 */
bool isSameTree(struct TreeNode *p, struct TreeNode *q)
{
    if (p == NULL || q == NULL){
        if (p == NULL && q == NULL)
            return true;
        return false;
    }


    if (q->val != p->val)
        return false;


    bool left_result = true, right_result = true;

    left_result = isSameTree(p->left, q->left);

    right_result = isSameTree(p->right, q->right);

    if (left_result != true || right_result != true)
        return false;

    return true;

}


/* ------------------------------------------------------------------ */
/* 아래는 검산용이에요. 문제 풀이랑은 상관없으니 위만 보시면 돼요       */
/* ------------------------------------------------------------------ */

typedef struct {
    int p[MAXN];   int np;
    int q[MAXN];   int nq;
    int expect;    /* 같으면 1, 다르면 0 */
} Case;

/* 앞의 세 개는 문제에 나온 예제예요.
 *
 * 그 뒤는 비워뒀어요. 이번 주 과제가 테스트를 안 주는 것과 같은 이유예요 —
 * 경계를 찾아내는 게 연습의 본체라서요. 문제의 제약 두 줄을 다시 읽으면서,
 * 이 세 개가 건드리지 않는 입력이 뭔지 찾아 채워보세요.
 *
 * 채울 때 하나만 봐주세요. 기대값이 0 인 케이스만 늘리면, 무조건 false 를
 * 돌려주는 풀이도 전부 통과해버려요. README 의 "통과는 증거가 아니다" 가
 * 이 자리예요 ( •̀ ω •́ )✧
 */
static Case CASES[] = {
    /* p 입력        개수  q 입력        개수  기대 */
    { {1, 2, 3},      3,   {1, 2, 3},      3,   1 },
    { {1, 2},         2,   {1, NA, 2},     3,   0 },
    { {1, 2, 1},      3,   {1, 1, 2},      3,   0 },

    /* 주석을 풀고 채워주세요. 줄이 모자라면 더 늘리셔도 돼요. */
     { { 1         },   1,   { 1        },   1,   1 },
    { {NA         },   0,   {NA         },   0,   1 },
{ {2,1          },   2,   {NA          },   0,   0 }
};

int main(void)
{
    int total = (int)(sizeof(CASES) / sizeof(CASES[0]));
    int passed = 0;

    for (int i = 0; i < total; i++) {
        Case *c = &CASES[i];

        struct TreeNode *p = bt_build(c->p, c->np);
        struct TreeNode *q = bt_build(c->q, c->nq);

        /* TODO: 호출 뒤에도 두 트리가 그대로인지 확인하는 검사를 채워보세요.
         *
         * 지금 이 검산기는 돌려받은 true/false 하나만 봐요. 그래서 비교하는
         * 김에 한쪽 트리의 값을 덮어쓰거나 자식을 떼어낸 풀이도 그대로
         * 통과해버립니다. 문제가 요구하는 "읽기만 한다" 조건이 검산에서
         * 빠져 있는 거예요.
         *
         * bt_to_array() 가 트리를 레벨 순서 배열로 옮겨줘요. 호출 전에 한 번
         * 떠두고 호출 뒤에 한 번 더 떠서, 두 배열이 글자 그대로 같은지 보면
         * 됩니다. 떠둔 걸 어디에 담아둘지와 두 배열을 맞대보는 부분이
         * 비어 있어요.
         */

        bool got = isSameTree(p, q);
        int ok = (got == (c->expect != 0));

        printf("[%d] ", i + 1);

        if (ok) {
            printf("PASS   ");
            bt_print_array(c->p, c->np);
            printf(" vs ");
            bt_print_array(c->q, c->nq);
            printf(" -> %s\n", got ? "true" : "false");
            passed++;
        } else {
            printf("FAIL   ");
            bt_print_array(c->p, c->np);
            printf(" vs ");
            bt_print_array(c->q, c->nq);
            printf("\n         기대 %s\n", c->expect ? "true" : "false");
            printf("         실제 %s\n", got ? "true" : "false");
        }

        /* 두 트리 다 해제해요. 풀이가 노드를 새로 만들어 붙였다면 여기서
         * 정리가 안 되고 valgrind 에 누수로 찍힙니다.
         */
        bt_free(p);
        bt_free(q);
    }

    printf("\n%d/%d 통과\n", passed, total);
    return 0;
}
