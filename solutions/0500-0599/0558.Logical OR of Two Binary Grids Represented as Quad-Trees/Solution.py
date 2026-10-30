# 题目：558. 四叉树交集（Logical OR of Two Binary Grids Represented as Quad-Trees）
# 核心思路：递归做逻辑或；两个叶子按 or 合并，一方是 1 的叶子可直接短路，四个孩子同值叶子时压缩成一个叶子。
# 时间复杂度：O(n)，只访问必要的节点；空间复杂度：O(h)，递归深度为树高。
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


class Solution:  # LeetCode 约定的题解类
    def intersect(self, quadTree1: "Node", quadTree2: "Node") -> "Node":  # 两棵四叉树的根，返回按位或之后的四叉树
        def dfs(t1, t2):  # 内部递归函数：合并 t1 与 t2 两棵子树
            if t1.isLeaf and t2.isLeaf:  # 两个都是叶子：按位或得到新叶子
                return Node(t1.val or t2.val, True)  # 或运算只要一方为 1 结果就是 1，所以直接构造叶子节点
            if t1.isLeaf:  # 只有 t1 是叶子
                return t1 if t1.val else t2  # t1 值为 1 时整块覆盖，返回 t1；否则结果完全由 t2 决定
            if t2.isLeaf:  # 只有 t2 是叶子
                return t2 if t2.val else t1  # 对称处理：t2 为 1 返回 t2，否则返回 t1
            res = Node()  # 双方都是内部节点，新建一个内部节点承载合并结果
            res.topLeft = dfs(t1.topLeft, t2.topLeft)  # 递归合并左上子区域
            res.topRight = dfs(t1.topRight, t2.topRight)  # 递归合并右上子区域
            res.bottomLeft = dfs(t1.bottomLeft, t2.bottomLeft)  # 递归合并左下子区域
            res.bottomRight = dfs(t1.bottomRight, t2.bottomRight)  # 递归合并右下子区域
            isLeaf = (
                res.topLeft.isLeaf  # 左上孩子是否为叶子
                and res.topRight.isLeaf  # 右上孩子是否为叶子，需四个都为叶子
                and res.bottomLeft.isLeaf  # 左下孩子是否为叶子
                and res.bottomRight.isLeaf  # 右下孩子是否为叶子，括号内整体构成 isLeaf
            )
            sameVal = (  # 比较四个孩子的值是否全部相同
                res.topLeft.val  # 左上孩子的值
                == res.topRight.val  # 与右上孩子的值相等
                == res.bottomLeft.val  # 与左下孩子的值相等
                == res.bottomRight.val  # 与右下孩子的值相等，链式比较整体即 sameVal
            )
            if isLeaf and sameVal:  # 四个孩子都是叶子且值相同：整块同值，可以压平
                res = res.topLeft  # 直接把这个叶子提上来，省掉一层内部节点
            return res  # 返回合并后的子树

        return dfs(quadTree1, quadTree2)  # 从两个根开始递归，返回最终结果
