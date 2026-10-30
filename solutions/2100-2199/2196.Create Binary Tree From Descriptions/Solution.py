# 题目：2196. 根据描述创建二叉树（Create Binary Tree From Descriptions）
# 思路：字典把结点值映射到结点对象，按描述逐条连接父子并记录所有“孩子”；值从未当过孩子的结点就是根。
# 时间复杂度：O(n)，每条描述只做常数次字典操作；空间复杂度：O(n)，字典最多保存 2n 个结点。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def createBinaryTree(self, descriptions: List[List[int]]) -> Optional[TreeNode]:  # descriptions：每条形如 [父结点值, 子结点值, 是否为左孩子]
        nodes = defaultdict(TreeNode)  # 值到结点的映射（默认工厂只是占位，真正创建结点都走显式赋值）
        children = set()  # 记录所有当过孩子（即一定不是根）的结点值，用于最后找根
        for parent, child, isLeft in descriptions:  # 逐条处理描述
            if parent not in nodes:  # 父结点还没有创建过
                nodes[parent] = TreeNode(parent)  # 新建父结点并登记
            if child not in nodes:  # 子结点还没有创建过
                nodes[child] = TreeNode(child)  # 新建子结点并登记
            children.add(child)  # 孩子结点一定不是根，记录下来
            if isLeft:  # isLeft 为真表示是左孩子
                nodes[parent].left = nodes[child]  # 挂到父结点的左侧
            else:  # 否则是右孩子
                nodes[parent].right = nodes[child]  # 挂到父结点的右侧
        root = (set(nodes.keys()) - children).pop()  # 全集减去孩子集合，剩下的唯一一个结点就是根
        return nodes[root]  # 按根的值取出根结点返回
