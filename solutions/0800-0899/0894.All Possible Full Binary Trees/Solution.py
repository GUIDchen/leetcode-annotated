# 题目：894. 所有可能的真二叉树（All Possible Full Binary Trees）
# 核心思路：真二叉树节点数必为奇数；枚举左子树节点数 i，右子树为 n-1-i，两两组合并用 cache 记忆化。
# 时间复杂度：约 O(Catalan(n/2))，与输出规模同阶；空间复杂度：O(Catalan(n/2))，缓存全部子树。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def allPossibleFBT(self, n: int) -> List[Optional[TreeNode]]:  # n：节点总数；只有奇数个节点才能构成真二叉树
        @cache  # 记忆化递归：相同 n 的子问题只求一次
        def dfs(n: int) -> List[Optional[TreeNode]]:  # 返回用 n 个节点能构成的所有真二叉树
            if n == 1:  # 只有一个节点：唯一的真二叉树就是这个叶子
                return [TreeNode()]  # 构造一个值为 0 的叶子节点
            ans = []  # 收集当前 n 的所有组合方式
            for i in range(n - 1):  # 枚举左子树节点数 i，根占 1 个，右子树为 n-1-i
                j = n - 1 - i  # 右子树节点数
                for left in dfs(i):  # 遍历所有可能的左子树
                    for right in dfs(j):  # 与所有可能的右子树两两组合
                        ans.append(TreeNode(0, left, right))  # 以新根串起这对左右子树
            return ans  # 返回当前 n 的全部组合

        return dfs(n)  # 答案就是 n 个节点的全部真二叉树
