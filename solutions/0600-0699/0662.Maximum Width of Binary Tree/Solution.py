# 题目：662. 二叉树最大宽度（Maximum Width of Binary Tree）
# 核心思路：BFS 按满二叉树给节点编号，每层宽度 = 最右编号 - 最左编号 + 1。
# 时间复杂度：O(n)；空间复杂度：O(n)，队列最多存一层节点。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def widthOfBinaryTree(self, root: Optional[TreeNode]) -> int:  # root 是树根，返回所有层中的最大宽度
        ans = 0  # ans 记录各层宽度的最大值
        q = deque([(root, 1)])  # 队列存 (节点, 满二叉树编号)，根编号从 1 开始
        while q:  # 逐层处理，队列不空就继续
            ans = max(ans, q[-1][1] - q[0][1] + 1)  # 本层最右编号 - 本层最左编号 + 1 即本层宽度
            for _ in range(len(q)):  # 只循环当前层的节点数，保证一层的节点一起出队
                root, i = q.popleft()  # 出队并拆出节点与编号
                if root.left:  # 有左孩子就入队
                    q.append((root.left, i << 1))  # 左孩子编号为 2i
                if root.right:  # 有右孩子就入队
                    q.append((root.right, i << 1 | 1))  # 右孩子编号为 2i+1
        return ans  # 返回最大宽度
