"""LeetCode 234. Palindrome Linked List  —  파이썬 버전

단일 연결 리스트의 head 를 받아서, 앞에서 읽으나 뒤에서 읽으나 값이 같으면(회문, palindrome) True,
아니면 False 를 돌려주는 문제예요 (｡･ω･｡)

회문이란: 1 2 2 1 이나 1 2 1 처럼 거꾸로 읽어도 같은 순서인 것.
단일 연결 리스트라서 next 로 앞으로만 갈 수 있고, 뒤로 가는 길은 없어요.

입력:
    head    리스트의 첫 노드. 노드는 최소 한 개 있어요

제약:
    노드 개수는 1 ~ 10^5
    0 <= Node.val <= 9

더 해 보기 (LeetCode 의 Follow up): 시간 O(n), 메모리 O(1) 로 풀 수 있나요?

LIST.md 의 연결고리: 뒤집어 쓰고 되돌려놓기. 남의 자료구조를 건드렸으면 원상복구까지가 책임이에요.

처음 푸는 문제라 백지에서 시작해요.

실행:
    C:/Users/Beak/Desktop/Jungle/Algorithm/.venv/Scripts/python.exe 0234_palindrome_linked_list.py
"""
from operator import truediv, countOf
from typing import Optional


class ListNode:
    """LeetCode 가 주는 정의 그대로예요."""

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    # 검산기는 돌려준 값 말고 하나를 더 봐요.
    # 함수가 끝난 뒤에 리스트가 처음 모양 그대로인지요. 노드마다 next 와 val 을 둘 다 봐요.
    # 중간에 리스트를 바꿔도 괜찮지만, 돌려주기 전에 원래대로 돌려놔야 PASS 예요 ( ˘•ω•˘ )

    def isPalindrome(self, head: Optional[ListNode]) -> bool:

        def check(self, current, val, x, odd) -> bool:
            if odd is not True:
                current = current.next

            m = 1

            if current.next is None: return False

            while current != None:
                if x < m: return False
                if val[x - m] != current.val:
                    return False
                m += 1
                current = current.next

            if x == m - 1: return True

            return False

        vals = []
        n = 0
        curr = head


        while curr != None:

            if n >= 2:
                if curr.next is not None:
                    odd = None
                    if vals[n - 1] == curr.val:
                        odd = True
                        if check(self, curr, vals, n, odd): return True

                    if vals[n - 1] == curr.next.val:
                        odd = False
                        if check(self, curr, vals, n, odd): return True

            vals.append(curr.val)
            n += 1
            curr = curr.next

        if len(vals) == 1 or len(vals) == 0: return True
        if len(vals) == 2 and head.val == head.next.val: return True
        if len(vals) == 3 and vals[0] == vals[2]: return True
        return False


# ---------------------------------------------------------------------------
# 아래는 검산용이에요. 풀이랑은 상관없으니 그냥 두고 위만 채우면 돼요.
# ---------------------------------------------------------------------------

# 한 케이스 = 한 줄이고, 칸은 세 개예요.
#
#   ("예제1", "1 2 2 1 -> true", "NN줄")
#             ~~~~~~~    ~~~~    ~~~~
#               노드 값  기대 결과  노리는 줄
#
# 노드 값은 앞에서부터 띄어 써요. 기대 결과는 true / false 예요.
# 노리는 줄: 내 코드에서 비교 하나(>, <=, ==, != 같은 것)를 골라서, 딱 그 경계에 걸리는 입력을 쓰고 그 줄 번호를 적어요.
# 검산기는 이 칸을 검사하지 않고 결과 옆에 그대로 찍어 주기만 해요.
#
# 예제 두 개는 문제에 나온 그대로예요. 나머지는 직접 만들어 주세요 — 반례 3개 룰이에요 (ง •̀_•́)ง
# 기대 결과도 손으로 먼저 정해서 적어 두고 돌려 주세요. 노드 값이 빈 줄은 검산기가 건너뛰어요.
CASES = [
    ("예제1", "1 2 2 1 -> true", "예제"),
    ("예제2", "1 2 -> false", "예제"),
    ("케이스3", "1 -> true", "85줄"),
    ("케이스4", "1 2 4 4 2 1 -> true", "73줄, 45줄"),
    ("케이스5", "1 2 3 4 4 4 3 2 1 -> true", "77줄"),
    ("케이스6", "1 0 1 -> true", "87줄"),
]


def parse_case(script: str):
    """"1 2 2 1 -> true" 를 ([1, 2, 2, 1], True) 로 나눠요. 못 읽으면 None."""
    if script.count("->") != 1:
        return None
    left, right = script.split("->")
    try:
        values = [int(w) for w in left.split()]
    except ValueError:
        return None
    answer = right.strip().lower()
    if answer not in ("true", "false"):
        return None
    return values, answer == "true"


def build(values: list):
    """값 목록으로 리스트를 만들어요. (head, 노드 목록) 을 돌려줘요."""
    nodes = [ListNode(v) for v in values]
    for a, b in zip(nodes, nodes[1:]):
        a.next = b
    return (nodes[0] if nodes else None), nodes


def run_case(name: str, script: str, aim: str) -> bool:
    tag = f"   (노리는 줄: {aim})" if aim else "   (노리는 줄: 비어 있음)"

    parsed = parse_case(script)
    if parsed is None:
        print(f"FAIL   {name}: {script!r} 을 못 읽었어요{tag}")
        print("         \"1 2 2 1 -> true\" 모양이어야 해요")
        return False
    values, expected = parsed

    if not values:
        print(f"FAIL   {name}: 노드가 하나도 없어요. 이 문제는 노드가 최소 한 개예요{tag}")
        return False
    bad = [v for v in values if not 0 <= v <= 9]
    if bad:
        print(f"FAIL   {name}: 값 {bad} 가 범위 밖이에요. 0 ~ 9 만 돼요{tag}")
        return False

    head, nodes = build(values)
    links_before = [n.next for n in nodes]
    vals_before = [n.val for n in nodes]

    got = Solution().isPalindrome(head)

    if not isinstance(got, bool):
        print(f"FAIL   {name}: True / False 가 아니라 {got!r} 을 돌려줬어요{tag}")
        return False
    if got != expected:
        print(f"FAIL   {name}: {values}{tag}")
        print(f"         기대 {expected}")
        print(f"         실제 {got}")
        return False
    moved = sum(1 for n, before in zip(nodes, links_before) if n.next is not before)
    changed = sum(1 for n, before in zip(nodes, vals_before) if n.val != before)
    if moved or changed:
        print(f"FAIL   {name}: 답은 맞는데, 리스트가 원래 모양이 아니에요{tag}")
        print(f"         next 가 바뀐 노드 {moved}개, val 이 바뀐 노드 {changed}개")
        return False

    print(f"PASS   {name}: {values} -> {got}{tag}")
    return True


def main() -> None:
    passed = 0
    filled = 0
    for name, script, aim in CASES:
        if not script.strip():
            print(f"-      {name}: 빈 칸이라 건너뛰었어요")
            print()
            continue
        filled += 1
        try:
            ok = run_case(name, script, aim)
        except Exception as e:
            print(f"ERROR  {name}: {type(e).__name__}: {e}")
            ok = False
        passed += ok
        print()

    print(f"{passed}/{filled} 통과 (빈 칸 {len(CASES) - filled}개 건너뜀)")


if __name__ == "__main__":
    main()
