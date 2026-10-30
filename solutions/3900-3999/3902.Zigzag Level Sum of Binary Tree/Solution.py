# 3902. 二叉树的 Z 字形层级和 / Zigzag Level Sum of Binary Tree
# 核心思路：BFS 逐层遍历，第 1 层从左到右、第 2 层从右到左交替扫描本层节点，遇到缺少对应方向孩子的节点立即停止并结算本层和。
# 复杂度：时间 O(n)，空间 O(n)。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # 题解类
    def zigzagLevelSum(self, root: TreeNode | None) -> list[int]:  # 返回 Z 字形逐层处理后的各层和
        q = [root]  # 当前层节点，初始为根节点
        ans = []  # 保存每一层的和
        left = True  # 本层方向：True 表示从左到右
        while q:  # 逐层处理
            nq = []  # 下一层节点
            for node in q:  # 按左、右顺序收集本层节点的孩子
                if node.left:  # 有左孩子
                    nq.append(node.left)  # 左孩子加入下一层
                if node.right:  # 有右孩子
                    nq.append(node.right)  # 右孩子加入下一层
            m = len(q)  # 本层节点数
            s = 0  # 本层计入答案的和
            for i in range(m):  # 按方向顺序遍历本层节点
                node = q[i] if left else q[m - i - 1]  # 从左取或从右取
                child = node.left if left else node.right  # 该方向上必需的孩子
                if not child:  # 命中停止条件
                    break  # 立即停止本层处理
                s += node.val  # 累加该节点的值
            ans.append(s)  # 记录本层的和
            left = not left  # 方向翻转
            q = nq  # 进入下一层
        return ans  # 返回各层的和
