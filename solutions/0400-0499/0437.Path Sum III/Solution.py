# 题目：437. 路径总和 III（Path Sum III）
# 思路：前缀和 + 哈希表计数——dfs 沿根到当前节点的路径维护前缀和 s，答案累加 cnt[s - targetSum]（以当前节点结尾的合法路径数），回溯时撤销计数。
# 时间复杂度：O(n)，每个节点进、出各一次；空间复杂度：O(n)，Counter 最多存 n 个前缀和，递归栈深度最多 n。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def pathSum(self, root: Optional[TreeNode], targetSum: int) -> int:  # 统计节点值之和恰好等于 targetSum 的向下路径条数（起点不限于根）
        def dfs(node, s):  # 内层 dfs：node 是当前节点，s 是根到父节点的前缀和
            if node is None:  # 走到空节点，说明这条路径到头了
                return 0  # 空节点贡献 0 条路径
            s += node.val  # 把当前节点值累加进根到当前节点的前缀和
            ans = cnt[s - targetSum]  # 之前若出现过前缀和 s-targetSum，二者相减就得到一条以当前节点结尾的合法路径；Counter 缺键返回 0
            cnt[s] += 1  # 把当前前缀和计入表，供子树查询使用
            ans += dfs(node.left, s)  # 递归统计左子树内部的合法路径
            ans += dfs(node.right, s)  # 递归统计右子树内部的合法路径
            cnt[s] -= 1  # 回溯：撤销当前前缀和的计数，保证表里只有根到当前节点的路径
            return ans  # 返回本节点及其子树贡献的路径总数

        cnt = Counter({0: 1})  # 前缀和计数表：空前缀和 0 记 1 次，这样「从根出发」的路径也能被统计到
        return dfs(root, 0)  # 从根开始 dfs，初始前缀和为 0
