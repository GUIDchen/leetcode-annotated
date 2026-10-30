# 题目：250. 统计同值子树（Count Univalue Subtrees）
# 思路：后序遍历，dfs 返回以当前节点为根的子树是否同值，并用外层计数器 ans 累加同值子树个数。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，h 为树高（递归栈深度）。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def countUnivalSubtrees(self, root: Optional[TreeNode]) -> int:  # root：二叉树根节点，返回同值子树的数量
        def dfs(root):  # dfs：判断以 root 为根的子树内所有节点值是否相同
            if root is None:  # 空节点按题面约定视为同值
                return True  # 空树返回真
            l, r = dfs(root.left), dfs(root.right)  # 递归处理左右子树，同时拿到它们是否同值
            if not l or not r:  # 任一子树不同值，当前子树也不可能同值
                return False  # 提前返回假
            a = root.val if root.left is None else root.left.val  # 左孩子存在取左值，否则用当前值占位
            b = root.val if root.right is None else root.right.val  # 右孩子同理取占位值
            if a == b == root.val:  # 左右孩子值与当前值都相同，构成同值子树
                nonlocal ans  # 声明 ans 来自外层函数，只有这样才能修改它
                ans += 1  # 计数加一
                return True  # 向父节点汇报本子树同值
            return False  # 值不相同，不是同值子树

        ans = 0  # 同值子树计数器
        dfs(root)  # 后序遍历整棵树，计数在递归中完成
        return ans  # 返回统计结果
