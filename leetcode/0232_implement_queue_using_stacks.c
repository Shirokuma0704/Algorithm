/* LeetCode 232. Implement Queue using Stacks  —  C 버전
 *
 * 스택 두 개만 써서 큐를 만드는 문제예요. 스택이 쓸 수 있는 연산은
 * push(맨 위에 넣기), pop(맨 위에서 빼기), peek(맨 위 보기), empty(비었나) 네 개뿐이고,
 * 그걸로 FIFO 를 흉내 내야 해요.
 *
 * 만들 연산 다섯 개:
 *     push(x)   큐 뒤에 x 를 넣는다
 *     pop()     큐 앞에서 빼서 그 값을 돌려준다
 *     peek()    큐 앞의 값을 보기만 한다
 *     empty()   비었으면 true
 *     free()    다 쓰고 정리한다
 *
 * 제약:
 *     1 <= x <= 9
 *     push, pop, peek, empty 를 합쳐 최대 100 번 호출
 *     pop 과 peek 은 비어 있지 않은 큐에서만 불린다
 *
 * 그리고 문제가 따로 묻는 게 하나 있어요 (follow-up):
 *     각 연산을 amortized O(1) 로 만들 수 있는가?
 *
 * "amortized(분할 상환)" 는 **한 번은 비싸도 여러 번에 걸쳐 나눠보면 싸다**는 뜻이에요.
 * 어떤 호출 하나가 O(n) 이어도, n 번 호출하는 동안 총비용이 O(n) 이면 평균은 O(1) 이죠.
 * 이 문제를 진짜로 푸는 건 이 한 줄이고, 나머지는 그걸 코드로 옮기는 일이에요.
 *
 * 컴파일하고 돌리는 법 — 둘 중 편한 쪽으로요.
 *
 *   윈도우 (CLion 번들 MinGW, PATH 에 없어서 절대경로로 불러요)
 *     "C:/Program Files/JetBrains/CLion 2026.2.2/bin/mingw/bin/gcc.exe" \
 *         0232_implement_queue_using_stacks.c -o 0232.exe && ./0232.exe
 *
 *   WSL (이쪽은 valgrind 랑 sanitizer 가 있어서 메모리까지 봐줘요)
 *     wsl.exe -d Ubuntu-22.04 -e bash -lc \
 *         'gcc -g 0232_implement_queue_using_stacks.c -o 0232 && valgrind -q ./0232'
 *
 * 0020 과 마찬가지로 common/ 에 헤더를 안 뒀어요. LeetCode 가 구조체를 안 정해주거든요.
 * **무엇을 어떻게 들고 갈지가 이 문제의 본체**라서 그 자리를 비워두는 게 맞아요 ( ˘ᵕ˘ )
 *
 * 그리고 이번 문제는 0020 과 결정적으로 달라요 — **malloc 이 나옵니다.**
 * 만든 것을 누가 언제 놓아주는지가 같이 걸려요. 이번 주 챌린지의 그 축이에요.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ------------------------------------------------------------------ */
/* 여기부터 아래가 LeetCode 에 붙여넣을 전부예요                        */
/* ------------------------------------------------------------------ */

/* 큐가 무엇을 들고 있어야 하는지는 상철님이 정하세요.
 *
 * 스택 두 개를 어떻게 표현할지(배열? 포인터? 크기는 고정? 동적?), 각 스택의
 * 꼭대기를 어떻게 기억할지가 전부 이 안에 들어갑니다.
 *
 * 제약의 "최대 100 번 호출" 을 다시 읽어보세요. 크기를 어떻게 잡을지가 거기서 정해져요.
 */
typedef struct
{
    int val[100];
    int idx;
} Stack;

typedef struct {
    Stack input;
    Stack output;

} MyQueue;


/* 빈 큐를 하나 만들어서 그 포인터를 돌려주세요.
 *
 * malloc 이 실패하면 NULL 이 옵니다. 이 파일에서는 실제로 실패할 일이 없지만,
 * 실패를 어떻게 다룰지는 정해두는 게 좋아요 — 이번 주 11번에서 본 그 얘기예요.
 */


MyQueue *myQueueCreate(void)
{
    MyQueue *head = malloc(sizeof(MyQueue));
    head->output.idx =0;
    head->input.idx = 0;
    memset(head->input.val, 0, (sizeof(int)) * 100);
    memset(head->output.val, 0, (sizeof(int)) * 100);
    return head;
}


/* 큐의 뒤에 x 를 넣으세요. */
void myQueuePush(MyQueue *obj, int x)
{
    obj->input.val[obj->input.idx] = x;
    obj->input.idx++;
}


/* 큐의 앞에서 하나 빼고, 그 값을 돌려주세요.
 *
 * 문제가 "비어 있지 않을 때만 부른다" 고 보장해줬어요. 그래도 빈 큐에서 불렸을 때
 * 무엇을 하고 싶은지는 생각해두세요 — 0020 에서 본 그 자리입니다.
 */
int myQueuePop(MyQueue *obj)
{

    int idx = obj->output.idx;

    if (obj->output.val[obj->output.idx] == 0)
    {
        if ( obj->input.val[idx] == 0) return 0;

        obj->output.idx = 0;
        while (obj->input.val[idx] != 0)
        {
            obj->output.val[obj->output.idx] = obj->input.val[idx];
            obj->input.val[idx] = 0;
            idx++;
            obj->output.idx++;
        }
        obj->input.idx = 0;
    }
    int pop_output = obj->output.val[obj->output.idx];
    obj->output.idx++;

    return pop_output;
}


/* 큐의 앞을 보기만 하세요. 빼지는 말고요.
 *
 * "보기만 한다" 가 내부 상태를 하나도 안 건드린다는 뜻은 아니에요.
 * 밖에서 본 큐의 내용이 같으면 됩니다. 그 차이가 이 문제의 핵심이에요.
 */
