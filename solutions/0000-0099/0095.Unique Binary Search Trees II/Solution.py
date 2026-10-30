# 题目：95. 不同的二叉搜索树 II（Unique Binary Search Trees II）
# 思路：分治 + 回溯，枚举区间 [i, j] 内每个值 v 作根，左右子区间分别递归生成全部 BST 后做笛卡尔积组合。
# 时间复杂度：O(4^n / n^{3/2})，即第 n 个卡特兰数级别的树个数；空间复杂度：O(4^n / n^{3/2})，需保存所有生成的树。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def generateTrees(self, n: int) -> List[Optional[TreeNode]]:  # n 是结点个数，返回所有结构不同的 BST
        def dfs(i: int, j: int) -> List[Optional[TreeNode]]:  # 生成用 [i, j] 区间内所有值能构成的全部 BST
            if i > j:  # 区间为空，说明这里没有子树
                return [None]  # 返回「一个空子树」这一种方案，供上层组合使用
            ans = []  # 收集当前区间能生成的所有 BST 根结点
            for v in range(i, j + 1):  # 枚举根结点的取值 v，左小右大自然满足 BST 性质
                left = dfs(i, v - 1)  # 左子树只能取比 v 小的区间 [i, v-1]
                right = dfs(v + 1, j)  # 右子树只能取比 v 大的区间 [v+1, j]
                for l in left:  # 枚举每一种左子树形态
                    for r in right:  # 枚举每一种右子树形态
                        ans.append(TreeNode(v, l, r))  # 左右子树组合出以 v 为根的新 BST
            return ans  # 返回当前区间的全部 BST

        return dfs(1, n)  # 结点值为 1..n，从整个区间开始分治
