# 题目：1609. 奇偶树（Even Odd Tree）
# 思路：BFS 逐层遍历，prev 记录同层上一个值；偶数层须为奇数且严格递增，奇数层须为偶数且严格递减。
# 时间复杂度：O(n)，每个节点进出队各一次；空间复杂度：O(n)，队列最宽时存一整层。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # 题解类
    def isEvenOddTree(self, root: Optional[TreeNode]) -> bool:  # root 为二叉树根节点
        even = 1  # 1 表示当前是偶数层（从 0 开始数的第 0、2、4… 层）
        q = deque([root])  # 双端队列，初始只装入根节点
        while q:  # 队列非空就继续按层处理
            prev = 0 if even else inf  # 偶数层从 0 起以保证严格递增，奇数层从 inf 起以保证严格递减
            for _ in range(len(q)):  # 循环开始时队列中恰好是本层全部节点，故只循环本层大小次
                root = q.popleft()  # 从队首取出一个节点
                if even and (root.val % 2 == 0 or prev >= root.val):  # 偶数层要求节点值为奇数且严格递增（% 2 == 0 是偶数，prev >= 当前值说明没递增）
                    return False  # 违反条件，返回 False
                if not even and (root.val % 2 == 1 or prev <= root.val):  # 奇数层要求节点值为偶数且严格递减（% 2 == 1 是奇数，prev <= 当前值说明没递减）
                    return False  # 违反条件，返回 False
                prev = root.val  # 记录当前值，供同层下一个节点比较
                if root.left:  # 左孩子存在则入队，留到下一层
                    q.append(root.left)  # 左孩子入队
                if root.right:  # 右孩子存在则入队
                    q.append(root.right)  # 右孩子入队
            even ^= 1  # 本层结束，切换层号的奇偶
        return True  # 所有层都满足要求，返回 True
