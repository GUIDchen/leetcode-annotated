# 题目：1522. N 叉树的直径（Diameter of N-Ary Tree）🔒
# 核心思路：DFS 返回以当前节点为顶端向下延伸的最长链；在每个节点处用「最长链 + 次长链」更新直径，用 nonlocal 修改外层 ans。
# 时间复杂度：O(n)，每个节点访问一次；空间复杂度：O(h)，h 为树高（递归栈）。
"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children if children is not None else []
"""


class Solution:  # LeetCode 约定的题解类
    def diameter(self, root: 'Node') -> int:  # root：N 叉树根节点，返回树的直径（最长路径的边数）
        """
        :type root: 'Node'
        :rtype: int
        """

        def dfs(root):  # 内部 DFS：返回以 root 为顶端向下延伸的最长链长度
            if root is None:  # 空节点
                return 0  # 没有链，返回 0
            nonlocal ans  # 声明 ans 来自外层函数作用域，内层才能给它赋值
            m1 = m2 = 0  # m1、m2 分别是当前节点的最长、次长孩子链（初始都是 0）
            for child in root.children:  # 遍历所有孩子
                t = dfs(child)  # 递归求出该孩子向下的最长链
                if t > m1:  # 比最长还长
                    m2, m1 = m1, t  # 交换：旧最长变次长，新值变最长
                elif t > m2:  # 否则若比次长更长
                    m2 = t  # 刷新次长
            ans = max(ans, m1 + m2)  # 经过当前节点的最长路径是两条最长链之和，用它更新直径
            return 1 + m1  # 向上返回当前节点向下的最长链（算上自己这条边）

        ans = 0  # 直径初值为 0
        dfs(root)  # 从根开始 DFS，过程中更新 ans
        return ans  # 返回直径
