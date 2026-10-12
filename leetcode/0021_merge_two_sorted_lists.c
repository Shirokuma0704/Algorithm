/* LeetCode 21. Merge Two Sorted Lists  —  C 버전
 *
 * 오름차순(같은 값 허용)으로 정렬된 연결 리스트 list1, list2 의 head 를 받아요.
 * 두 리스트의 노드를 이어 붙여서 정렬된 리스트 하나로 만들고, 그 head 를 돌려줘요.
 * 10-07 에 파이썬으로 풀었고, 오늘은 C 로 백지에서 다시 짜는 날이에요.
 * 그날 .py 파일은 열지 않기로 해요 (｡•̀ᴗ-)✧
 *
 * 제약:
 *     두 리스트 각각 노드 0 ~ 50 개
 *     -100 <= Node.val <= 100
 *     두 리스트 모두 오름차순(같은 값 허용)으로 정렬돼 있어요
 *
 * 컴파일하고 돌리는 법 — 둘 중 편한 쪽으로요.
 *
 *   윈도우 (CLion 번들 MinGW, PATH 에 없어서 절대경로로 불러요)
 *     "C:/Program Files/JetBrains/CLion 2026.2.2/bin/mingw/bin/gcc.exe" \
 *         0021_merge_two_sorted_lists.c -o 0021.exe && ./0021.exe
 *
 *   WSL (이쪽은 valgrind 랑 sanitizer 가 있어서 메모리까지 봐줘요)
 *     wsl.exe -d Ubuntu-22.04 -e bash -lc \
 *         'gcc -g -fsanitize=address 0021_merge_two_sorted_lists.c -o 0021 && ./0021'
 *
 *   CLion 은 실행 목록에 안 보이면 "Reload CMake Project" 를 한 번 눌러주세요.
 *
 * 처음엔 함수 몸통이 비어 있어서 "control reaches end of non-void function" 경고가
 * 떠요. 그게 정상이고, 그 경고가 사라지는 게 첫 번째 목표예요.
 *
 * 구조체 정의랑 도구 함수는 common/llist.h 에 있어요. LeetCode 가 주는 정의와
 * 글자 하나까지 같아서, 아래 함수를 통째로 복사해 붙여넣으면 손 볼 게 없어요.
 */

#include <string.h>

#include "common/llist.h"

#define MAXN 64   /* 로컬 케이스용 상한이에요. 리스트 하나에 50 개까지라 넉넉하게 잡았어요 */


/* ------------------------------------------------------------------ */
/* 여기부터 아래 함수 하나가 LeetCode 에 붙여넣을 전부예요              */
/* ------------------------------------------------------------------ */

/* list1 과 list2 의 노드를 이어 붙여서 정렬된 리스트 하나로 만들고, 그 head 를 돌려주세요.
 *
 * 문제 원문이 "splicing together the nodes of the first two lists" 예요.
 * 받은 노드들의 next 만 다시 이어서 만들라는 뜻이에요. 값을 복사한 새 노드로
 * 만든 리스트는 출력이 맞아도 아래 검산기가 FAIL 로 잡아요.
 */
struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2)
{
    struct ListNode *tail, *temp;
    struct ListNode *base_list, *input_list;

    if (list1 == NULL || list2 == NULL)
    {
        if (list1 == NULL && list2 == NULL)
            return NULL;

        if (list1 == NULL)
            return list2;
        else
            return list1;
    }

    int r = 0;


    if (list1->val <= list2->val)
    {
        base_list = list1;
        input_list = list2;
    }
    else
    {
        base_list = list2;
        input_list = list1;
        r = 1;
    }

    if (list1->next == NULL && list2->next == NULL)
    {
        base_list->next = input_list;
        return base_list;
    }

    while (base_list->next != NULL)
    {
        if (input_list->next != NULL)
        {
            if (base_list->next->val >= input_list->val)
            {
                tail = base_list->next;
                temp = input_list->next;

                base_list->next = input_list;
                base_list->next->next = tail;
                input_list = temp;
            }
            else
            {
                base_list = base_list->next;
            }

        }
        else
        {
            if (base_list->next->val >= input_list->val)
            {
                tail = base_list->next;
                base_list->next = input_list;
                base_list->next->next = tail;
                base_list = base_list->next;
                if (r == 0) return list1;
                return list2;

            }
            base_list = base_list->next;
        }
    }

    if (input_list != NULL) base_list->next = input_list;
    if (r == 0) return list1;
    return list2;

}


/* ------------------------------------------------------------------ */
/* 아래는 검산용이에요. 문제 풀이랑은 상관없으니 위만 보시면 돼요       */
/* ------------------------------------------------------------------ */

/* 한 케이스 = 문자열 한 줄이에요.
 *
 *   "list1 | list2 -> 기대 결과"
 *
 *   숫자는 띄어쓰기로 나눠요.           "1 2 4 | 1 3 4 -> 1 1 2 3 4 4"
 *   빈 리스트는 [] 로 써요.              "[] | 0 -> 0"
 *
 * 문제에 나온 예제 세 개만 채워뒀어요. 나머지는 직접 만들어 주세요 — 반례 3개 룰이에요 ٩(ˊᗜˋ*)و
 * 주석을 풀어서 쓰시면 되고, 줄을 더 만드셔도 돼요.
 */
typedef struct {
    const char *name;
    const char *script;
} Case;

static const Case CASES[] = {
    { "예제1", "1 2 4 | 1 3 4 -> 1 1 2 3 4 4" },
    { "예제2", "[] | [] -> []" },
    { "예제3", "[] | 0 -> 0" },
    { "케이스4", " 5 | 1 2 4 -> 1 2 4 5" },
    /* { "케이스5", "" }, */
    /* { "케이스6", "" }, */
};


