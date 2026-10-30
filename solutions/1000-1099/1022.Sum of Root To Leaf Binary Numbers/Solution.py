# 题目：1022. 从根到叶的二进制数之和（Sum of Root To Leaf Binary Numbers）
# 思路：DFS 时用参数 x 累积「从根到当前节点」的二进制值（左移一位再或上当前位），走到叶子就把 x 返回并逐层累加。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，h 为树高，来自递归调用栈。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
# 上面的 TreeNode 定义由 LeetCode 判题器注入，代码中直接使用
class Solution:  # LeetCode 约定的题解类
    def sumRootToLeaf(self, root: Optional[TreeNode]) -> int:  # root 是 01 二叉树的根；返回所有根到叶路径所表示二进制数之和
        def dfs(root: Optional[TreeNode], x: int) -> int:  # 内部递归：root 为当前节点，x 为从根到父节点已累积的数值
            if root is None:  # 空节点不形成路径，剪枝
                return 0  # 返回 0，不影响父节点的求和
            x = x << 1 | root.val  # 左移一位腾出最低位，再按位或填入当前节点的二进制位
            if root.left == root.right:  # 左右孩子都为 None，说明当前节点是叶子
                return x  # 到达叶子，这条路径代表的数就是 x
            return dfs(root.left, x) + dfs(root.right, x)  # 非叶子：递归求左右子树的路径和再相加

        # 从根节点、累积值 0 开始搜索
        return dfs(root, 0)  # 返回总的路径数值和