int myQueuePeek(MyQueue *obj)
{
    int idx = obj->output.idx;

    if (obj->output.val[obj->output.idx] == 0)
    {
        if ( obj->input.val[idx] == 0) return 0;
        obj->output.idx = 0;
        while (obj->input.val[idx] != 0)
        {
            obj->output.val[obj->output.idx] = obj->input.val[idx];
            obj->input.val[idx] = 0;
            idx++;
            obj->output.idx++;
        }
        obj->input.idx = 0;
    }
    return obj->output.val[obj->output.idx];
}


/* 비어 있으면 true. */
bool myQueueEmpty(MyQueue *obj)
{
    if (obj->output.val[obj->output.idx] == 0 && obj->input.val[obj->input.idx] == 0) return true;
    return false;
}



/* 큐가 잡고 있던 것을 전부 놓아주세요.
 *
 * obj 자신뿐 아니라, 구조체 안에서 따로 malloc 한 게 있다면 그것도요.
 * 안쪽을 먼저 놓아주고 바깥을 놓아주는 순서를 지켜야 해요 — 바깥을 먼저 free 하면
 * 안쪽 포인터를 읽을 방법이 사라집니다.
 */
void myQueueFree(MyQueue *obj)
{
    free(obj);
}


/* ------------------------------------------------------------------ */
/* 아래는 검산용이에요. 문제 풀이랑은 상관없으니 위만 보시면 돼요       */
/* ------------------------------------------------------------------ */

/* 연산 하나를 이렇게 적어요.
 *
 *   U x   push(x)       기대값 없음
 *   O     pop()         돌려받을 값을 expect 에
 *   K     peek()        돌려받을 값을 expect 에
 *   E     empty()       기대값 1(참) 또는 0(거짓)
 */
typedef struct {
    char op;
    int arg;
    int expect;
} Step;

#define U(x) { 'U', (x), 0 }
#define O(e) { 'O', 0, (e) }
#define K(e) { 'K', 0, (e) }
#define E(e) { 'E', 0, (e) }
#define END  { 0, 0, 0 }

/* 첫 줄은 문제에 나온 예제예요.
 *
 * 그 뒤는 비워뒀어요. 경계를 찾아내는 게 연습의 본체라서요. 위의 제약과 연산 목록을
 * 다시 읽으면서, 이 시나리오가 건드리지 않는 순서가 뭔지 찾아 채워보세요.
 *
 * 힌트를 하나만 드리면, 아래 예제는 **넣기를 다 끝낸 다음에 빼기 시작**해요.
 * 넣기와 빼기를 번갈아 하면 어떻게 되는지가 이 문제에서 제일 잘 깨지는 자리예요
 * ( •̀ ω •́ )✧
 */
static Step CASE1[] = { U(1), U(2), K(1), O(1), E(0), END };
static Step CASE2[] = { K(0), O(0), E(1), END };
static Step CASE3[] = { U(1), U(2), O(1), O(2), E(1), END };


/* 주석을 풀고 채워주세요. 줄을 더 만드셔도 돼요. */
/* static Step CASE2[] = { END }; */
/* static Step CASE3[] = { END }; */

static Step *CASES[] = { CASE1,  CASE2, CASE3  };
static const char *NAMES[] = { "예제", "케이스2", "케이스3"  };


static int run_case(const char *name, Step *steps)
{
    MyQueue *q = myQueueCreate();
    int ok = 1;

    if (q == NULL) {
        printf("FAIL   %s: myQueueCreate 가 NULL 을 돌려줬어요\n", name);
        return 0;
    }

    for (int i = 0; steps[i].op != 0; i++) {
        Step *s = &steps[i];
        int got = 0;

        /* TODO: peek 이 큐를 바꾸지 않는지 확인하는 검사를 채워보세요.
         *
         * 지금 이 검산기는 peek 이 돌려준 값 하나만 봐요. 그래서 peek 을 부를 때마다
         * 원소를 하나씩 잃어버리는 구현도, 순서가 뒤집히는 구현도 그대로 통과합니다.
         *
         * 방법은 간단해요 — peek 을 부른 뒤에 한 번 더 부르면 같은 값이 나와야 하고,
         * empty() 결과도 그대로여야 해요. 무엇을 떠두고 무엇과 비교할지가 비어 있어요.
         */

        switch (s->op) {
        case 'U':
            myQueuePush(q, s->arg);
            printf("       push(%d)\n", s->arg);
            continue;
        case 'O': got = myQueuePop(q);        break;
        case 'K': got = myQueuePeek(q);       break;
        case 'E': got = myQueueEmpty(q) ? 1 : 0; break;
        }

        if (got == s->expect) {
            printf("       %c() -> %d\n", s->op == 'O' ? 'p' : (s->op == 'K' ? 'k' : 'e'), got);
        } else {
            printf("       %c() -> %d   기대 %d   <-- 여기\n",
                   s->op == 'O' ? 'p' : (s->op == 'K' ? 'k' : 'e'), got, s->expect);
            ok = 0;
        }
    }

    /* 여기서 놓아주지 않으면 valgrind 가 누수로 잡아요.
     * 0020 에서 쓴 그 도구입니다 — 이번엔 "안 놓아준 것" 을 봅니다.
     */
    myQueueFree(q);

    printf("[%s] %s\n\n", ok ? "PASS" : "FAIL", name);
    return ok;
}

int main(void)
{
    int total = (int)(sizeof(CASES) / sizeof(CASES[0]));
    int passed = 0;

    for (int i = 0; i < total; i++)
        passed += run_case(NAMES[i], CASES[i]);

    printf("%d/%d 통과\n", passed, total);
    return 0;
}
