# 题目：979. 在二叉树中分配硬币（Distribute Coins in Binary Tree）
# 思路：后序遍历返回子树需要向外「净输出」的硬币数，每个子树的盈余绝对值之和就是必须经过这条边的移动次数。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(n)，递归栈深度。
# 题目给出的二叉树节点定义（题面已给出，无需再 import）
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def distributeCoins(self, root: Optional[TreeNode]) -> int:  # root：二叉树根节点，返回让每个节点恰好有 1 枚硬币所需的最少移动次数
        def dfs(root):  # 内层后序递归：返回该子树需要净输出/净输入的硬币数
            if root is None:  # 空节点没有硬币可搬
                return 0  # 空节点贡献 0
            left, right = dfs(root.left), dfs(root.right)  # 先递归左右子树，拿到它们各自需要净输出/净输入的硬币数
            nonlocal ans  # 声明 ans 来自外层作用域，这里要修改它
            ans += abs(left) + abs(right)  # 左右子树与当前节点之间的硬币都要经过这两条边，绝对值之和就是移动次数
            return left + right + root.val - 1  # 本子树净输出量 = 左 + 右 + 自身硬币数 - 自己保留的 1 枚

        ans = 0  # ans 累计所有边上发生的移动次数
        dfs(root)  # 从根开始后序遍历，过程即完成全部统计
        return ans  # 返回最少移动次数
