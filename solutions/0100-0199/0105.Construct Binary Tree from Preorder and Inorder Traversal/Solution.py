# 题目：105. 从前序与中序遍历序列构造二叉树（Construct Binary Tree from Preorder and Inorder Traversal）
# 思路：前序首元素是根，字典 d 记录每个值在中序中的下标，用根的位置 k 把区间切成左右两段递归建树。
# 时间复杂度：O(n)，建字典与建树各一遍；空间复杂度：O(n)，字典与递归栈的开销。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:  # 前序、中序序列，返回构造出的树根
        def dfs(i: int, j: int, n: int) -> Optional[TreeNode]:  # i 前序起点，j 中序起点，n 本段节点个数
            if n <= 0:  # 区间为空
                return None  # 没有节点，返回空子树
            v = preorder[i]  # 前序区间首元素即为当前子树的根值
            k = d[v]  # 查根在中序序列中的下标，用来切分左右两段
            l = dfs(i + 1, j, k - j)  # 左子树：前序紧跟根开始，中序从 j 开始，长度 k-j
            r = dfs(i + 1 + k - j, k + 1, n - k + j - 1)  # 右子树：前序跳过根的左子树部分，中序从 k+1 开始，长度 n-(k-j)-1
            return TreeNode(v, l, r)  # 用根值和左右子树构造节点返回

        d = {v: i for i, v in enumerate(inorder)}  # 值 → 中序下标 的映射；放在 dfs 之后定义，调用时已可见
        return dfs(0, 0, len(preorder))  # 从整个序列区间开始递归建树
