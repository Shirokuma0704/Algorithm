"""LeetCode 100. Same Tree

두 이진 트리의 root 인 p 와 q 를 받아, 두 트리가 같은지 판정한다.
같다는 건 두 가지가 동시에 성립한다는 뜻이다.
    1. 구조가 같다 (어느 자리에 노드가 있고 없는지가 같다).
    2. 같은 자리의 노드끼리 val 이 같다.

제약:
    노드 개수 0 ~ 100, -10^4 <= Node.val <= 10^4
    -> 빈 트리(둘 다 None)가 입력으로 들어올 수 있다.

이 파일은 재풀이다. C 버전(0100_same_tree.c)은 이미 있으니 열지 말고 백지에서 쓴다.
파일을 보면서 옮기면 번역이 되고, 재풀이로 남는 게 없다.

실행:
    C:/Users/Beak/Desktop/Jungle/Algorithm/.venv/Scripts/python.exe 0100_same_tree.py
"""
from typing import Optional


class TreeNode:
    """LeetCode 가 주는 정의 그대로."""

    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def isSameTree(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:
        """반환값은 트리가 아니라 **두 트리가 같은지 여부(bool)** 다.

        p 와 q 는 각각 None 일 수 있고, 둘 다 None 일 수도 있다.
        """
        # 여기부터'
        if p is None and q is None:
            return True

        if (p is None) != (q is None):
            return False

        if p.val != q.val:
            return False

        left_result = Solution.isSameTree(self, p.left,q.left)

        right_result = Solution.isSameTree(self, p.right,q.right)
        if left_result is True and right_result is True:
            return True


        return False






# ---------------------------------------------------------------------------
# 아래는 테스트용 도구. 문제 풀이와는 상관없으니 그냥 두고 위만 채우면 된다.
# ---------------------------------------------------------------------------

def build(values: list) -> Optional[TreeNode]:
    r"""LeetCode 표기법(레벨 순서, 빈 자리는 None)을 실제 트리로 바꾼다.

    [1, 2, 3]       ->      1        [1, None, 2]  ->    1
                           / \                            \
                          2   3                             2
    """
    if not values or values[0] is None:
        return None

    root = TreeNode(values[0])
    queue = [root]
    i = 1
    while queue and i < len(values):
        node = queue.pop(0)

        if i < len(values):
            if values[i] is not None:
                node.left = TreeNode(values[i])
                queue.append(node.left)
            i += 1

        if i < len(values):
            if values[i] is not None:
                node.right = TreeNode(values[i])
                queue.append(node.right)
            i += 1

    return root


# 앞의 세 개는 문제에 나온 예제다.
# 나머지는 비워뒀다 - 어떤 입력에서 깨질지 직접 정해서 채울 것.
# 기대값을 손으로 먼저 계산해 적어둔 다음에 돌린다. 통과는 증거가 아니다.
#
# 채울 때 생각해볼 갈래 세 개 (문장은 힌트고, 실제 입력은 직접 고른다):
#   - 한쪽에만 노드가 있고 다른 쪽 자리는 비어 있으면 어떻게 되는가
#   - 값은 전부 같은데 왼쪽/오른쪽 자리가 바뀌어 있으면 어떻게 되는가
#   - 트리가 아예 비어 있는 경우는 몇 가지가 있고, 각각 답이 무엇인가
CASES = [
    # (p, q, 기대 출력)
    ([1, 2, 3], [1, 2, 3], True),
    ([1, 2], [1, None, 2], False),
    ([1, 2, 1], [1, 1, 2], False),
]


def main() -> None:
    passed = 0
    for i, (p_values, q_values, expected) in enumerate(CASES, 1):
        try:
            got = Solution().isSameTree(build(p_values), build(q_values))
        except Exception as e:
            print(f"[{i}] ERROR  입력 {p_values} / {q_values} -> {type(e).__name__}: {e}")
            continue

        if got is expected:
            print(f"[{i}] PASS   입력 {p_values} / {q_values} -> {got}")
            passed += 1
        else:
            print(f"[{i}] FAIL   입력 {p_values} / {q_values}")
            print(f"         기대 {expected!r}")
            print(f"         실제 {got!r}")

    print(f"\n{passed}/{len(CASES)} 통과")


if __name__ == "__main__":
    main()
