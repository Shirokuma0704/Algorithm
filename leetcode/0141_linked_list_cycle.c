/* LeetCode 141. Linked List Cycle  —  C 버전
 *
 * 연결 리스트의 head 를 받아서, 리스트 안에 순환(cycle)이 있으면 true, 없으면 false 를 돌려줘요.
 * 10-13 에 파이썬으로 풀었고, 오늘은 C 로 백지에서 다시 짜는 날이에요.
 * 그날 .py 파일은 열지 않기로 해요 (｡•̀ᴗ-)✧
 *
 * 순환이란: 어떤 노드의 next 를 계속 따라가다 보면 이미 지나온 노드로 다시 돌아오는 것.
 * 문제 설명의 pos 는 "꼬리가 몇 번째 노드로 이어지는지"인데, 함수에는 안 넘어와요.
 * 함수가 받는 건 head 하나뿐이에요.
 *
 * 제약:
 *     노드 개수 0 ~ 10^4
 *     -10^5 <= Node.val <= 10^5        값은 겹칠 수 있어요
 *     pos 는 -1(순환 없음) 이거나 리스트 안의 올바른 위치
 *
 * 더 해 보기 (LeetCode 의 Follow up): 메모리를 O(1) 만 쓰고 풀 수 있나요?
 *
 * 컴파일하고 돌리는 법 — 둘 중 편한 쪽으로요.
 *
 *   윈도우 (CLion 번들 MinGW, PATH 에 없어서 절대경로로 불러요)
 *     "C:/Program Files/JetBrains/CLion 2026.2.2/bin/mingw/bin/gcc.exe" \
 *         0141_linked_list_cycle.c -o 0141.exe && ./0141.exe
 *
 *   WSL (이쪽은 valgrind 랑 sanitizer 가 있어서 메모리까지 봐줘요)
 *     wsl.exe -d Ubuntu-22.04 -e bash -lc \
 *         'gcc -g -fsanitize=address 0141_linked_list_cycle.c -o 0141 && ./0141'
 *
 *   CLion 은 실행 목록에 안 보이면 "Reload CMake Project" 를 한 번 눌러주세요.
 *
 * 처음엔 함수 몸통이 비어 있어서 "control reaches end of non-void function" 경고가
 * 떠요. 그게 정상이고, 그 경고가 사라지는 게 첫 번째 목표예요.
 *
 * 돌렸는데 아무것도 안 찍히고 멈춰 있으면, 순환이 있는 케이스에서 반복이 안 끝나는 거예요.
 * Ctrl+C 로 끊으면 돼요. 마지막으로 찍힌 케이스 다음 줄이 범인이에요.
 *
 * 구조체 정의는 common/llist.h 에 있어요. LeetCode 가 주는 정의와 글자 하나까지 같아서,
 * 아래 함수를 통째로 복사해 붙여넣으면 손 볼 게 없어요.
 */

#include <stdbool.h>
#include <string.h>

#include "common/llist.h"

#define MAXN 64   /* 로컬 케이스용 상한이에요. 문제의 10^4 와는 상관없어요 */


/* ------------------------------------------------------------------ */
/* 여기부터 아래 함수 하나가 LeetCode 에 붙여넣을 전부예요              */
/* ------------------------------------------------------------------ */


bool hasCycle(struct ListNode *head)
{
    struct ListNode *curr = head;
    bool result = false;

    while (curr != NULL) {
        if (abs(curr->val) > 1e5) {
            result = true;
            break;
        }

        curr->val ^= (1 << 30);
        curr = curr->next;
    }

    curr = head;
    while (curr != NULL) {
        if (abs(curr->val) <= (1e5)) return result;

        curr->val ^= (1 << 30);
        curr = curr->next;
    };

    return result;
}


/* ------------------------------------------------------------------ */
/* 아래는 검산용이에요. 문제 풀이랑은 상관없으니 위만 보시면 돼요       */
/* ------------------------------------------------------------------ */

/* 한 케이스 = 한 줄이에요. 파이썬 버전과 같은 모양이에요.
 *
 *   "3 2 0 -4 @ 1 -> true"
 *    ~~~~~~~~   ~    ~~~~
 *    노드 값들  pos  기대하는 결과 (true / false)
 *
 * pos 는 꼬리가 이어지는 노드의 위치예요. 0부터 세요. 순환이 없으면 -1 이에요.
 * 빈 리스트는 [] 라고 쓰면 돼요. 빈 리스트의 pos 는 -1 이어야 해요.
 *
 * 검산기는 돌려준 값 말고 하나를 더 봐요. 함수가 끝난 뒤 노드들의 next 가 처음 모양 그대로인지요.
 * val 이 바뀌어 있으면 알려만 주고 실패로 치지는 않아요 (파이썬 버전 검산기와 같은 기준이에요).
 *
 * 예제 세 개는 문제에 나온 그대로예요. 나머지는 직접 만들어 주세요 — 반례 3개 룰이에요 (ง'̀-'́)ง
 * 기대 결과도 손으로 먼저 정해서 적어 두고 돌려 주세요.
 * 주석을 풀어서 쓰시면 되고, 줄을 더 만드셔도 돼요.
 */
typedef struct {
    const char *name;
    const char *script;
} Case;

