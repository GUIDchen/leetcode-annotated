# 题目：1026. 节点与其祖先之间的最大差值（Maximum Difference Between Node and Ancestor）
# 思路：DFS 向下传递「根到父节点路径上的最小值 mi 与最大值 mx」，在当前节点用 mi、mx 与自身作差来更新答案。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，h 为树高，来自递归调用栈。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
# 上面的 TreeNode 定义由 LeetCode 判题器注入，代码中直接使用
class Solution:  # LeetCode 约定的题解类
    def maxAncestorDiff(self, root: Optional[TreeNode]) -> int:  # root 是二叉树根；返回祖先与后代节点值之差绝对值的最大值
        def dfs(root: Optional[TreeNode], mi: int, mx: int):  # 内部递归：root 为当前节点，mi/mx 是从根到父节点路径上的最小值和最大值
            if root is None:  # 空节点直接返回，没有可以比较的一对节点
                return  # 结束这条分支
            nonlocal ans  # 声明使用外层函数的 ans，下面的赋值才会修改真正的答案变量
            ans = max(ans, abs(mi - root.val), abs(mx - root.val))  # 用当前节点与路径上最小值、最大值分别作差，三者取最大
            mi = min(mi, root.val)  # 把当前节点并入路径最小值，传给子节点
            mx = max(mx, root.val)  # 把当前节点并入路径最大值，传给子节点
            dfs(root.left, mi, mx)  # 递归左子树，继续带着更新后的 mi、mx
            dfs(root.right, mi, mx)  # 递归右子树，同理

        # 根节点没有祖先，mi 与 mx 都初始化为根的值
        ans = 0  # 答案初始为 0
        dfs(root, root.val, root.val)  # 从根节点启动 DFS，上下界都是根的值
        return ans  # 返回最大差值
