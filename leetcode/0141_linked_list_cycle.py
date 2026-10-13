"""LeetCode 141. Linked List Cycle  —  파이썬 버전

연결 리스트의 head 를 받아서, 리스트 안에 순환(cycle)이 있으면 True, 없으면 False 를 돌려주는 문제예요 (๑•̀ᴗ•́)

순환이란: 어떤 노드의 next 를 계속 따라가다 보면 이미 지나온 노드로 다시 돌아오는 것.
문제 설명에 나오는 pos 는 "꼬리가 몇 번째 노드로 이어지는지"인데, 함수에는 안 넘어와요.
함수가 받는 건 head 하나뿐이에요.

입력:
    head    리스트의 첫 노드. 비어 있으면 None 이에요

제약:
    노드 개수는 0 ~ 10^4
    -10^5 <= Node.val <= 10^5        값은 겹칠 수 있어요
    pos 는 -1(순환 없음) 이거나 리스트 안의 올바른 위치

더 해 보기 (LeetCode 의 Follow up): 메모리를 O(1) 만 쓰고 풀 수 있나요?

LIST.md 의 연결고리: 순환 감지. 리스트를 순회하며 free 하는 루프가 왜 안 끝나는지와 같은 그림이에요.

처음 푸는 문제라 백지에서 시작해요.

실행:
    C:/Users/Beak/Desktop/Jungle/Algorithm/.venv/Scripts/python.exe 0141_linked_list_cycle.py
"""
from typing import Optional


class ListNode:
    """LeetCode 가 주는 정의 그대로예요."""

    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    # 검산기는 돌려준 값 말고 하나를 더 봐요.
    # 함수가 끝난 뒤에 리스트의 연결(next)이 처음 모양 그대로인지요.
    # 남의 자료구조를 들여다보기만 하고 원래대로 두는 게 예의라서요 ( ˘•ω•˘ )

    def hasCycle(self, head: Optional[ListNode]) -> bool:
        if head.next is None:
            return False
        cur = head.next
        while cur.next is not None:
            if cur.val is None:
                return True
            cur.val = None
            cur = cur.next
        return False



# ---------------------------------------------------------------------------
# 아래는 검산용이에요. 풀이랑은 상관없으니 그냥 두고 위만 채우면 돼요.
# ---------------------------------------------------------------------------

# 한 케이스 = 한 줄이에요.
#
#   "3 2 0 -4 @ 1 -> true"
#    ~~~~~~~~   ~    ~~~~
#    노드 값들  pos  기대하는 결과 (true / false)
#
# pos 는 꼬리가 이어지는 노드의 위치예요. 0부터 세요. 순환이 없으면 -1 이에요.
# 빈 리스트는 [] 라고 쓰면 돼요. 빈 리스트의 pos 는 -1 이어야 해요.
# 리스트 밖을 가리키는 pos 를 쓰면 검산기가 돌리기 전에 알려 줘요.
#
# 예제 세 개는 문제에 나온 그대로예요. 나머지는 직접 만들어 주세요 — 반례 3개 룰이에요 (ง'̀-'́)ง
# 기대 결과도 손으로 먼저 정해서 적어 두고 돌려 주세요.
CASES = [
    ("예제1", "3 2 0 -4 @ 1 -> true"),
    ("예제2", "1 2 @ 0 -> true"),
    ("예제3", "1 @ -1 -> false"),
    ("예제4", "1 2 3 1 2 4 1 2 1 2 @ -1 -> false"),

]


def parse_case(script: str):
    """"3 2 0 -4 @ 1 -> true" 를 ([3, 2, 0, -4], 1, True) 로 나눠요. 못 읽으면 None."""
    if script.count("->") != 1 or script.count("@") != 1:
        return None
    left, right = script.split("->")
    values_text, pos_text = left.split("@")
    values_text = values_text.strip()
    try:
        values = [] if values_text in ("", "[]") else [int(w) for w in values_text.split()]
        pos = int(pos_text)
    except ValueError:
        return None
    answer = right.strip().lower()
    if answer not in ("true", "false"):
        return None
    return values, pos, answer == "true"


def build(values: list, pos: int):
    """값 목록으로 리스트를 만들고, pos 가 0 이상이면 꼬리를 그 노드에 이어요. (head, 노드 목록) 을 돌려줘요."""
    nodes = [ListNode(v) for v in values]
    for a, b in zip(nodes, nodes[1:]):
        a.next = b
    if nodes and pos >= 0:
        nodes[-1].next = nodes[pos]
    return (nodes[0] if nodes else None), nodes


def run_case(name: str, script: str) -> bool:
    parsed = parse_case(script)
    if parsed is None:
        print(f"FAIL   {name}: {script!r} 을 못 읽었어요")
        print("         \"3 2 0 -4 @ 1 -> true\" 모양이어야 해요")
        return False
    values, pos, expected = parsed

    if not (pos == -1 or 0 <= pos < len(values)):
        print(f"FAIL   {name}: pos {pos} 가 리스트 밖이에요. -1 이거나 0 ~ {len(values) - 1} 이어야 해요")
        return False

    head, nodes = build(values, pos)
    links_before = [id(n.next) for n in nodes]

    got = Solution().hasCycle(head)

    if not isinstance(got, bool):
        print(f"FAIL   {name}: True / False 가 아니라 {got!r} 을 돌려줬어요")
        return False
    if got != expected:
        print(f"FAIL   {name}: {values} @ {pos}")
        print(f"         기대 {expected}")
        print(f"         실제 {got}")
        return False
    changed = sum(1 for n, before in zip(nodes, links_before) if id(n.next) != before)
    if changed:
        print(f"FAIL   {name}: 답은 맞는데, 노드 {changed}개의 next 가 바뀌어 있어요. 리스트를 원래대로 둬야 해요")
        return False

    print(f"PASS   {name}: {values} @ {pos} -> {got}")
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
