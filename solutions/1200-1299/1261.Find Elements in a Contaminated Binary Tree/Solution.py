# 题目：1261. 在受污染的二叉树中查找元素（Find Elements in a Contaminated Binary Tree）
# 思路：按完全二叉树编号规则（左 2x+1、右 2x+2）从根值 0 递归还原所有节点，把值存入集合，find 时 O(1) 判存在。
# 时间复杂度：构造 O(n)、find O(1)；空间复杂度：O(n)，集合保存全部节点值。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class FindElements:  # 题解类：构造阶段还原整棵树，find 阶段只查集合

    def __init__(self, root: Optional[TreeNode]):  # 构造方法：root 是值被污染的树根
        def dfs(root: Optional[TreeNode]):  # 内部递归函数，负责还原以 root 为根的子树
            self.s.add(root.val)  # 当前节点值已经正确，加入集合供查询
            if root.left:  # 存在左孩子时继续还原
                root.left.val = root.val * 2 + 1  # 左孩子编号规则：2 * 父值 + 1
                dfs(root.left)  # 递归还原左子树
            if root.right:  # 存在右孩子时继续还原
                root.right.val = root.val * 2 + 2  # 右孩子编号规则：2 * 父值 + 2
                dfs(root.right)  # 递归还原右子树

        root.val = 0  # 题目规定根节点原本的值是 0
        self.s = set()  # 集合必须先于 dfs 创建，dfs 内部会往 self.s 里写
        dfs(root)  # 启动还原遍历

    def find(self, target: int) -> bool:  # 查询 target 是否是还原后树中的某个节点值
        return target in self.s  # 集合成员判断，平均 O(1)


# Your FindElements object will be instantiated and called as such:
# obj = FindElements(root)
# param_1 = obj.find(target)
