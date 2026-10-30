# 题目：987. 二叉树的垂序遍历（Vertical Order Traversal of a Binary Tree）
# 思路：DFS 收集每个节点的 (列号, 行号, 值)，排序后按列号分组输出，组内即按行号、值升序。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(n)，保存全部节点信息。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def verticalTraversal(self, root: Optional[TreeNode]) -> List[List[int]]:  # root 是二叉树根节点
        def dfs(root: Optional[TreeNode], i: int, j: int):  # 内层 DFS：i 为行号，j 为列号
            if root is None:  # 空节点直接返回
                return  # 递归出口
            nodes.append((j, i, root.val))  # 记录 (列号, 行号, 节点值)，列号放最前面方便排序
            dfs(root.left, i + 1, j - 1)  # 左子节点：行号 +1，列号 -1
            dfs(root.right, i + 1, j + 1)  # 右子节点：行号 +1，列号 +1

        nodes = []  # 收集节点信息的列表，定义在调用 dfs 之前即可被闭包引用
        dfs(root, 0, 0)  # 从根节点开始，行列坐标均为 0
        nodes.sort()  # 按 (列号, 行号, 值) 升序排序，符合题目优先级
        ans = []  # ans 保存按列分组的结果
        prev = -2000  # 上一组的列号，越界哨兵保证第一组一定新建
        for j, _, val in nodes:  # 按排序顺序遍历，_ 为行号占位符
            if prev != j:  # 列号变化说明进入新的一列
                ans.append([])  # 新建一个空分组
                prev = j  # 更新当前列号
            ans[-1].append(val)  # 把节点值追加到当前列的分组
        return ans  # 返回垂序遍历结果
