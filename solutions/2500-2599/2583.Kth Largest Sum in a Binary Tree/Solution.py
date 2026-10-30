# 题目：2583. 二叉树中的第 K 大层和（Kth Largest Sum in a Binary Tree）
# 思路：用 deque 做 BFS 逐层遍历，累加每层节点值得到层和并存入数组，最后用 nlargest 取出第 k 大；层数不足 k 返回 -1。
# 时间复杂度：O(n log L)（n 为节点数、L 为层数，nlargest 近似 O(L log k)）；空间复杂度：O(n)，队列与层和数组最多存 O(n) 个节点。
# Definition for a binary tree node.  # 题目给出的二叉树节点定义注释
# class TreeNode:  # 节点类
#     def __init__(self, val=0, left=None, right=None):  # 构造函数：值、左孩子、右孩子
#         self.val = val  # 节点值
#         self.left = left  # 左孩子
#         self.right = right  # 右孩子
class Solution:  # LeetCode 约定的题解类
    def kthLargestLevelSum(self, root: Optional[TreeNode], k: int) -> int:  # root 为根节点，k 为要求的第几大；返回第 k 大层和
        arr = []  # 保存每一层的节点值之和
        q = deque([root])  # BFS 队列，初始化只放根节点
        while q:  # 队列非空说明还有待处理的层
            t = 0  # 当前层的节点值累加和，每层开始时清零
            for _ in range(len(q)):  # 先固定本层节点个数，只处理这一层
                root = q.popleft()  # 从队首取出节点
                t += root.val  # 把该节点的值累加到本层和
                if root.left:  # 左孩子存在才入队
                    q.append(root.left)  # 左孩子留到下一层处理
                if root.right:  # 右孩子存在才入队
                    q.append(root.right)  # 右孩子留到下一层处理
            arr.append(t)  # 本层处理完毕，把该层和存入数组
        return -1 if len(arr) < k else nlargest(k, arr)[-1]  # 层数不足 k 返回 -1，否则取第 k 大（降序列表的末位）
