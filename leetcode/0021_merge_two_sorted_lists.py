"""LeetCode 21. Merge Two Sorted Lists  —  파이썬 버전

이미 정렬된 연결 리스트 두 개를 받아서, 정렬된 리스트 하나로 합쳐 head 를 돌려주는 문제예요 (๑•̀ᴗ•́)

입력:
    list1, list2    각각 정렬된 리스트의 head. 비어 있으면 None 이에요

제약:
    노드 개수는 각각 0 ~ 50
    -100 <= Node.val <= 100        음수도 들어와요
    두 리스트 모두 오름차순 (같은 값이 연달아 있을 수 있음)

LIST.md 의 연결고리: 노드를 복사하지 않고 재사용해서 두 리스트를 하나로 이어요.
소유권이 넘어가는 순간을 손으로 쓰게 돼요.

처음 푸는 문제라 백지에서 시작해요.

실행:
    C:/Users/Beak/Desktop/Jungle/Algorithm/.venv/Scripts/python.exe 0021_merge_two_sorted_lists.py
"""
from re import search
from typing import Optional


class ListNode:
    """LeetCode 가 주는 정의 그대로예요."""

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    # 문제 조건: 새 노드를 만들지 말고, 두 리스트의 노드를 이어 붙여서 만들어야 해요.
    # LeetCode 채점기는 이걸 안 보지만, 아래 검산기는 봐요.
    # 결과에 입력에 없던 노드가 섞여 있으면 FAIL 이 나요 ( ˘•ω•˘ )

    def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
        if list1 is None or list2 is None:
            if list1 is None and list2 is None: return None
            elif list1 is None: return list2
            else: return list1


        if list1.next is None and list2.next is None:
            if list1.val <= list2.val :
                list1.next = list2
                return list1
            else:
                list2.next = list1
                return list2

        temp = ListNode()
        temp2 = ListNode()

        if list1.val <= list2.val:
            cur = list1
            search_list = list2
            return_i = 0
        else:
            cur = list2
            search_list = list1
            return_i = 1

        while cur.next is not None:
            if search_list.next is None:
                if cur.next.val >= search_list.val:
                    temp2 = cur.next

                    cur.next = search_list
                    cur.next.next = temp2
                    break
                else: cur = cur.next

            elif cur.next.val >= search_list.val:
                temp = search_list.next
                temp2 = cur.next

                cur.next = search_list
                cur.next.next = temp2
                search_list = temp

            else:
                cur = cur.next


        if cur.val <= search_list.val: cur.next = search_list
        if return_i == 0: return list1
        else: return list2



# ---------------------------------------------------------------------------
# 아래는 검산용이에요. 풀이랑은 상관없으니 그냥 두고 위만 채우면 돼요.
# ---------------------------------------------------------------------------

# 한 케이스 = 한 줄이에요.
#
#   "1 2 4 + 1 3 4 -> 1 1 2 3 4 4"
#    ~~~~~   ~~~~~    ~~~~~~~~~~~
#    list1   list2    기대하는 결과
#
# 숫자는 띄어쓰기로 나눠요. 빈 리스트는 [] 라고 쓰면 돼요.
# 오름차순이 아닌 입력을 쓰면 검산기가 돌리기 전에 알려 줘요.
#
# 예제 세 개는 문제에 나온 그대로예요. 나머지는 직접 만들어 주세요 — 반례 3개 룰이에요 (ง'̀-'́)ง
# 기대 결과도 손으로 먼저 계산해서 적어 두고 돌려 주세요.
CASES = [
    ("예제1", "1 2 4 + 1 3 4 -> 1 1 2 3 4 4"),
    ("예제2", "[] + [] -> []"),
    ("예제3", "[] + 0 -> 0"),
    ("케이스4", "1 1 1 + 1 1 1 -> 1 1 1 1 1 1"),
    ("케이스5", "-5 4 + 1 -> -5 1 4"),
    ("케이스6", "1 + -5 -> -5 1"),
    ("케이스7", "5 + 1 2 4 -> 1 2 4 5"),
    ("케이스8", "1 + 1 1 -> 1 1 1"),

]


def parse_values(text: str):
    """"1 2 4" -> [1, 2, 4], "[]" 나 빈칸 -> []. 못 읽으면 None."""
    text = text.strip()
    if text in ("", "[]"):
        return []
    try:
        return [int(w) for w in text.split()]
    except ValueError:
        return None


def parse_case(script: str):
    """"A + B -> C" 를 ([A], [B], [C]) 로 나눠요. 못 읽으면 None."""
    if script.count("->") != 1:
        return None
    left, right = script.split("->")
    if left.count("+") != 1:
        return None
    a, b = left.split("+")
    parts = (parse_values(a), parse_values(b), parse_values(right))
    if any(p is None for p in parts):
        return None
    return parts


def build(values: list) -> Optional[ListNode]:
    """[1, 2, 3] -> 1 -> 2 -> 3 -> None"""
    head = None
    for v in reversed(values):
        head = ListNode(v, head)
    return head


def walk(head: Optional[ListNode]) -> list:
    """head 부터 노드를 차례로 모아요. 순환하면 무한루프 대신 에러를 내요."""
    nodes = []
    seen = set()
    node = head
    while node is not None:
        if id(node) in seen:
            raise RuntimeError(f"순환 발견: 지금까지 {[n.val for n in nodes]}")
        seen.add(id(node))
        nodes.append(node)
        node = node.next
    return nodes


def run_case(name: str, script: str) -> bool:
    parsed = parse_case(script)
    if parsed is None:
        print(f"FAIL   {name}: {script!r} 을 못 읽었어요")
        print("         \"1 2 4 + 1 3 4 -> 1 1 2 3 4 4\" 모양이어야 해요")
        return False
    a, b, expected = parsed

    for label, values in (("list1", a), ("list2", b)):
        if values != sorted(values):
            print(f"FAIL   {name}: {label} {values} 가 오름차순이 아니에요. 문제 조건 밖의 입력이에요")
            return False

    list1, list2 = build(a), build(b)
    given = {id(n) for n in walk(list1)} | {id(n) for n in walk(list2)}

    head = Solution().mergeTwoLists(list1, list2)
    nodes = walk(head)
    got = [n.val for n in nodes]

    if got != expected:
        print(f"FAIL   {name}: {a} + {b}")
        print(f"         기대 {expected}")
        print(f"         실제 {got}")
        return False

    new_nodes = sum(1 for n in nodes if id(n) not in given)
    if new_nodes:
        print(f"FAIL   {name}: 값은 맞는데, 입력에 없던 새 노드가 {new_nodes}개 섞여 있어요")
        return False

    print(f"PASS   {name}: {a} + {b} -> {got}")
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
