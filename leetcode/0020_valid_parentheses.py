"""LeetCode 20. Valid Parentheses

'(', ')', '{', '}', '[', ']' 로만 이루어진 문자열 s 가 올바른 괄호 문자열인지 판정한다.

올바르다는 건 세 가지가 동시에 성립한다는 뜻이다.
    1. 열린 괄호는 같은 종류의 괄호로 닫힌다.
    2. 닫히는 순서가 열린 순서의 역순이다.
    3. 모든 닫는 괄호에는 짝이 되는 열린 괄호가 앞에 있다.

제약:
    1 <= len(s) <= 10^4
    s 는 '()[]{}' 여섯 글자로만 이루어진다.
    -> 길이가 1 이상이라 빈 문자열은 LeetCode 입력에 안 나온다.
       그래도 아래 CASES 에 넣어뒀다. 채점기가 안 물어봐도 내 코드는 답해야 하니까.

실행:
    C:/Users/Beak/Desktop/Jungle/Algorithm/.venv/Scripts/python.exe 0020_valid_parentheses.py
"""

class Solution:
    def isValid(self, s: str) -> bool:
        if len(s) == 0:
            return False
        parentheses = list(s)
        stack = []
        for string in parentheses:
            match string:
                case "{": stack.append('{')
                case "(": stack.append('(')
                case "[": stack.append('[')
                case "}":
                    if len(stack) == 0: return False
                    pop = stack.pop()
                    if pop != '{': return False
                case "]":
                    if len(stack) == 0: return False
                    pop = stack.pop()
                    if pop != '[': return False
                case ")":
                    if len(stack) == 0: return False
                    pop = stack.pop()
                    if pop != '(': return False
                case _: return False
        if len(stack) != 0: return False
        return True





# ---------------------------------------------------------------------------
# 아래는 테스트용 도구. 문제 풀이와는 상관없으니 그냥 두고 위만 채우면 된다.
# ---------------------------------------------------------------------------

# 앞의 네 개는 문제에 나온 예제다.
# 나머지는 비워뒀다 — 어떤 입력에서 깨질지 직접 정해서 채울 것.
# 기대값을 손으로 먼저 계산해 적어둔 다음에 돌린다. 통과는 증거가 아니다.
#
# 채울 때 생각해볼 갈래 세 개 (문장은 힌트고, 실제 문자열은 직접 고른다):
#   - 스택이 비어 있는데 닫는 괄호가 먼저 오면 어떻게 되는가
#   - 문자열을 다 읽었는데 스택에 뭔가 남아 있으면 그건 무슨 상황인가
#   - 짝의 개수는 맞는데 종류가 엇갈리면 어떻게 되는가
CASES = [
    # (입력, 기대 출력)
    ("()", True),
    ("()[]{}", True),
    ("(]", False),
    ("([])", True),
    ("([)]", False),
    ("", False),
    ("(((((", False),
    ("(]", False)
]


def main() -> None:
    passed = 0
    for i, (s, expected) in enumerate(CASES, 1):
        try:
            got = Solution().isValid(s)
        except Exception as e:
            print(f"[{i}] ERROR  입력 {s!r} -> {type(e).__name__}: {e}")
            continue

        if got is expected:
            print(f"[{i}] PASS   입력 {s!r} -> {got}")
            passed += 1
        else:
            print(f"[{i}] FAIL   입력 {s!r}")
            print(f"         기대 {expected!r}")
            print(f"         실제 {got!r}")

    print(f"\n{passed}/{len(CASES)} 통과")


if __name__ == "__main__":
    main()
