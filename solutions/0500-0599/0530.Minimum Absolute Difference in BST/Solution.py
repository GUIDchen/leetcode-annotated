# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
# 题目：530. 二叉搜索树的最小绝对差（Minimum Absolute Difference in BST）
# 思路：二叉搜索树的中序遍历严格递增，最小绝对差必在相邻两节点之间出现，边遍历边比较。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归栈深度等于树高。
class Solution:  # LeetCode 约定的题解类
    def getMinimumDifference(self, root: Optional[TreeNode]) -> int:  # root 是二叉搜索树的根
        def dfs(root: Optional[TreeNode]):  # 中序遍历：左 → 根 → 右
            if root is None:  # 空节点是递归出口
                return  # 直接返回，不参与比较
            dfs(root.left)  # 先递归左子树，保证按升序访问节点
            nonlocal pre, ans  # 声明要修改外层函数里的 pre 和 ans，而不是新建局部变量
            ans = min(ans, root.val - pre)  # 当前值减前驱值就是中序相邻差，取最小
            pre = root.val  # 当前值成为下一个节点的前驱
            dfs(root.right)  # 最后递归右子树

        pre = -inf  # 前驱初值取负无穷，保证第一次做差得到极大值、不干扰答案
        ans = inf  # 答案初值取正无穷，等待被更小的差覆盖
        dfs(root)  # 从根开始遍历整棵树
        return ans  # 返回最小绝对差
