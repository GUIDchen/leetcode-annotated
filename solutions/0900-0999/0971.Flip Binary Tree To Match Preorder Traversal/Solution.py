# 题目：971. 翻转二叉树以匹配先序遍历（Flip Binary Tree To Match Preorder Traversal）
# 思路：按 voyage 的顺序做先序 DFS，若左孩子不等于 voyage 的下一个值，就先递归右子树再递归左子树，并记录该节点值。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(n)，递归栈深度与答案数组。
# 题目给出的二叉树节点定义（题面已给出，无需再 import）
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def flipMatchVoyage(self, root: Optional[TreeNode], voyage: List[int]) -> List[int]:  # root：待翻转的二叉树根节点；voyage：期望的先序遍历序列
        def dfs(root):  # 内层递归函数：按先序依次消费 voyage 中的元素
            nonlocal i, ok  # 声明 i 与 ok 来自外层作用域，这里要修改它们的值
            if root is None or not ok:  # 空节点，或前面已经失配，就没有继续比对的必要
                return  # 直接返回，不做任何处理
            if root.val != voyage[i]:  # 当前节点的值必须等于 voyage[i]，否则该遍历方式不可行
                ok = False  # 失配，标记整体失败
                return  # 直接返回，后续节点不再比对
            i += 1  # 当前节点匹配成功，消耗掉 voyage 中的一个位置
            if root.left is None or root.left.val == voyage[i]:  # 左孩子为空，或左孩子恰好是 voyage 的下一个值：说明不用翻转
                dfs(root.left)  # 按原顺序先递归左子树
                dfs(root.right)  # 再递归右子树
            else:  # 否则需要翻转：先右后左
                ans.append(root.val)  # 记录被翻转的节点值（题目要求输出这些值）
                dfs(root.right)  # 先访问右子树
                dfs(root.left)  # 再访问左子树

        ans = []  # ans 记录需要翻转的节点值
        i = 0  # i 是 voyage 中下一个待比对元素的下标
        ok = True  # ok 标记当前遍历方式是否仍与 voyage 完全一致
        dfs(root)  # 从根节点开始遍历
        return ans if ok else [-1]  # 全部匹配返回 ans，否则按题目约定返回 [-1]
