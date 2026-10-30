# 题目：988. 从叶结点开始的最小字符串（Smallest String Starting From Leaf）
# 思路：从根 DFS，路径记录根到当前结点的字母；到叶子时反转成叶→根字符串，取字典序最小。
# 时间复杂度：O(n^2)，n 为结点数，每条根到叶路径的反转与比较都需 O(n)；空间复杂度：O(n)，递归栈与路径列表。
# 下面 6 行是题目给出的二叉树结点定义，实际判题时由 LeetCode 提供。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def smallestFromLeaf(self, root: TreeNode) -> str:  # 入口：root 是二叉树根结点；返回从叶到根拼接出的最小字符串
        ans = chr(ord('z') + 1)  # ans 初值取比 'z' 还大的字符，方便后面用 min 统一比较、无需特判

        def dfs(root, path):  # 内部递归函数：path 是从根到当前结点的字母列表，按引用就地修改
            nonlocal ans  # 声明 ans 来自外层函数，才能在内层函数里给它重新赋值
            if root:  # 空结点直接跳过，避免访问 None 的属性
                path.append(chr(ord('a') + root.val))  # 把结点值 0..25 映射成 'a'..'z' 并追加到路径末尾
                if root.left is None and root.right is None:  # 叶子判断：左右孩子都为空，此时 path 是一条完整的根到叶路径
                    ans = min(ans, ''.join(reversed(path)))  # 反转路径得到「从叶到根」的字符串，与当前答案取字典序更小者
                dfs(root.left, path)  # 继续深入左子树
                dfs(root.right, path)  # 继续深入右子树
                path.pop()  # 回溯：撤销本层追加的字母，恢复路径

        dfs(root, [])  # 从根开始搜索，初始路径为空列表
        return ans  # 返回搜索得到的最小字符串
