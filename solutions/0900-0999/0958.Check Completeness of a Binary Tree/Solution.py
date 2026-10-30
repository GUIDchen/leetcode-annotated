# 题目：958. 二叉树的完全性检验（Check Completeness of a Binary Tree）
# 思路：层序遍历，空儿子也入队；遇到第一个空节点就停止扩展，最后要求队列里剩下的全是空节点。
# 时间复杂度：O(n)，每个节点最多入队一次；空间复杂度：O(n)，队列最坏保存一层节点。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def isCompleteTree(self, root: TreeNode) -> bool:  # root：二叉树根节点，返回这棵树是否为完全二叉树
        q = deque([root])  # 层序遍历队列，初始只有根节点
        while q:  # 队列不空就继续取节点
            node = q.popleft()  # 取出队首节点
            if node is None:  # 第一次遇到空节点就说明出现缺口
                break  # 停止扩展，剩下的队列交给最后一行统一检查
            q.append(node.left)  # 左儿子入队，空儿子也要入队以占位
            q.append(node.right)  # 右儿子入队，同样允许为空
        return all(node is None for node in q)  # 缺口之后必须全是空节点：是则完全二叉树，否则不是
