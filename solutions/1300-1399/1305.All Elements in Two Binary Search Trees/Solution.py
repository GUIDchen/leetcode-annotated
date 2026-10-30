# 题目：1305. 两棵二叉搜索树中的所有元素（All Elements in Two Binary Search Trees）
# 核心思路：对两棵 BST 分别做中序遍历得到两个升序列表，再用双指针归并成一个升序列表。
# 时间复杂度：O(m + n)，m、n 为两棵树的节点数；空间复杂度：O(m + n)，用于两个中序列表和答案。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def getAllElements(  # 入口方法：返回两棵树所有元素的升序列表
        self, root1: Optional[TreeNode], root2: Optional[TreeNode]  # root1、root2 是两棵 BST 的根
    ) -> List[int]:  # 返回值是整数升序列表
        def dfs(root: Optional[TreeNode], nums: List[int]) -> int:  # 中序遍历辅助函数：左 → 根 → 右
            if root is None:  # 空节点没有元素可收集
                return  # 直接回溯上一层
            dfs(root.left, nums)  # 先递归左子树，让较小值先进入列表
            nums.append(root.val)  # 再访问根节点，把当前值追加到 nums
            dfs(root.right, nums)  # 最后递归右子树

        a, b = [], []  # a、b 分别收集两棵树的中序结果
        dfs(root1, a)  # 遍历第一棵树，结果天然升序
        dfs(root2, b)  # 遍历第二棵树，结果天然升序
        m, n = len(a), len(b)  # 两个列表的长度，供双指针使用
        i = j = 0  # i、j 分别是 a、b 的读指针
        ans = []  # 存放归并结果
        while i < m and j < n:  # 两边都还有元素时逐对比较
            if a[i] <= b[j]:  # 取较小的一方放入答案
                ans.append(a[i])  # 追加 a[i]
                i += 1  # 指针后移
            else:  # b[j] 更小
                ans.append(b[j])  # 追加 b[j]
                j += 1  # 指针后移
        while i < m:  # a 中剩余元素全部追加
            ans.append(a[i])  # 追加当前元素
            i += 1  # 指针后移
        while j < n:  # b 中剩余元素全部追加
            ans.append(b[j])  # 追加当前元素
            j += 1  # 指针后移
        return ans  # 返回升序合并后的所有元素
