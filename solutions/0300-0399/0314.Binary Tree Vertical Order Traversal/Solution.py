# 题目：314. 二叉树的垂直遍历（Binary Tree Vertical Order Traversal）
# 思路：DFS 记录每个节点的列偏移与深度，按列分组后同列按深度升序输出，保证自上而下。
# 时间复杂度：O(n log n)，主要是每列内部排序；空间复杂度：O(n)，保存全部节点信息。
# 下面这 5 行是题目给出的二叉树节点定义（判题器已提供，这里只是注释）
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def verticalOrder(self, root: Optional[TreeNode]) -> List[List[int]]:  # root：二叉树根节点
        def dfs(root, depth, offset):  # depth：深度（行号）；offset：列偏移，根节点为 0
            if root is None:  # 空节点直接返回
                return  # 结束本次递归
            d[offset].append((depth, root.val))  # 记录「列偏移 → (深度, 节点值)」
            dfs(root.left, depth + 1, offset - 1)  # 左孩子：深度加一，列偏移减一
            dfs(root.right, depth + 1, offset + 1)  # 右孩子：深度加一，列偏移加一

        d = defaultdict(list)  # 列偏移 → [(深度, 节点值)] 的字典，缺省值为空列表
        dfs(root, 0, 0)  # 先序遍历，根节点位于列 0、深度 0
        ans = []  # 按列从左到右存放结果
        for _, v in sorted(d.items()):  # 按列偏移升序遍历每一列，_ 是占位的列偏移
            v.sort(key=lambda x: x[0])  # 同一列内按深度升序排序，保证同列节点自上而下
            ans.append([x[1] for x in v])  # 取出该列所有节点值，组成结果的一行
        return ans  # 返回按列分组、自上而下的遍历结果
