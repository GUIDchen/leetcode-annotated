# 题目：951. 翻转等价二叉树（Flip Equivalent Binary Trees）
# 思路：递归同时比较两棵树；根值相同时，比较「不交换」或「交换」两种左右子树配对，任一成立即翻转等价。
# 时间复杂度：O(n)，每个节点至多配对常数次；空间复杂度：O(h)，h 为树高，即递归栈深度。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def flipEquiv(self, root1: Optional[TreeNode], root2: Optional[TreeNode]) -> bool:  # root1、root2：待比较的两棵树的根节点
        def dfs(root1, root2):  # 内部递归函数：判断两棵子树是否翻转等价
            if root1 == root2 or (root1 is None and root2 is None):  # 同一对象或同时为 None，直接等价（递归终止条件）
                return True  # 返回真，表示这两棵子树等价
            if root1 is None or root2 is None or root1.val != root2.val:  # 只有一方为空，或根值不同，必然不等价
                return False  # 返回假，表示这两棵子树不等价
            return (dfs(root1.left, root2.left) and dfs(root1.right, root2.right)) or (  # 先尝试「左右子树不交换」的配对（括号内换行是隐式续行）
                dfs(root1.left, root2.right) and dfs(root1.right, root2.left)  # 再尝试「左右子树交换」的配对；两种配对任一成立即可
            )  # 结束多行表达式，与第 14 行构成一个完整条件

        return dfs(root1, root2)  # 从两个根开始递归判定
