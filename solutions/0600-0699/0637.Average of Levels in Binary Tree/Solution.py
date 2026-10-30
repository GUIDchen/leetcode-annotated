# 题目：637. 二叉树的层平均值（Average of Levels in Binary Tree）
# 思路：用队列做 BFS，每轮先用 len(q) 固定本层节点数，整层出队求和、孩子入队，再求该层平均值。
# 时间复杂度：O(n)，每个节点进出队列一次；空间复杂度：O(w)，w 为树的最大宽度。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def averageOfLevels(self, root: Optional[TreeNode]) -> List[float]:  # 返回二叉树每一层节点值的平均值（自顶向下）
        q = deque([root])  # BFS 队列，先把根节点放入；deque 由判题环境提供
        ans = []  # ans 按层序保存每层的平均值
        while q:  # 队列非空说明还有待处理的层
            s, n = 0, len(q)  # s 是本层节点值之和，n 是本层节点数（必须先用 len(q) 固定住）
            for _ in range(n):  # 只处理本层的 n 个节点
                root = q.popleft()  # 取出队首节点
                s += root.val  # 把节点值累加进本层总和
                if root.left:  # 左孩子非空
                    q.append(root.left)  # 左孩子入队，属于下一层
                if root.right:  # 右孩子非空
                    q.append(root.right)  # 右孩子入队，属于下一层
            ans.append(s / n)  # 本层平均值：Python 的 / 结果是浮点数，无需额外转换
        return ans  # 按层序返回每层的平均值
