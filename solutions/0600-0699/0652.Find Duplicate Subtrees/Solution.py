# 题目：652. 寻找重复的子树（Find Duplicate Subtrees）
# 思路：后序遍历把每棵子树序列化成「根值,左子树串,右子树串」，用计数器统计每种形态出现次数，第二次出现时把该子树根节点加入答案。
# 时间复杂度：O(n^2)，最坏情况下字符串拼接与比较达到 O(n)；空间复杂度：O(n^2)，计数器保存全部子树的序列化串。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def findDuplicateSubtrees(  # 返回所有重复子树的根节点
        self, root: Optional[TreeNode]  # self 是实例本身，root 是整棵树的根节点
    ) -> List[Optional[TreeNode]]:  # 返回值是重复子树根节点组成的列表
        def dfs(root):  # 返回以 root 为根的子树的序列化串
            if root is None:  # 空节点用 '#' 占位，保证不同形态不会序列化成同一字符串
                return '#'  # 空节点直接返回占位符
            v = f'{root.val},{dfs(root.left)},{dfs(root.right)}'  # 先序拼接「根值,左子树串,右子树串」，形态相同必然串相同
            counter[v] += 1  # 该子树形态的出现次数加一
            if counter[v] == 2:  # 恰好在第二次出现时收录，避免同一形态重复加入
                ans.append(root)  # 记录这棵重复子树的根节点
            return v  # 把当前子树串回溯给父节点拼接

        ans = []  # 收集重复子树的根节点
        counter = Counter()  # 子树序列化串 → 出现次数的计数器
        dfs(root)  # 一次后序遍历即可同时填满 counter 与 ans
        return ans  # 返回收集到的重复子树根节点
