"""LeetCode 232. Implement Queue using Stacks  —  파이썬 버전

스택 두 개만 써서 큐(FIFO)를 만드는 문제다.

만들 연산 네 개:
    push(x)   큐 뒤에 x 를 넣는다
    pop()     큐 앞에서 빼서 그 값을 돌려준다
    peek()    큐 앞의 값을 보기만 한다
    empty()   비었으면 True

스택으로 쓰는 list 에 허락된 동작은 네 개뿐이다.
    append(x)    맨 위에 넣기
    pop()        맨 위에서 빼기   (인자 없이. pop(0) 은 스택 연산이 아니다)
    [-1]         맨 위 보기
    len() / not  비었는지 보기
-> 인덱스로 바닥을 들여다보거나 뒤집어 읽는 건 전부 규칙 위반이다.

제약:
    1 <= x <= 9
    push, pop, peek, empty 를 합쳐 최대 100 번 호출
    pop 과 peek 은 비어 있지 않은 큐에서만 불린다

follow-up: 각 연산을 amortized O(1) 로 만들 수 있는가?

C 버전과 다른 점 하나: free() 가 없다. 파이썬은 아무도 안 가리키는 객체를 알아서 치운다.
어제 C 에서 신경 썼던 "누가 놓아주나" 축이 통째로 사라지는 셈이다.

어제 C 파일은 보지 않고 백지에서 짠다 (LIST.md 규칙).

실행:
    C:/Users/Beak/Desktop/Jungle/Algorithm/.venv/Scripts/python.exe 0232_implement_queue_using_stacks.py
"""

class MyQueue:

    def __init__(self):
        self.input = []
        self.output = []

    def sort(self) -> None:
        while len(self.input) != 0:
            self.output.append(self.input.pop())


    def push(self, x: int) -> None:
        self.input.append(x)

    def pop(self) -> int:
        if len(self.output) == 0:
            self.sort()

        return self.output.pop()


    def peek(self) -> int:
        if len(self.output) == 0:
            self.sort()

        return self.output[-1]


    def empty(self) -> bool:
        if len(self.output) == 0 and len(self.input) == 0:
            return True
        return False





# ---------------------------------------------------------------------------
# 아래는 테스트용 도구. 문제 풀이와는 상관없으니 그냥 두고 위만 채우면 된다.
# ---------------------------------------------------------------------------

# 한 케이스 = 연산을 차례로 부르는 한 줄의 시나리오.
# 한 걸음은 (연산, 인자, 기대값) 이다. push 는 돌려주는 게 없으니 기대값 자리에 None.
# 기대값 자리에 예외 클래스(IndexError 같은)를 적으면 "그 예외가 나야 통과"라는 뜻이다.
#
# 케이스2~4 는 어제 C 버전의 CASE2~4 를 그대로 옮겼다. 하나만 다르다.
#   케이스2  C 는 빈 큐의 peek/pop 이 0 을 돌려주기로 했지만, 파이썬 버전은 에러를 던지기로 했다.
#            (빈 list 의 pop() 이 IndexError 를 던지는 것과 같은 약속)
#            "어제랑 똑같겠지" 하고 안 돌렸으면 이 차이를 못 봤다.
CASES = [
    ("예제", [
        ("push", 1, None),
        ("push", 2, None),
        ("peek", None, 1),
        ("pop", None, 1),
        ("empty", None, False),
    ]),
    ("케이스2 빈 큐", [
        ("peek", None, IndexError),
        ("pop", None, IndexError),
        ("empty", None, True),
    ]),
    ("케이스3 넣기만 하고 빼기만", [
        ("push", 1, None),
        ("push", 2, None),
        ("pop", None, 1),
        ("pop", None, 2),
        ("empty", None, True),
    ]),
    ("케이스4 번갈아", [
        ("push", 1, None),
        ("pop", None, 1),
        ("push", 2, None),
        ("pop", None, 2),
    ]),
]


def run_case(name: str, steps: list) -> bool:
    q = MyQueue()

    for i, (op, arg, expected) in enumerate(steps, 1):
        if op == "push":
            q.push(arg)
            print(f"       push({arg})")
            continue

        if isinstance(expected, type) and issubclass(expected, Exception):
            try:
                got = getattr(q, op)()
            except expected:
                print(f"       {op}() -> {expected.__name__} (기대대로)")
                continue
            print(f"FAIL   {name}: {i}번째 {op}()")
            print(f"         기대 {expected.__name__} 발생")
            print(f"         실제 {got!r} 를 돌려줌")
            return False

        got = getattr(q, op)()

        # peek 은 보기만 해야 한다. 한 번 더 불러서 값과 empty() 가 그대로인지 본다.
        if op == "peek":
            empty_before = q.empty()
            again = q.peek()
            if again != got or q.empty() != empty_before:
                print(f"FAIL   {name}: {i}번째 peek 이 큐를 바꿨다 "
                      f"(첫 peek {got!r}, 다시 peek {again!r})")
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
