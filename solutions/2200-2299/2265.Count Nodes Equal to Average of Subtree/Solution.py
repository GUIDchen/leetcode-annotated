# 题目：2265. 统计值等于子树平均值的节点数（Count Nodes Equal to Average of Subtree）
# 思路：后序 DFS 返回每棵子树的 (节点值之和, 节点个数)，用整除求平均值与当前节点值比较，相等则让外层答案累加 1。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(h)，递归栈深度为树高 h（最坏情况 O(n)）。
class Solution:  # LeetCode 约定的题解类
    def averageOfSubtree(self, root: TreeNode) -> int:  # root：二叉树根节点
        def dfs(root) -> tuple:  # 递归函数：返回本子树的 (节点值之和, 节点个数)
            if not root:  # 空节点：递归出口
                return 0, 0  # 空子树的贡献为 (0, 0)
            ls, ln = dfs(root.left)  # 递归求左子树的 (和, 节点数) 并解包
            rs, rn = dfs(root.right)  # 递归求右子树的 (和, 节点数) 并解包
            s = ls + rs + root.val  # 以当前节点为根的子树全部节点值之和
            n = ln + rn + 1  # 该子树的节点总数（左右子树节点数 + 当前节点）
            nonlocal ans  # 声明 ans 来自外层函数，内层才能修改它
            ans += int(s // n == root.val)  # 整除求平均值，相等时布尔值转成 1 累加，否则加 0
            return s, n  # 把本子树的 (和, 节点数) 返回给父节点复用

        ans = 0  # 统计满足条件的节点个数，初始为 0
        dfs(root)  # 从根节点开始遍历整棵树
        return ans  # 返回满足条件的节点总数
