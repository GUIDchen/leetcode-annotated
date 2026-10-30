# 题目：889. 从前序与后序遍历序列构造二叉树（Construct Binary Tree from Preorder and Postorder Traversal）
# 思路：前序首元素是根，前序第二个元素必为左子树根；用后序下标表定位它，算出左子树大小，再递归切分两个区间。
# 时间复杂度：O(n)，建表与建树各线性；空间复杂度：O(n)，下标表与递归栈。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def constructFromPrePost(  # 由前序与后序序列还原二叉树，返回根结点
        self, preorder: List[int], postorder: List[int]  # 形参：两个遍历序列
    ) -> Optional[TreeNode]:  # preorder 为前序序列，postorder 为后序序列，返回值是根结点
        def dfs(a: int, b: int, c: int, d: int) -> Optional[TreeNode]:  # dfs(a,b,c,d)：处理 preorder[a..b] 与 postorder[c..d] 两段区间
            if a > b:  # 区间为空，说明没有结点
                return None  # 空区间对应空子树
            root = TreeNode(preorder[a])  # 前序区间首元素就是当前子树的根
            if a == b:  # 只剩一个结点，是叶子
                return root  # 叶子没有左右子树，直接返回
            i = pos[preorder[a + 1]]  # 前序第二个元素是左子树根，它的后序位置 i 分隔左右子树
            m = i - c + 1  # 左子树结点个数 = i - c + 1
            root.left = dfs(a + 1, a + m, c, i)  # 递归构造左子树：前序 a+1..a+m，后序 c..i
            root.right = dfs(a + m + 1, b, i + 1, d - 1)  # 递归构造右子树：前序 a+m+1..b，后序 i+1..d-1（要去掉末尾的根）
            return root  # 返回当前子树的根

        pos = {x: i for i, x in enumerate(postorder)}  # 后序「值 → 下标」的映射，用来快速求左子树规模
        return dfs(0, len(preorder) - 1, 0, len(postorder) - 1)  # 两个区间都取满整个序列，构造整棵树
