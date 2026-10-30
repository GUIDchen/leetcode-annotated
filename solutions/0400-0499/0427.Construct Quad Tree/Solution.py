# 题目：427. 建立四叉树（Construct Quad Tree）
# 思路：递归处理子矩阵，先扫描判断该区域是否只含一种值：是则返回叶子节点，否则四等分后递归构造四个子节点再合并。
# 时间复杂度：O(n^2 log n)，每层扫描 O(n^2) 共 log n 层；空间复杂度：O(log n)，递归栈深度。
# 说明：下面是题目自带的 QuadTree Node 定义（注释块，由判题器提供），仅作参考。
"""
# Definition for a QuadTree node.
class Node:
    def __init__(self, val, isLeaf, topLeft, topRight, bottomLeft, bottomRight):
        self.val = val
        self.isLeaf = isLeaf
        self.topLeft = topLeft
        self.topRight = topRight
        self.bottomLeft = bottomLeft
        self.bottomRight = bottomRight
"""


class Solution:  # LeetCode 题解类
    def construct(self, grid: List[List[int]]) -> 'Node':  # grid：由 0/1 组成的 n x n 方阵，返回四叉树的根节点
        def dfs(a, b, c, d):  # 处理行区间 [a, c]、列区间 [b, d] 这块子矩阵
            zero = one = 0  # 标记这块区域里是否出现过 0 和 1
            for i in range(a, c + 1):  # 枚举行
                for j in range(b, d + 1):  # 枚举列
                    if grid[i][j] == 0:  # 当前格子是 0
                        zero = 1  # 记录出现过 0
                    else:  # 当前格子是 1
                        one = 1  # 记录出现过 1
            isLeaf = zero + one == 1  # 只出现过一种值，说明区域同色，可以作为叶子
            val = isLeaf and one  # 叶子的值：全为 1 取 True，全为 0 取 False
            if isLeaf:  # 叶子节点无需继续分裂
                return Node(grid[a][b], True)  # 用区域内任意一格的值建叶子节点
            topLeft = dfs(a, b, (a + c) // 2, (b + d) // 2)  # 左上子块：行 [a, mid]、列 [b, mid]
            topRight = dfs(a, (b + d) // 2 + 1, (a + c) // 2, d)  # 右上子块：行 [a, mid]、列 [mid+1, d]
            bottomLeft = dfs((a + c) // 2 + 1, b, c, (b + d) // 2)  # 左下子块：行 [mid+1, c]、列 [b, mid]
            bottomRight = dfs((a + c) // 2 + 1, (b + d) // 2 + 1, c, d)  # 右下子块：行 [mid+1, c]、列 [mid+1, d]
            return Node(val, isLeaf, topLeft, topRight, bottomLeft, bottomRight)  # 把四个子节点合并成内部节点返回

        return dfs(0, 0, len(grid) - 1, len(grid[0]) - 1)  # 从整个矩阵开始递归构造
