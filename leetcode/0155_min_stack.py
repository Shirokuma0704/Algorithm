"""LeetCode 155. Min Stack  —  파이썬 버전

보통 스택에 "지금 들어 있는 것 중 가장 작은 값"을 바로 알려주는 기능 하나를 얹는 문제예요 (๑˃ᴗ˂)ﻭ

만들 연산 네 개:
    push(val)   맨 위에 val 을 넣어요
    pop()       맨 위를 빼요. 돌려주는 값은 없어요
    top()       맨 위 값을 돌려줘요
    getMin()    지금 스택 안에서 가장 작은 값을 돌려줘요

제약:
    -2^31 <= val <= 2^31 - 1      음수도 들어와요
    pop, top, getMin 은 비어 있지 않은 스택에서만 불려요
    전부 합쳐 최대 3 * 10^4 번 호출

LIST.md 의 연결고리: 값 옆에 정보를 하나 더 얹어서 같이 관리하는 구조예요.
malloc 이 블록 앞뒤에 헤더/푸터를 붙이는 것과 같은 모양이에요.

처음 푸는 문제라 백지에서 시작해요.

실행:
    C:/Users/Beak/Desktop/Jungle/Algorithm/.venv/Scripts/python.exe 0155_min_stack.py
"""
from asyncio.windows_events import NULL


class MinStack:
    # 문제 조건: 네 연산 전부 각각 O(1) 시간이어야 해요.
    # getMin 을 부를 때마다 스택 전체를 훑으면 답은 맞아도 조건 위반이에요.
    # 아래 검산기는 시간을 안 재서 이걸 못 잡아요. 이 줄만은 눈으로 지켜야 해요 ( ˘•ω•˘ )

    def __init__(self):
        self.stack = []
        self.min_val = []

    def push(self, val: int) -> None:
        self.stack.append(val)
        if (len(self.min_val) == 0) or (self.min_val[-1] >= val):
            self.min_val.append(val)
        return

    def pop(self) -> None:
        pop_val = self.stack.pop(-1)
        if pop_val == self.min_val[-1]:
            self.min_val.pop(-1)

    def top(self) -> int:
        return self.stack[-1]

    def getMin(self) -> int:
        return self.min_val[-1]


# ---------------------------------------------------------------------------
# 아래는 검산용이에요. 풀이랑은 상관없으니 그냥 두고 위만 채우면 돼요.
# ---------------------------------------------------------------------------

# 한 케이스 = 연산을 차례로 부르는 시나리오 한 줄이에요. 쉼표로 걸음을 나눠요.
#
#   push -2       push(-2)            숫자는 넣을 값이에요
#   pop           pop()               돌려받는 게 없어서 숫자 없이 써요
#   top 0         top()    이 0 을 돌려줘야 통과
#   getMin -3     getMin() 이 -3 을 돌려줘야 통과
#
# 예제 하나만 채워뒀어요. 나머지는 직접 만들어 주세요 — 반례 3개 룰이에요 (ง •̀ω•́)ง
# 주석을 풀어서 쓰시면 되고, 줄을 더 만드셔도 돼요.
CASES = [
    ("예제", "push -2, push 0, push -3, getMin -3, pop, top 0, getMin -2"),
    ("케이스2", "push -2, push -2, pop, getMin -2"),
    ("케이스3", "push 5, push 1, push 1, push -5, pop, pop, getMin 1"),
    # ("케이스4", ""),
]


def parse_step(piece: str):
    """조각 하나("push -2", "pop", "getMin -3")를 (연산, 숫자) 로 나눠요. 못 읽으면 None."""
    words = piece.split()
    if words == ["pop"]:
        return "pop", None
    if len(words) != 2 or words[0] not in ("push", "top", "getMin"):
        return None
    try:
        return words[0], int(words[1])
    except ValueError:
        return None


def run_case(name: str, script: str) -> bool:
    s = MinStack()

    for i, piece in enumerate(script.split(","), 1):
        step = parse_step(piece)
        if step is None:
            print(f"FAIL   {name}: {i}번째 조각 {piece.strip()!r} 을 못 읽었어요")
            print("         push -2 / pop / top 0 / getMin -3 중 하나 모양이어야 해요")
            return False
        op, num = step

        if op == "push":
            s.push(num)
            print(f"       push({num})")
            continue
        if op == "pop":
            s.pop()
            print("       pop()")
            continue

        got = getattr(s, op)()
        if got != num or type(got) is not int:
            print(f"FAIL   {name}: {i}번째 {op}()")
            print(f"         기대 {num!r}")
            print(f"         실제 {got!r}")
            return False
        print(f"       {op}() -> {got!r}")

    print(f"PASS   {name}")
    return True


def main() -> None:
    passed = 0
    for name, script in CASES:
        try:
            ok = run_case(name, script)
        except Exception as e:
            print(f"ERROR  {name}: {type(e).__name__}: {e}")
            ok = False
        passed += ok
        print()

    print(f"{passed}/{len(CASES)} 통과")


if __name__ == "__main__":
    main()
