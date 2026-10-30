# 题目：1530. 好叶子节点对的数量（Number of Good Leaf Nodes Pairs）
# 思路：递归每个结点作为汇合点，用计数器记下左右子树中「距离 → 叶子数」，再按 k1+k2<=distance 累加配对数量。
# 时间复杂度：O(n·distance²)，逐层合并距离表；空间复杂度：O(n)，递归深度与计数器开销。
# Definition for a binary tree node.  # 下面几行是题面给出的 TreeNode 定义，判题器提供，无需自己实现
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def countPairs(self, root: TreeNode, distance: int) -> int:  # root：二叉树根；distance：叶子对之间允许的最大距离
        def dfs(root, cnt, i):  # 内部辅助函数：从 root 出发收集所有叶子，按距离 i 计数进 cnt
            if root is None or i >= distance:  # 空结点，或距离已达上限（再远配不上），直接剪枝
                return  # 剪枝后返回
            if root.left is None and root.right is None:  # 左右孩子都为空，说明当前结点就是叶子
                cnt[i] += 1  # 距离为 i 的叶子数量加一
                return  # 叶子没有孩子，本次递归结束
            dfs(root.left, cnt, i + 1)  # 向左子树递归，距离加一
            dfs(root.right, cnt, i + 1)  # 向右子树递归，距离加一

        if root is None:  # 空树没有叶子，也就没有叶子对
            return 0  # 直接返回 0
        ans = self.countPairs(root.left, distance) + self.countPairs(  # 先递归求左右子树内部各自的好叶子对（这一行跨了两行括号）
            root.right, distance
        )
        cnt1 = Counter()  # cnt1：左子树中「到 root 的距离 → 叶子个数」
        cnt2 = Counter()  # cnt2：右子树中「到 root 的距离 → 叶子个数」
        dfs(root.left, cnt1, 1)  # 收集左子树里的叶子，root 到左孩子的距离记为 1
        dfs(root.right, cnt2, 1)  # 收集右子树里的叶子，距离同样从 1 起算

        for k1, v1 in cnt1.items():  # 枚举左子树中距离为 k1 的 v1 个叶子
            for k2, v2 in cnt2.items():  # 枚举右子树中距离为 k2 的 v2 个叶子
                if k1 + k2 <= distance:  # 这对叶子路径经过 root，长度 k1+k2 不超过 distance 才是好叶子对
                    ans += v1 * v2  # 两层叶子可以任意两两配对，组合数为 v1*v2
        return ans  # 返回好叶子对的总数
