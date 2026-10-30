# 题目：366. 寻找二叉树的叶子节点（Find Leaves of Binary Tree）
# 思路：后序 DFS 求每个结点的高度（叶子高度为 0），把同高度的结点值追加到 ans[高度]，得到自底向上的分层叶子。
# 时间复杂度：O(n)，每个结点只访问一次；空间复杂度：O(n)，递归栈深度与结果数组。
# 下列注释是 LeetCode 题面自带的二叉树结点定义，原样保留
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def findLeaves(self, root: Optional[TreeNode]) -> List[List[int]]:  # root 是二叉树根结点，返回自底向上的逐层叶子值列表
        def dfs(root: Optional[TreeNode]) -> int:  # 递归函数 dfs 返回以 root 为根的子树高度
            if root is None:  # 空结点高度为 0，是递归的终止条件
                return 0  # 空子树贡献高度 0
            l, r = dfs(root.left), dfs(root.right)  # 同时递归求左右子树高度
            h = max(l, r)  # 当前结点高度取左右子树较高者，叶子因此得到 h = 0
            if len(ans) == h:  # 第一次出现该高度，说明这一层还没有对应的列表
                ans.append([])  # 为新的一层创建空列表
            ans[h].append(root.val)  # 把当前结点值放到对应高度层，叶子最先、根最后
            return h + 1  # 返回给父结点的高度是 h + 1

        ans = []  # 结果容器，dfs 内部会闭包引用它，必须先于调用准备
        dfs(root)  # 触发后序遍历，填充 ans
        return ans  # 返回自底向上的分层叶子
