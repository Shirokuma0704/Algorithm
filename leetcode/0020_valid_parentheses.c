/* LeetCode 20. Valid Parentheses  —  C 버전
 *
 * 괄호로만 이루어진 문자열 s 를 받아서, 짝이 올바르게 맞는지 돌려줘요.
 * 올바르다는 건 두 가지예요. 여는 괄호는 같은 종류로 닫혀야 하고,
 * 닫히는 순서가 열린 순서의 역순이어야 해요.
 *
 * 제약:
 *     1 <= s.length <= 10^4
 *     s 는 '(' ')' '[' ']' '{' '}' 여섯 글자로만 이루어져요
 *
 * 길이가 최소 1 이라서 빈 문자열은 안 들어와요. 다만 그게 "짧은 입력은
 * 신경 안 써도 된다"는 뜻은 아니에요 — 길이 1 짜리는 들어옵니다.
 *
 * 컴파일하고 돌리는 법 — 둘 중 편한 쪽으로요.
 *
 *   윈도우 (CLion 번들 MinGW, PATH 에 없어서 절대경로로 불러요)
 *     "C:/Program Files/JetBrains/CLion 2026.2.2/bin/mingw/bin/gcc.exe" \
 *         0020_valid_parentheses.c -o 0020.exe && ./0020.exe
 *
 *   WSL (이쪽은 valgrind 랑 sanitizer 가 있어서 메모리까지 봐줘요)
 *     wsl.exe -d Ubuntu-22.04 -e bash -lc \
 *         'gcc -g -fsanitize=address 0020_valid_parentheses.c -o 0020 && ./0020'
 *
 * 이 문제는 common/ 에 헤더를 안 뒀어요. 0206 과 0100 은 LeetCode 가 노드
 * 구조체를 정해주지만 여기는 안 정해주거든요. 무엇을 어떻게 들고 갈지가
 * 이 문제의 본체라서, 그 자리를 비워두는 게 맞아요 ( ˘ᵕ˘ )
 *
 * 처음 한 번은 컴파일 경고가 뜨는 게 정상이에요. 아래 함수 몸통이 비어 있어서
 * "control reaches end of non-void function" 이 나옵니다. 그 경고가 사라지는
 * 게 첫 번째 목표예요.
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>


/* ------------------------------------------------------------------ */
/* 여기부터 아래 함수 하나가 LeetCode 에 붙여넣을 전부예요              */
/* ------------------------------------------------------------------ */

/* 짝이 올바르게 맞으면 true, 아니면 false 를 돌려주세요.
 *
 * 받은 문자열은 읽기만 하고 바꾸지 마세요. s 는 LeetCode 가 준 메모리라
 * 여기에 덮어쓰면 채점기에서는 통과해도 남의 버퍼를 건드린 게 돼요.
 * 이번 주 챌린지에서 보고 계신 그 축이에요.
 *
 * malloc 을 쓰셨다면 return 하기 전에 전부 free 해주세요. 중간에 일찍
 * 돌아가는 return 이 생기면 그 길에서도 free 가 지나가야 해요.
 */

char want(char word)
{
    switch(word){
    case '}': return '{';
    case ']': return '[';
    case ')': return '(';
    default: return '\0';
    }
}

bool isValid(char *s)
{
    if (strlen(s) == 0) return false;
    char stack[strlen(s)+1];
    int last_index = 0;

    while (*s != '\0')
    {
        char current = *s;
        int def = 0;
        if ( current == '{' || current =='(' || current =='[') def = 1;
        else if ( current == '}' ||current == ']' ||current == ')') def = 2;
        switch (def)
        {
        case 1:
            last_index++;
            stack[last_index] = current;
            break;
        case 2:
            if (stack[last_index] == want(current))
            {
                stack[last_index] = 0;
                last_index --;
                break;
            }
            return false;
        }
        s++;
    }

    if (last_index != 0) return false;
    return true;
}


/* ------------------------------------------------------------------ */
/* 아래는 검산용이에요. 문제 풀이랑은 상관없으니 위만 보시면 돼요       */
/* ------------------------------------------------------------------ */

typedef struct {
    const char *s;
    int expect;    /* 올바르면 1, 아니면 0 */
} Case;

/* 앞의 세 개는 문제에 나온 예제예요.
 *
 * 그 뒤는 비워뒀어요. 이번 주 과제가 테스트를 안 주는 것과 같은 이유예요 —
 * 경계를 찾아내는 게 연습의 본체라서요. 위의 제약 두 줄을 다시 읽으면서,
 * 이 세 개가 건드리지 않는 입력이 뭔지 찾아 채워보세요.
 *
 * 채울 때 하나만 봐주세요. 기대값이 0 인 케이스만 늘리면 무조건 false 를
 * 돌려주는 풀이가 전부 통과하고, 1 인 케이스만 늘리면 반대가 통과해요.
 * README 의 "통과는 증거가 아니다" 가 이 자리예요 ( •̀ ω •́ )✧
 *
 * 힌트를 하나만 드리면, 예제 세 개는 전부 **여는 괄호로 시작해서 개수가
 * 딱 맞아떨어지는** 문자열이에요. 그 조건을 하나씩 깨보시면 돼요.
 */
static Case CASES[] = {
    /* 입력            기대 */
    { "()",             1 },
    { "()[]{}",         1 },
    { "(]",             0 },

    /* 주석을 풀고 채워주세요. 줄이 모자라면 더 늘리셔도 돼요. */
    { "([)]",            0 },
    { "",            0 },
     { "{((",            0 },
};

int main(void)
{
    int total = (int)(sizeof(CASES) / sizeof(CASES[0]));
    int passed = 0;

    for (int i = 0; i < total; i++) {
        Case *c = &CASES[i];

        /* LeetCode 는 배열을 주지 상수 문자열을 주지 않아요. 그래서 여기서
         * 한 벌 떠서 넘겨요. 풀이가 s 를 건드리면 그게 아래에서 드러나요.
         */
        char buf[64];
        snprintf(buf, sizeof(buf), "%s", c->s);

        /* TODO: 호출 뒤에도 입력 문자열이 그대로인지 확인하는 검사를 채워보세요.
         *
         * 지금 이 검산기는 돌려받은 true/false 하나만 봐요. 그래서 비교하는
         * 김에 buf 의 글자를 덮어쓰거나 잘라버린 풀이도 그대로 통과해버립니다.
         * 위에 적어둔 "읽기만 한다" 조건이 검산에서 빠져 있는 거예요.
         *
         * 호출 전에 buf 를 어딘가 한 벌 더 떠두고, 호출 뒤에 그 둘이 글자
         * 그대로 같은지 보면 됩니다 (strcmp 가 0 이면 같아요). 떠둔 걸 어디에
         * 담아둘지와, 달라졌을 때 어떻게 알릴지가 비어 있어요.
         */

        bool got = isValid(buf);
        int ok = (got == (c->expect != 0));

        printf("[%d] ", i + 1);

        if (ok) {
            printf("PASS   \"%s\" -> %s\n", c->s, got ? "true" : "false");
            passed++;
        } else {
            printf("FAIL   \"%s\"\n", c->s);
            printf("         기대 %s\n", c->expect ? "true" : "false");
            printf("         실제 %s\n", got ? "true" : "false");
        }
    }

    printf("\n%d/%d 통과\n", passed, total);
    return 0;
}
