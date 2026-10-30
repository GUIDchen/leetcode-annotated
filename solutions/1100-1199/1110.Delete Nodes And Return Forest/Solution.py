# 题目：1110. 删点成林（Delete Nodes And Return Forest）
# 思路：把待删值放进集合，后序 DFS 先修好左右子树；当前节点待删就把它留下的非空孩子收进结果并返回 None，否则原样返回。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(n)，待删集合与递归栈。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def delNodes(  # 主方法：删除指定值后返回新森林的所有树根
        self, root: Optional[TreeNode], to_delete: List[int]  # root 是原树根，to_delete 是要删除的节点值
    ) -> List[TreeNode]:  # 返回值是森林中每棵树的根节点列表
        def dfs(root: Optional[TreeNode]) -> Optional[TreeNode]:  # 递归函数：返回处理后的子树根，节点被删则返回 None
            if root is None:  # 空节点无需处理
                return None  # 直接返回空
            root.left, root.right = dfs(root.left), dfs(root.right)  # 后序遍历：先递归修复左右子树并接回新的孩子
            if root.val not in s:  # 当前节点不在待删集合中
                return root  # 保留它，交回给父节点使用
            if root.left:  # 当前节点待删，但它有非空左孩子
                ans.append(root.left)  # 被断开的左孩子自成新森林的一棵树
            if root.right:  # 非空右孩子同理
                ans.append(root.right)  # 被断开的右孩子也自成新树
            return None  # 当前节点被删除，向父节点报告此处为空

        s = set(to_delete)  # 待删值转成集合，查询只需 O(1)
        ans = []  # 收集新森林里的所有树根
        if dfs(root):  # 从根开始 DFS；若根节点没有被删掉
            ans.append(root)  # 原根也是一棵新树的根，需要加入结果
        return ans  # 返回森林中所有树的根节点
