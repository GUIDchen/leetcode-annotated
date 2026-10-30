# 题目：1302. 层数最深叶子节点的和（Deepest Leaves Sum）
# 思路：层序遍历（BFS）。每处理完一层就把累加和清零，循环结束时留下的正是最深一层的叶子节点之和。
# 时间复杂度：O(n)，每个节点进出队列一次；空间复杂度：O(n)，队列最多存一层节点。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def deepestLeavesSum(self, root: Optional[TreeNode]) -> int:  # root：二叉树根节点
        q = deque([root])  # 层序遍历队列，初始只有根节点
        while q:  # 队列非空说明还存在下一层
            ans = 0  # 进入新的一层先清零，最后留下的就是最深层的和
            for _ in range(len(q)):  # 用当前队列长度固定次数，只处理本层节点
                node = q.popleft()  # 取出队首节点
                ans += node.val  # 累加该节点的值
                if node.left:  # 有左孩子就入队
                    q.append(node.left)  # 左孩子成为下一层节点
                if node.right:  # 有右孩子就入队
                    q.append(node.right)  # 右孩子成为下一层节点
        return ans  # 循环结束时 ans 就是最深叶子节点的和
