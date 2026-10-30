# 题目：863. 二叉树中所有距离为 K 的结点（All Nodes Distance K in Binary Tree）
# 思路：先 DFS 记录每个结点的父结点，把二叉树补成无向图；再从 target 出发做深度为 k 的 DFS，收集到达距离 k 的结点。
# 时间复杂度：O(n)，每个结点被访问常数次；空间复杂度：O(n)，父指针表与递归栈。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None


class Solution:  # LeetCode 约定的题解类
    def distanceK(self, root: TreeNode, target: TreeNode, k: int) -> List[int]:  # root：二叉树根；target：起点结点；k：期望距离；返回所有距离为 k 的结点值
        def dfs(root, fa):  # 第一次 DFS：递归填写每个结点的父结点
            if root is None:  # 空结点直接返回，递归出口
                return  # 结束本次递归
            g[root] = fa  # 记录当前结点的父亲；根结点的父亲为 None
            dfs(root.left, root)  # 递归处理左子树
            dfs(root.right, root)  # 递归处理右子树

        def dfs2(root, fa, k):  # 第二次 DFS：从当前结点出发，向下或向上走 k 步
            if root is None:  # 空结点直接返回，递归出口
                return  # 结束本次递归
            if k == 0:  # 已经走到目标距离
                ans.append(root.val)  # 该结点与 target 距离正好为 k，加入答案
                return  # 不再继续深入，避免更远
            for nxt in (root.left, root.right, g[root]):  # 依次枚举左儿子、右儿子、父亲三个方向（树已被补成无向图）
                if nxt != fa:  # 跳过刚来的结点，避免原路返回造成重复访问
                    dfs2(nxt, root, k - 1)  # 距离减一，继续向下一层搜索

        g = {}  # 邻接表：记录每个结点的父结点，让搜索可以沿父边向上走
        dfs(root, None)  # 先建好父指针，把树补成无向图
        ans = []  # 存放答案结点值
        dfs2(target, None, k)  # 从 target 出发搜索与它相距 k 的结点
        return ans  # 返回收集到的答案
