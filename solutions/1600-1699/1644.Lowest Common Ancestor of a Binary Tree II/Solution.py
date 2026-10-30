# 题目：1644. 二叉树的最近公共祖先 II（Lowest Common Ancestor of a Binary Tree II）
# 思路：后序 DFS 返回「子树里是否出现 p 或 q」；左右两支各含一个，或当前节点本身是 p/q 而另一支含另一个，该节点即为答案。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，递归栈深度为树高 h。
# Definition for a binary tree node.  # 节点类由判题器提供，下面几行只是题面里的定义说明
# class TreeNode:  # 节点类名
#     def __init__(self, x):  # 构造函数，x 为节点值
#         self.val = x  # 节点值
#         self.left = None  # 左子节点
#         self.right = None  # 右子节点


class Solution:  # LeetCode 约定的题解类
    def lowestCommonAncestor(  # root：二叉树根；p、q：两个目标节点，返回它们的最近公共祖先
        self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode'  # 形参列表（因为太长而换行书写）
    ) -> 'TreeNode':  # 返回值为最近公共祖先节点
        def dfs(root, p, q):  # dfs(root, p, q)：返回以 root 为根的子树中是否出现过 p 或 q
            if root is None:  # 空节点不含任何目标节点
                return False  # 返回 False
            l = dfs(root.left, p, q)  # 递归左子树，得到左子树中是否出现 p 或 q
            r = dfs(root.right, p, q)  # 递归右子树，得到右子树中是否出现 p 或 q
            nonlocal ans  # 声明 ans 来自外层函数，允许在 dfs 内部改写
            if l and r:  # 左右子树各含一个目标节点，当前节点即最近公共祖先
                ans = root  # 记录答案
            if (l or r) and (root.val == p.val or root.val == q.val):  # 当前节点本身是 p 或 q，且另一支里出现了另一个目标节点
                ans = root  # 记录答案
            return l or r or root.val == p.val or root.val == q.val  # 三处任意一处出现 p/q 就向上返回 True

        ans = None  # ans 初值为 None，表示还没找到
        dfs(root, p, q)  # 启动后序遍历，答案写入 ans
        return ans  # 返回最近公共祖先（可能为 None）
