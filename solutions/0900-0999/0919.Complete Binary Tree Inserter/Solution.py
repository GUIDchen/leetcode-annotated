# 题目：919. 完全二叉树插入器（Complete Binary Tree Inserter）
# 思路：BFS 把完全二叉树按层序存进列表，插入位置由 (len-1)//2 直接定位，左孩子空就补左、否则补右。
# 时间复杂度：构造 O(n)，insert 均摊 O(1)，get_root O(1)；空间复杂度：O(n)，保存层序节点。
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class CBTInserter:  # 完全二叉树的插入器类

    def __init__(self, root: Optional[TreeNode]):  # root 是已有的完全二叉树根节点
        self.tree = []  # 按层序保存所有节点，下标对应完全二叉树的编号
        q = deque([root])  # BFS 队列，初始只放根节点
        while q:  # 队列非空就继续扩展
            for _ in range(len(q)):  # 固定当前层节点数并逐个处理，保证层序
                node = q.popleft()  # 弹出队首节点
                self.tree.append(node)  # 记录到层序数组
                if node.left:  # 存在左孩子才入队
                    q.append(node.left)  # 左孩子入队
                if node.right:  # 存在右孩子才入队
                    q.append(node.right)  # 右孩子入队

    def insert(self, val: int) -> int:  # 插入新值，返回新节点父节点的值
        p = self.tree[(len(self.tree) - 1) // 2]  # 新节点的父节点下标为 (len-1)//2
        node = TreeNode(val)  # 为新值创建节点
        self.tree.append(node)  # 追加到层序数组
        if p.left is None:  # 左孩子为空就先补左孩子
            p.left = node  # 挂到左孩子
        else:  # 否则挂到右孩子
            p.right = node  # 挂到右孩子
        return p.val  # 返回父节点的值

    def get_root(self) -> Optional[TreeNode]:  # 取根节点
        return self.tree[0]  # 层序数组首元素即根


# Your CBTInserter object will be instantiated and called as such:
# obj = CBTInserter(root)
# param_1 = obj.insert(val)
# param_2 = obj.get_root()
