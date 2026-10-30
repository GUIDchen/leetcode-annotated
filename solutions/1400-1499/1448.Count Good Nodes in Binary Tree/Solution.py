# 题目：1448. 统计二叉树中好节点的数目（Count Good Nodes in Binary Tree）
# 核心思路：DFS 向下传递「从根到当前节点路径上的最大值 mx」，节点值不小于 mx 即为好节点，再带上新的最大值继续递归。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，h 为树高（递归栈深度）。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def goodNodes(self, root: TreeNode) -> int:  # 返回二叉树中好节点的个数
        def dfs(root: TreeNode, mx: int):  # 内部 DFS：mx 是根到当前节点路径上的最大值
            if root is None:  # 空节点直接返回，作为递归的终止条件
                return  # 不做任何事，直接回溯
            nonlocal ans  # 声明 ans 来自外层函数，否则内部赋值会新建局部变量
            if mx <= root.val:  # 当前节点值不小于路径最大值，说明它是好节点
                ans += 1  # 好节点计数加一
                mx = root.val  # 更新路径最大值，供子树使用
            dfs(root.left, mx)  # 递归处理左子树，带上更新后的路径最大值
            dfs(root.right, mx)  # 递归处理右子树，带上更新后的路径最大值

        ans = 0  # 计数器，记录好节点的数量
        dfs(root, -1000000)  # 从根开始遍历，根到根的路径最大值取足够小的初值 -1000000
        return ans  # 返回好节点总数