/* "1 2 4" 나 "[]" 같은 조각 하나를 숫자 배열로 바꿔요. 개수를 돌려주고, 못 읽으면 -1 이에요. */
static int parse_list(char *piece, int *out)
{
    int n = 0;
    char *tok = strtok(piece, " \t");
    while (tok != NULL) {
        if (strcmp(tok, "[]") != 0) {
            char *end;
            long v = strtol(tok, &end, 10);
            if (*end != '\0' || n >= MAXN)
                return -1;
            out[n++] = (int)v;
        }
        tok = strtok(NULL, " \t");
    }
    return n;
}

/* 배열이 오름차순(같은 값 허용)인지 봐요. 입력이 문제 조건을 어기면 알려주려고요. */
static int is_sorted(const int *a, int n)
{
    for (int i = 1; i < n; i++)
        if (a[i - 1] > a[i])
            return 0;
    return 1;
}

/* 리스트의 노드 주소를 seen 에 차례로 담고, 담은 개수를 돌려줘요. */
static int collect_nodes(struct ListNode *head, struct ListNode **seen, int count)
{
    for (struct ListNode *node = head; node != NULL; node = node->next)
        seen[count++] = node;
    return count;
}

static int run_case(const Case *c)
{
    char buf[512];
    if (strlen(c->script) >= sizeof(buf)) {
        printf("FAIL   %s: 케이스 문자열이 너무 길어요 (511 글자까지)\n", c->name);
        return 0;
    }
    strcpy(buf, c->script);

    char *arrow = strstr(buf, "->");
    char *bar = strchr(buf, '|');
    if (arrow == NULL || bar == NULL || bar > arrow) {
        printf("FAIL   %s: \"list1 | list2 -> 기대 결과\" 모양이 아니에요\n", c->name);
        return 0;
    }
    *bar = '\0';
    *arrow = '\0';

    int a[MAXN], b[MAXN], expect[MAXN];
    int na = parse_list(buf, a);
    int nb = parse_list(bar + 1, b);
    int ne = parse_list(arrow + 2, expect);
    if (na < 0 || nb < 0 || ne < 0) {
        printf("FAIL   %s: 숫자가 아닌 조각이 있어요. 숫자와 [] 만 쓸 수 있어요\n", c->name);
        return 0;
    }
    if (!is_sorted(a, na) || !is_sorted(b, nb)) {
        printf("FAIL   %s: 입력 리스트가 오름차순이 아니에요. 문제 조건부터 맞춰 주세요\n", c->name);
        return 0;
    }

    struct ListNode *list1 = ll_build(a, na);
    struct ListNode *list2 = ll_build(b, nb);

    /* 합치기 전에 원래 노드 주소를 모두 적어둬요. 결과가 이 노드들로만 이어졌는지 볼 거예요. */
    struct ListNode *original[2 * MAXN];
    int n_original = collect_nodes(list1, original, 0);
    n_original = collect_nodes(list2, original, n_original);

    struct ListNode *out = mergeTwoLists(list1, list2);

    /* 결과 리스트를 따라가며 값을 모으고, 노드마다 원래 노드인지, 두 번 나오지 않는지 봐요. */
    int got[2 * MAXN];
    int used[2 * MAXN] = {0};
    int n = 0;
    int new_node = 0, repeated = 0;
    for (struct ListNode *node = out; node != NULL; node = node->next) {
        if (n >= 2 * MAXN) {
            repeated = 1;               /* 원래 노드 수를 넘었어요. 거의 순환이에요 */
            break;
        }
        int k = 0;
        while (k < n_original && original[k] != node)
            k++;
        if (k == n_original) {
            new_node = 1;
        } else if (used[k]) {
            repeated = 1;               /* 같은 노드를 두 번 지나요. 순환이에요 */
            break;
        } else {
            used[k] = 1;
        }
        got[n++] = node->val;
    }

    printf("       ");
    ll_print_array(a, na);
    printf(" + ");
    ll_print_array(b, nb);
    printf("\n");

    if (repeated) {
        printf("FAIL   %s: 결과 리스트에 순환이 생겼어요. 같은 노드를 두 번 지나요\n", c->name);
        return 0;   /* 순환이면 해제도 못 돌려요 */
    }

    int ok = (n == ne);
    for (int k = 0; ok && k < n; k++)
        if (got[k] != expect[k])
            ok = 0;

    if (!ok) {
        printf("FAIL   %s\n         기대 ", c->name);
        ll_print_array(expect, ne);
        printf("\n         실제 ");
        ll_print_array(got, n);
        printf("\n");
    } else if (new_node) {
        printf("FAIL   %s: 값은 맞는데 결과에 새로 만든 노드가 섞여 있어요\n", c->name);
        printf("         받은 노드의 next 만 다시 이어서 만들어야 해요\n");
        ok = 0;
    } else {
        printf("PASS   %s -> ", c->name);
        ll_print_array(got, n);
        printf("\n");
    }

    /* 결과 리스트를 해제해요. 받은 노드를 전부 이어 붙였다면 이 한 번으로 다 정리되고,
     * 빠뜨린 노드가 있으면 valgrind 나 sanitizer 에 누수로 찍혀요.
     */
    ll_free(out);
    return ok;
}

int main(void)
{
    int total = (int)(sizeof(CASES) / sizeof(CASES[0]));
    int passed = 0;

    for (int i = 0; i < total; i++) {
        passed += run_case(&CASES[i]);
        printf("\n");
    }

    printf("%d/%d 통과\n", passed, total);
    return 0;
}
