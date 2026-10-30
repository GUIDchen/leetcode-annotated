# 题目：173. 二叉搜索树迭代器（Binary Search Tree Iterator）
# 思路：构造时用闭包做一次中序遍历，把升序结果存进 self.vals；next 取当前下标并后移，hasNext 比较下标与长度。
# 时间复杂度：构造 O(n)，next 与 hasNext 均为 O(1)；空间复杂度：O(n)，保存全部节点值。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class BSTIterator:  # 二叉搜索树迭代器：按中序（升序）依次返回节点值
    def __init__(self, root: TreeNode):  # 构造函数：初始化下标并完成一次中序遍历
        def inorder(root):  # 闭包形式的递归中序遍历：左 → 根 → 右
            if root:  # 空节点直接返回
                inorder(root.left)  # 先遍历左子树，让更小的值先入列表
                self.vals.append(root.val)  # 访问根节点，把值追加到 self.vals
                inorder(root.right)  # 再遍历右子树

        self.cur = 0  # 下一个要弹出的下标
        self.vals = []  # 先建好空列表，供上面的 inorder 闭包往里写
        inorder(root)  # 真正触发遍历，此后 vals 是升序的

    def next(self) -> int:  # 返回下一个最小值
        res = self.vals[self.cur]  # 取出当前下标的元素
        self.cur += 1  # 下标后移，为下一次调用做准备
        return res  # 返回取到的值

    def hasNext(self) -> bool:  # 是否还有未访问的节点
        return self.cur < len(self.vals)  # 下标小于列表长度说明还有元素


# Your BSTIterator object will be instantiated and called as such:
# obj = BSTIterator(root)
# param_1 = obj.next()
# param_2 = obj.hasNext()
