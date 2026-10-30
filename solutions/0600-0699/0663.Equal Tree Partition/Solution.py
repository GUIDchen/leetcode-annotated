# 题目：663. 均匀树划分（Equal Tree Partition）
# 思路：后序 DFS 收集每棵子树的和；总和为偶数且存在某棵「真子树」的和等于总和一半，即可切分。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(n)，递归深度与 seen 列表各为 O(n)。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def checkEqualTree(self, root: TreeNode) -> bool:  # root 是树根，返回能否切成两个和相等的部分
        def sum(root):  # 内部辅助函数：后序 DFS 求出子树和并写入 seen
            if root is None:  # 空节点子树和为 0
                return 0  # 递归出口，返回 0
            l, r = sum(root.left), sum(root.right)  # 先求左右子树的子树和
            seen.append(l + r + root.val)  # 当前子树和 = 左 + 右 + 根节点值，追加进 seen
            return seen[-1]  # 直接返回刚追加的结果，避免重复计算

        seen = []  # 用列表收集所有子树和（包括整棵树的和）
        s = sum(root)  # 求整棵树的总和，顺便填充 seen
        if s % 2 == 1:  # 总和为奇数就不可能平分
            return False  # 直接判定失败
        seen.pop()  # 弹出整棵树的和：切分必须落在真子树上
        return s // 2 in seen  # 存在真子树和等于总和一半即可切分
