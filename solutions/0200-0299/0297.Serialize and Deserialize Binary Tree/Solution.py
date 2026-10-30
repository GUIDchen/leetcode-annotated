# 题目：297. 二叉树的序列化与反序列化（Serialize and Deserialize Binary Tree）
# 思路：层序（BFS）编码，空结点记为 #、结点值之间用逗号分隔；反序列化时用同一层序队列逐个给父结点补左右孩子。
# 时间复杂度：O(n)，每个结点进出队列各一次；空间复杂度：O(n)，队列与结果列表最多存 n 个元素。
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None


class Codec:  # Codec：负责树的序列化与反序列化
    def serialize(self, root):  # root：树根；返回层序编码后的字符串
        """Encodes a tree to a single string.

        :type root: TreeNode
        :rtype: str
        """
        if root is None:  # 空树需要单独处理
            return ""  # 空树编码为空串
        q = deque([root])  # 层序（BFS）队列，初始只有根结点
        ans = []  # 用列表收集各结点的 token
        while q:  # 队列非空就继续层序遍历
            node = q.popleft()  # 取出队首结点（可能是 None）
            if node:  # 是真实结点
                ans.append(str(node.val))  # 记录结点值
                q.append(node.left)  # 左孩子入队（可能为 None，也要入队占位）
                q.append(node.right)  # 右孩子入队（可能为 None，也要入队占位）
            else:  # 空结点用 # 占位
                ans.append("#")  # 记录空标记
        return ",".join(ans)  # 用逗号拼接成最终字符串

    def deserialize(self, data):  # data：编码字符串；返回重建出的树根
        """Decodes your encoded data to tree.

        :type data: str
        :rtype: TreeNode
        """
        if not data:  # data：编码字符串；空串对应空树
            return None  # 返回空树
        vals = data.split(",")  # 按逗号切分出所有 token
        root = TreeNode(int(vals[0]))  # 第一个 token 就是根结点
        q = deque([root])  # 层序队列，保存待补孩子的结点
        i = 1  # token 下标，从根之后的 1 开始
        while q:  # 逐个结点补左右孩子
            node = q.popleft()  # 取出队首父结点
            if vals[i] != "#":  # 左孩子非空
                node.left = TreeNode(int(vals[i]))  # 新建左孩子挂到父结点上
                q.append(node.left)  # 左孩子入队，等待补它自己的孩子
            i += 1  # 前进到下一个 token
            if vals[i] != "#":  # 右孩子非空
                node.right = TreeNode(int(vals[i]))  # 新建右孩子挂到父结点上
                q.append(node.right)  # 右孩子入队，等待补它自己的孩子
            i += 1  # 前进到下一个 token
        return root  # 返回重建好的树根


# Your Codec object will be instantiated and called as such:
# codec = Codec()
# codec.deserialize(codec.serialize(root))
