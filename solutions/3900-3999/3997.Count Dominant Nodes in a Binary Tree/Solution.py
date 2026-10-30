# 3997. 统计二叉树中支配节点的数量 / Count Dominant Nodes in a Binary Tree（中等）
# 核心思路：后序 DFS 让每棵子树返回自身最大值，节点值若等于「左子树最大值、右子树最大值、自身值」三者的最大者，它就是支配节点；空子树用 -inf 表示「没有节点」。
# 复杂度：时间 O(n)，每个节点只访问一次；空间 O(h)，递归栈深度等于树高。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # 题解类
    def countDominantNodes(self, root: TreeNode | None) -> int:  # 返回支配节点的数量
        def dfs(node: TreeNode | None) -> int:  # 后序 DFS：返回以 node 为根的子树中所有节点值的最大值
            if node is None:  # 空节点
                return -inf  # 空子树没有节点，用负无穷充当最大值
            l = dfs(node.left)  # 左子树的最大值
            r = dfs(node.right)  # 右子树的最大值
            mx = max(l, r, node.val)  # 整棵子树的最大值
            if mx == node.val:  # 自身即子树最大值，说明它是支配节点
                nonlocal ans  # 声明这里修改的是外层函数里的计数变量
                ans += 1  # 计数加一
            return mx  # 把子树最大值返回给父节点

        ans = 0  # 支配节点计数器
        dfs(root)  # 从根节点开始遍历
        return ans  # 返回支配节点数量
