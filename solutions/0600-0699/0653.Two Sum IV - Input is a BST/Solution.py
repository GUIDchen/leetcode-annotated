# 题目：653. 两数之和 IV - 输入二叉搜索树（Two Sum IV - Input is a BST）
# 思路：DFS 遍历整棵树，用哈希集合记录已见过的节点值，对每个节点检查补数 k - 当前值是否已在集合中，命中即说明存在和为 k 的一对。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(n)，哈希集合最多存 n 个节点值（递归栈另计 O(h)）。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def findTarget(self, root: Optional[TreeNode], k: int) -> bool:  # root 是树根，k 是目标和，返回是否存在两节点值之和为 k
        def dfs(root):  # 递归函数：判断以 root 为根的子树中能否找到配对
            if root is None:  # 空节点没有值可以配对
                return False  # 该分支失败
            if k - root.val in vis:  # 之前访问过补数 k - 当前值，说明这一对已经凑齐
                return True  # 已找到答案，立即返回
            vis.add(root.val)  # 把当前值加入集合，供后续节点查询
            return dfs(root.left) or dfs(root.right)  # 左右子树任一侧找到即算成功

        vis = set()  # 记录 DFS 过程中已经访问过的节点值
        return dfs(root)  # 从整棵树的根开始搜索
