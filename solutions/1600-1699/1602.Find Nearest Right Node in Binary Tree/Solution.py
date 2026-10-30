# 题目：1602. 找到二叉树中最近的右侧节点（Find Nearest Right Node in Binary Tree）
# 思路：BFS 按层遍历，处理本层节点时若遇到 u，则同层右侧还有节点就返回队列中的下一个节点，否则返回空。
# 时间复杂度：O(n)，每个节点最多入队出队一次；空间复杂度：O(w)，w 为树的最大层宽。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def findNearestRightNode(self, root: TreeNode, u: TreeNode) -> Optional[TreeNode]:  # root 为树根，u 为目标节点，返回它同层右侧最近的节点
        q = deque([root])  # BFS 队列，用根节点初始化
        while q:  # 队列非空说明还有层没处理
            for i in range(len(q) - 1, -1, -1):  # 从大到小计数，只处理当前这一层的节点
                root = q.popleft()  # 取出队首节点
                if root == u:  # 找到目标节点 u
                    return q[0] if i else None  # i 不为 0 说明同层右侧还有节点，取队首；否则 u 是本层最后一个
                if root.left:  # 左孩子存在才入队
                    q.append(root.left)  # 左孩子加入队尾
                if root.right:  # 右孩子存在才入队
                    q.append(root.right)  # 右孩子加入队尾