static const Case CASES[] = {
    { "예제1", "3 2 0 -4 @ 1 -> true" },
    { "예제2", "1 2 @ 0 -> true" },
    { "예제3", "1 @ -1 -> false" },
    { "케이스4", "1 2 3 1 2 4 1 2 1 2 @ -1 -> false" },
    { "케이스5", "1 2 3 1 2 3 @ -1 -> false" },
    { "케이스6", "1 2 10000 -10000 -1 @ 1 -> true" },
};


/* "3 2 0 -4" 나 "[]" 같은 조각을 숫자 배열로 바꿔요. 개수를 돌려주고, 못 읽으면 -1 이에요. */
static int parse_values(char *piece, int *out)
{
    int n = 0;
    for (char *tok = strtok(piece, " \t"); tok != NULL; tok = strtok(NULL, " \t")) {
        if (strcmp(tok, "[]") == 0)
            continue;
        char *end;
        long v = strtol(tok, &end, 10);
        if (*end != '\0' || n >= MAXN)
            return -1;
        out[n++] = (int)v;
    }
    return n;
}

/* 앞뒤 공백을 떼요. */
static char *trim(char *s)
{
    while (*s == ' ' || *s == '\t')
        s++;
    char *e = s + strlen(s);
    while (e > s && (e[-1] == ' ' || e[-1] == '\t'))
        *--e = '\0';
    return s;
}

static int run_case(const Case *c)
{
    char buf[512];
    strncpy(buf, c->script, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';

    char *at = strchr(buf, '@');
    char *arrow = strstr(buf, "->");
    if (at == NULL || arrow == NULL || arrow < at) {
        printf("FAIL   %s: \"%s\" 을 못 읽었어요\n", c->name, c->script);
        printf("         \"3 2 0 -4 @ 1 -> true\" 모양이어야 해요\n");
        return 0;
    }
    *at = '\0';
    *arrow = '\0';

    int values[MAXN];
    int n = parse_values(buf, values);
    char *pos_text = trim(at + 1);
    char *answer = trim(arrow + 2);
    char *end;
    long pos = strtol(pos_text, &end, 10);
    bool expected;

    if (n < 0 || *pos_text == '\0' || *end != '\0') {
        printf("FAIL   %s: \"%s\" 을 못 읽었어요\n", c->name, c->script);
        return 0;
    }
    if (strcmp(answer, "true") == 0)
        expected = true;
    else if (strcmp(answer, "false") == 0)
        expected = false;
    else {
        printf("FAIL   %s: 기대 결과는 true 나 false 여야 해요 (\"%s\")\n", c->name, answer);
        return 0;
    }
    if (!(pos == -1 || (0 <= pos && pos < n))) {
        printf("FAIL   %s: pos %ld 가 리스트 밖이에요. -1 이거나 0 ~ %d 이어야 해요\n", c->name, pos, n - 1);
        return 0;
    }

    /* 노드를 배열로 들고 있으면서 만들어요. 순환이 있어도 이 배열로 해제할 수 있게요. */
    struct ListNode *nodes[MAXN];
    for (int i = 0; i < n; i++) {
        nodes[i] = malloc(sizeof(struct ListNode));
        nodes[i]->val = values[i];
        nodes[i]->next = NULL;
    }
    for (int i = 0; i + 1 < n; i++)
        nodes[i]->next = nodes[i + 1];
    if (n > 0 && pos >= 0)
        nodes[n - 1]->next = nodes[pos];

    struct ListNode *links_before[MAXN];
    for (int i = 0; i < n; i++)
        links_before[i] = nodes[i]->next;

    bool got = hasCycle(n > 0 ? nodes[0] : NULL);

    int changed_next = 0, changed_val = 0;
    for (int i = 0; i < n; i++) {
        if (nodes[i]->next != links_before[i])
            changed_next++;
        if (nodes[i]->val != values[i])
            changed_val++;
    }

    int ok = 0;
    if (got != expected) {
        printf("FAIL   %s: ", c->name);
        ll_print_array(values, n);
        printf(" @ %ld\n         기대 %s\n         실제 %s\n", pos,
               expected ? "true" : "false", got ? "true" : "false");
    } else if (changed_next) {
        printf("FAIL   %s: 답은 맞는데, 노드 %d개의 next 가 바뀌어 있어요. 리스트를 원래대로 둬야 해요\n",
               c->name, changed_next);
    } else {
        printf("PASS   %s: ", c->name);
        ll_print_array(values, n);
        printf(" @ %ld -> %s\n", pos, got ? "true" : "false");
        ok = 1;
    }
    if (changed_val)
        printf("         (알림) 노드 %d개의 val 이 바뀌어 있어요. 실패로 치지는 않아요\n", changed_val);

    /* 리스트를 따라가지 않고 배열로 해제해요. 순환이 있어도 한 번씩만 free 돼요. */
    for (int i = 0; i < n; i++)
        free(nodes[i]);
    return ok;
}

int main(void)
{
    int total = (int)(sizeof(CASES) / sizeof(CASES[0]));
    int passed = 0;

    for (int i = 0; i < total; i++) {
        passed += run_case(&CASES[i]);
        printf("\n");
        fflush(stdout);
    }

    printf("%d/%d 통과\n", passed, total);
    return 0;
}
