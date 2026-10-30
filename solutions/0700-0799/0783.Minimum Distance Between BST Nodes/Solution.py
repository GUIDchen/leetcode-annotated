# 题目：783. 二叉搜索树节点最小距离（Minimum Distance Between BST Nodes）
# 思路：BST 的中序遍历是严格递增序列，最小差值必然出现在中序序列的相邻两节点之间；递归时用 pre 保存前驱值，随时更新答案。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度为树高，最坏 O(n)。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类（上方注释是题目给出的 TreeNode 定义）
    def minDiffInBST(self, root: Optional[TreeNode]) -> int:  # root：BST 根节点；返回任意两个不同节点值的最小差值
        def dfs(root: Optional[TreeNode]):  # 嵌套函数 dfs：中序遍历，按值从小到大访问节点
            if root is None:  # 空节点直接返回，作为递归出口
                return  # 结束本层递归
            dfs(root.left)  # 先遍历左子树，保证访问顺序递增
            nonlocal pre, ans  # 声明下面要修改外层作用域的 pre 与 ans（不是重新绑定）
            ans = min(ans, root.val - pre)  # 当前值与前驱值相邻，用它们的差更新最小距离
            pre = root.val  # 当前节点值成为下一轮的前驱
            dfs(root.right)  # 再遍历右子树

        pre = -inf  # pre：中序前驱节点的值，初值 -inf 让第一次做差得到极大值，不影响答案
        ans = inf  # ans：最小差值，初值取正无穷
        dfs(root)  # 从根节点开始中序遍历
        return ans  # 返回最小差值
