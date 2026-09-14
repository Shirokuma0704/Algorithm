"""LeetCode 206. Reverse Linked List

단일 연결 리스트의 head를 받아 뒤집은 리스트의 head를 반환한다.

제약:
    노드 개수 0 ~ 5000, -5000 <= Node.val <= 5000

실행:
    C:/Users/Beak/Desktop/Jungle/Week2/.venv/Scripts/python.exe 0206_reverse_linked_list.py
"""
from typing import Optional


class ListNode:
    """LeetCode가 주는 정의 그대로."""

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        """새 노드를 만들지 말고, 기존 노드의 next 방향만 뒤집을 것 (추가 공간 O(1)).

        반환값은 리스트가 아니라 **뒤집힌 리스트의 head 노드**다.
        """
        # 여기부터
        if head is None:
            return head

        prev = None
        node = head

        while node is not None:
            next_node = node.next
            node.next = prev
            prev = node
            node = next_node

        return prev

# ---------------------------------------------------------------------------
# 아래는 테스트용 도구. 문제 풀이와는 상관없으니 그냥 두고 위만 채우면 된다.
# ---------------------------------------------------------------------------

def build(values: list) -> Optional[ListNode]:
    """[1,2,3] -> 1 -> 2 -> 3 -> None"""
    head = None
    for v in reversed(values):
        head = ListNode(v, head)
    return head


def to_list(head: Optional[ListNode]) -> list:
    """1 -> 2 -> 3 -> None -> [1,2,3]  (순환하면 무한루프 대신 에러를 낸다)"""
    out = []
    seen = set()
    node = head
    while node is not None:
        if id(node) in seen:
            raise RuntimeError(f"순환 발견: 지금까지 {out}")
        seen.add(id(node))
        out.append(node.val)
        node = node.next
    return out


# 앞의 세 개는 문제에 나온 예제다.
# 나머지 두 줄은 비워뒀다 — 어떤 입력에서 깨질지 직접 정해서 채울 것.
# (기대값도 손으로 먼저 계산해서 적어둔 다음에 돌린다)
CASES = [
    # (입력, 기대 출력)
    ([1, 2, 3, 4, 5], [5, 4, 3, 2, 1]),
    ([1, 2], [2, 1]),
    ([], []),
    ([1],[1]),
    ([2,2],[2,2])
]


def main() -> None:
    passed = 0
    for i, (values, expected) in enumerate(CASES, 1):
        try:
            got = to_list(Solution().reverseList(build(values)))
        except Exception as e:
            print(f"[{i}] ERROR  입력 {values} -> {type(e).__name__}: {e}")
            continue

        if got == expected:
            print(f"[{i}] PASS   입력 {values} -> {got}")
            passed += 1
        else:
            print(f"[{i}] FAIL   입력 {values}")
            print(f"         기대 {expected}")
            print(f"         실제 {got}")

    print(f"\n{passed}/{len(CASES)} 통과")


if __name__ == "__main__":
    main()
