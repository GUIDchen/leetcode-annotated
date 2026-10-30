# 题目：1586. 二叉搜索树迭代器 II（Binary Search Tree Iterator II）
# 思路：构造时中序遍历把 BST 的值按升序存入数组，再用下标 i 表示当前位置，next/prev 只是移动下标。
# 时间复杂度：构造 O(n)，四个接口均 O(1)；空间复杂度：O(n)，数组保存全部节点值。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class BSTIterator:  # 二叉搜索树迭代器
    def __init__(self, root: Optional[TreeNode]):  # 构造时把整棵树中序遍历成升序数组
        self.nums = []  # 存放中序遍历结果

        def dfs(root):  # 内部递归函数：中序遍历（左 → 根 → 右）
            if root is None:  # 空节点是递归出口
                return
            dfs(root.left)  # 先左子树，得到更小的值
            self.nums.append(root.val)  # 再记录根节点的值
            dfs(root.right)  # 最后右子树，得到更大的值

        dfs(root)  # 完成整棵树的遍历
        self.i = -1  # 当前下标，-1 表示还没有访问任何元素

    def hasNext(self) -> bool:  # 是否还能向后移动
        return self.i < len(self.nums) - 1  # 下标未到末尾即存在下一个元素

    def next(self) -> int:  # 移动到下一个元素并返回它的值
        self.i += 1  # 下标右移一位
        return self.nums[self.i]  # 返回新位置上的值

    def hasPrev(self) -> bool:  # 是否还能向前移动
        return self.i > 0  # 下标大于 0 才存在前驱元素

    def prev(self) -> int:  # 移动到前一个元素并返回它的值
        self.i -= 1  # 下标左移一位
        return self.nums[self.i]  # 返回新位置上的值


# Your BSTIterator object will be instantiated and called as such:
# obj = BSTIterator(root)
# param_1 = obj.hasNext()
# param_2 = obj.next()
# param_3 = obj.hasPrev()
# param_4 = obj.prev()
