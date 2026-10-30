# 题目：1612. 检查两棵二叉表达式树是否等价（Check If Two Expression Trees are Equivalent）
# 思路：中序遍历两棵树，用 Counter 统计各操作数的净系数（第一棵 +1、第二棵 -1）；最后所有计数都回到 0 即等价。
# 时间复杂度：O(n)，两棵树各遍历一次；空间复杂度：O(n)，递归栈深度加上不同操作数的个数。
# Definition for a binary tree node.
# class Node(object):
#     def __init__(self, val=" ", left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def checkEquivalence(self, root1: 'Node', root2: 'Node') -> bool:  # root1/root2：两棵表达式树的根节点
        def dfs(root, v):  # 递归中序遍历；v 是这棵树贡献的符号（+1 / -1）
            if root is None:  # 空节点，递归到边界
                return  # 直接返回上一层
            if root.val != '+':  # 非 '+' 说明当前是叶子操作数
                cnt[root.val] += v  # 按符号累加该操作数的净系数
            dfs(root.left, v)  # 递归处理左子树，符号不变
            dfs(root.right, v)  # 递归处理右子树，符号不变

        cnt = Counter()  # 计数容器：键是操作数字符，值是净系数；放在 dfs 之前定义，闭包调用时按名字取到它
        dfs(root1, 1)  # 第一棵树整体记 +1
        dfs(root2, -1)  # 第二棵树整体记 -1
        return all(x == 0 for x in cnt.values())  # 所有净系数都为 0 才说明两式等价
