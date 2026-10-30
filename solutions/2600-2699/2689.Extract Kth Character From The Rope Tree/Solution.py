# 题目：2689. 从 Rope 树中提取第 K 个字符（Extract Kth Character From The Rope Tree）
# 核心思路：递归遍历 Rope 树，按「左子树 + 右子树」的顺序把字符拼成一整串，再取下标 k-1 的字符。
# 时间复杂度：O(n)，n 为字符串总长，每个结点访问一次（拼接为 O(n^2) 量级拷贝）；空间复杂度：O(n)，递归栈与结果字符串。
# Definition for a rope tree node.
# class RopeTreeNode(object):
#     def __init__(self, len=0, val="", left=None, right=None):
#         self.len = len
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def getKthCharacter(self, root: Optional[object], k: int) -> str:  # root：Rope 树根结点；k：从 1 开始计数的第 k 个字符
        def dfs(root):  # 局部递归函数 dfs：返回以 root 为根的子树按顺序拼出的字符串
            if root is None:  # 空结点不贡献任何字符
                return ""  # 空串是字符串拼接的单位元，不影响最终结果
            if root.len == 0:  # len 为 0 说明是叶子结点，val 才是真正的字符串内容
                return root.val  # 叶子结点直接给出自己保存的字符串
            return dfs(root.left) + dfs(root.right)  # 内部结点：左子树的字符整体在前，右子树在后

        return dfs(root)[k - 1]  # 把 1 基的 k 转成 0 基下标，取出目标字符；题目保证 k 不越界
