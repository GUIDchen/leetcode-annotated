# 题目：508. 出现次数最多的子树元素和（Most Frequent Subtree Sum）
# 思路：后序 DFS 求每棵子树的元素和，用 Counter 统计每个和出现的次数并取最大频次，最后筛出频次等于最大值的和。
# 时间复杂度：O(n)，每个节点只访问一次；空间复杂度：O(n)，计数器与递归栈。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def findFrequentTreeSum(self, root: Optional[TreeNode]) -> List[int]:  # root：二叉树根节点；返回出现次数最多的子树元素和
        def dfs(root: Optional[TreeNode]) -> int:  # 内部递归函数：返回以 root 为根的子树元素和
            if root is None:  # 空节点没有元素
                return 0  # 空子树的元素和记为 0
            l, r = dfs(root.left), dfs(root.right)  # 先递归求左右子树的元素和
            s = l + r + root.val  # 子树和 = 左子树和 + 右子树和 + 根节点值
            cnt[s] += 1  # 该和的次数加一（cnt 来自外层作用域）
            return s  # 把子树和返回给父节点

        cnt = Counter()  # 计数器：子树和 → 出现次数（必须先建好，dfs 内部要用）
        dfs(root)  # 从根遍历整棵树，把所有子树和都统计好
        mx = max(cnt.values())  # 出现次数的最大值
        return [k for k, v in cnt.items() if v == mx]  # 筛出所有出现次数等于最大频次的子树和
