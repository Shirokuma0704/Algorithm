"""LeetCode 225. Implement Stack using Queues  —  파이썬 버전

큐 두 개만 써서 스택(LIFO)을 만드는 문제예요. 0232 를 거꾸로 뒤집은 모양이에요 (ﾉ◕ヮ◕)ﾉ

만들 연산 네 개:
    push(x)   스택 맨 위에 x 를 넣어요
    pop()     맨 위에서 빼고 그 값을 돌려줘요
    top()     맨 위 값을 보기만 해요
    empty()   비었으면 True

큐로 쓰는 collections.deque 에 허락된 동작은 네 개뿐이에요.
    append(x)    뒤에 넣기
    popleft()    앞에서 빼기
    [0]          앞 보기
    len() / not  비었는지 보기
-> pop(), [-1] 처럼 뒤쪽에서 꺼내거나 들여다보는 건 스택 연산이라 규칙 위반이에요.
   출력이 맞아도 테스트는 이걸 못 잡아요. 이 줄만은 눈으로 지켜야 해요 ( ˘•ω•˘ )

제약:
    1 <= x <= 9
    push, pop, top, empty 를 합쳐 최대 100 번 호출
    pop 과 top 은 비어 있지 않은 스택에서만 불려요

follow-up: 큐를 하나만 써서도 만들 수 있을까요?

처음 푸는 문제라 백지에서 시작해요. 내일 C 로 다시 짤 때는 이 파일 보지 않기 (LIST.md 규칙).

실행:
    C:/Users/Beak/Desktop/Jungle/Algorithm/.venv/Scripts/python.exe 0225_implement_stack_using_queues.py
"""

from collections import deque
from gettext import find


class MyStack:

    def __init__(self):
        self.last_val = None
        self.queue = []

    def push(self, x: int) -> None:
        if self.last_val is None:
            self.last_val = x
        else:
            self.queue.append(self.last_val)
            self.last_val = x
        return

    def find_last_val(self):

        temp = []

        if len(self.queue) != 0:
            while len(self.queue) != 0:
                pop_val = self.queue.pop(0)

                if len(self.queue) == 0:
                    self.last_val = pop_val
                else: temp.append(pop_val)

            self.queue = temp
        else: self.last_val = None
        return

    def pop(self) -> int:

        last_val = self.last_val
        self.find_last_val()
        return last_val

    def top(self) -> int:
        return self.last_val

    def empty(self) -> bool:
        if self.last_val is None: return True
        return False


# ---------------------------------------------------------------------------
# 아래는 테스트용 도구예요. 풀이랑은 상관없으니 그냥 두고 위만 채우면 돼요.
# ---------------------------------------------------------------------------

# 한 케이스 = 연산을 차례로 부르는 시나리오 한 줄이에요.
# 한 걸음은 (연산, 인자, 기대값) 이에요. push 는 돌려주는 게 없으니 기대값 자리에 None.
# 기대값 자리에 예외 클래스(IndexError 같은)를 적으면 "그 예외가 나야 통과"라는 뜻이에요.
#
# 예제 하나만 채워뒀어요. 나머지 케이스는 직접 만들어 주세요 — 반례 3개 룰이에요 ٩(˘◡˘)۶
CASES = [
    ("예제", [
        ("push", 1, None),
        ("push", 2, None),
        ("top", None, 2),
        ("pop", None, 2),
        ("empty", None, False),
    ]),
    ("예제", [
        ("push", 1, None),
        ("pop", None, 1),
        ("push", 2, None),
        ("pop", None, 2),
        ("empty", None, True),
    ]),
    ("케이스3 ", [
        ("push", 1, None),
        ("push", 2, None),
        ("push", 3, None),

        ("top", None, 3),
        ("pop", None, 3),
        ("top", None, 2),
        ("pop", None, 2),

        ("empty", None, False),

    ]),
    # ("케이스4 ", [
    # ]),
]


def run_case(name: str, steps: list) -> bool:
    s = MyStack()

    for i, (op, arg, expected) in enumerate(steps, 1):
        if op == "push":
            s.push(arg)
            print(f"       push({arg})")
            continue

        if isinstance(expected, type) and issubclass(expected, Exception):
            try:
                got = getattr(s, op)()
            except expected:
                print(f"       {op}() -> {expected.__name__} (기대대로)")
                continue
            print(f"FAIL   {name}: {i}번째 {op}()")
            print(f"         기대 {expected.__name__} 발생")
            print(f"         실제 {got!r} 를 돌려줌")
            return False

        got = getattr(s, op)()

        # top 은 보기만 해야 해요. 한 번 더 불러서 값과 empty() 가 그대로인지 봐요.
        if op == "top":
            empty_before = s.empty()
            again = s.top()
            if again != got or s.empty() != empty_before:
                print(f"FAIL   {name}: {i}번째 top 이 스택을 바꿨어요 "
                      f"(첫 top {got!r}, 다시 top {again!r})")
                return False

        if got != expected or type(got) is not type(expected):
            print(f"FAIL   {name}: {i}번째 {op}()")
            print(f"         기대 {expected!r}")
            print(f"         실제 {got!r}")
            return False
        print(f"       {op}() -> {got!r}")

    print(f"PASS   {name}")
    return True


def main() -> None:
    passed = 0
    for name, steps in CASES:
        try:
            ok = run_case(name, steps)
        except Exception as e:
            print(f"ERROR  {name}: {type(e).__name__}: {e}")
            ok = False
        passed += ok
        print()

    print(f"{passed}/{len(CASES)} 통과")


if __name__ == "__main__":
    main()
