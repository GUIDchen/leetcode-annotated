# 题目：1214. 查找两棵二叉搜索树之和（Two Sum BSTs）
# 思路：BST 的中序遍历是升序序列，分别把两棵树展开成有序列表后，用左右双指针判定是否存在和为 target 的一对数。
# 时间复杂度：O(n1 + n2)，遍历两棵树与双指针各线性；空间复杂度：O(n1 + n2)，需要保存两个中序序列。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:  # LeetCode 约定的题解类
    def twoSumBSTs(  # root1、root2：两棵二叉搜索树
        self, root1: Optional[TreeNode], root2: Optional[TreeNode], target: int  # target：目标和；判断是否存在 x + y = target
    ) -> bool:  # 返回布尔结果
        def dfs(root: Optional[TreeNode], i: int):  # 递归中序遍历：i 为 0 表示处理第一棵树、1 表示第二棵（nums 在后面才定义，调用时已存在）
            if root is None:  # 遇到空结点，递归终止
                return  # 直接回溯到上一层
            dfs(root.left, i)  # 先递归左子树，保证「左 → 根 → 右」的中序顺序
            nums[i].append(root.val)  # 访问根结点；BST 的中序序列因此严格升序
            dfs(root.right, i)  # 再递归右子树

        nums = [[], []]  # nums[0]、nums[1] 分别保存两棵树的中序遍历结果（升序）
        dfs(root1, 0)  # 把第一棵树展开成升序列表 nums[0]
        dfs(root2, 1)  # 把第二棵树展开成升序列表 nums[1]
        i, j = 0, len(nums[1]) - 1  # 双指针：i 从左端扫 nums[0]，j 从右端扫 nums[1]
        while i < len(nums[0]) and ~j:  # ~j 等价于 j >= 0，两个指针都未越界就还有候选组合
            x = nums[0][i] + nums[1][j]  # 当前双指针指向的两数之和
            if x == target:  # 和恰好等于目标值
                return True  # 找到满足条件的一对数，返回真
            if x < target:  # 和偏小，需要增大，于是让左数组指针右移
                i += 1  # 取 nums[0] 中更大的元素
            else:  # 和偏大，需要减小，于是让右数组指针左移
                j -= 1  # 取 nums[1] 中更小的元素
        return False  # 指针相遇仍未命中，说明不存在这样的两数
